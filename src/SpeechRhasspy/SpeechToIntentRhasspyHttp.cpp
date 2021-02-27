#include <SerialFlash.h>
#include <ArduinoJson.h>
#include "SpeechToIntentRhasspyHttp.h"
#include "Util/Base64Encode.h"
#include <Network/StreamableHTTPClient.h>
#include <Network/Net.h>
#include "Settings.h"
#include "Audio/Compression.h"
#include <SPIFFS.h>

SpeechToIntentRhasspyHttpImpl SpeechToIntentRhasspyHttp;

SpeechToIntentRhasspyHttpImpl::SpeechToIntentRhasspyHttpImpl() : settingsAlreadyRead(false){

}

void SpeechToIntentRhasspyHttpImpl::doJob(const STIJob& job){
	if(!settingsAlreadyRead){
		readRhasspySettings();
		settingsAlreadyRead = true;
	}

	if(!Net.checkConnection() && !Net.reconnect()){
		*job.result = new IntentResult(IntentResult::NETWORK);
		return;
	}

	IntentResult* result = identifyVoice(job.recordingFilename);

	*job.result = result;
}

IntentResult* SpeechToIntentRhasspyHttpImpl::identifyVoice(const char* filename){
	compress(filename, "compressed.wav");

	SerialFlashFile file = SerialFlash.open("compressed.wav");
	if(!file){
		Serial.println("Couldn't open file for reading");
		return new IntentResult(IntentResult::FILE);
	}

	uint wavSize = 0;
	file.seek(4); //skip RIFF on start of file
	for(int8_t i = 0; i < 4; i++){
		file.read(&(((char*)(void*)&wavSize)[i]), 1);
	}
	wavSize += 8 + 44;
	file.seek(0);

	StreamableHTTPClient http;
	http.useHTTP10(true);
	http.setReuse(false);
	Serial.println("Speech-to-Intent http begin start");
	const std::string rhasspySpeechToIntentUrl = rhasspySettings.baseUrl + "/api/speech-to-intent";
	if(!http.begin(rhasspySpeechToIntentUrl.c_str())){
		return new IntentResult(IntentResult::NETWORK);
	}
	Serial.println("Speech-to-Intent http begin end");

	http.addHeader("Content-Type", "audio/wav");
	http.addHeader("Accept-Encoding", "identity");
	http.addHeader("Content-Length", String(wavSize));


	if(!http.startPOST()){
		Serial.println("Error connecting");
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return new IntentResult(IntentResult::NETWORK);
	}

	Serial.println("Speech-to-Intent http send start");
	uint sent = 0;
	unsigned char buffer[256];
	while(sent < wavSize){
		uint readSize = min((uint) 256, wavSize - sent);
		file.read(buffer, readSize);
		if(!http.send(buffer, readSize)){
			http.end();
			http.getStream().stop();
			http.getStream().flush();
			return new IntentResult(IntentResult::NETWORK);
		}
		sent += readSize;
	}
	Serial.println("Speech-to-Intent http send end");


	int code = http.finish();
	if(code != 200){
		Serial.printf("HTTP code %d\n", code);
		http.end();
		http.getStream().stop();
		http.getStream().flush();
		return new IntentResult(IntentResult::JSON);
	}

	// https://arduinojson.org/v6/how-to/determine-the-capacity-of-the-jsondocument/
	// Technique 2: compute the capacity with macros
	const int SIZE = JSON_ARRAY_SIZE(8) + JSON_OBJECT_SIZE(60) + 600;
	DynamicJsonDocument json(SIZE);
	DeserializationError error = deserializeJson(json, http.getStream());
	serializeJson(json, Serial);
	Serial.println();

	http.end();
	http.getStream().stop();
	http.getStream().flush();

	if(error){
		Serial.print(F("Parsing JSON failed: "));
		Serial.println(error.c_str());
		return new IntentResult(IntentResult::JSON);
	}

	if(!json.containsKey("text")){
		return new IntentResult(IntentResult::INTENT);
	}

	IntentResult* result = new IntentResult(IntentResult::OK);

	const char* transcript = json["text"].as<const char*>();
	uint32_t transcriptLength = strlen(transcript);
	result->transcript = static_cast<char*>(malloc(transcriptLength + 1));
	memset(result->transcript, 0, transcriptLength+1);
	memcpy(result->transcript, transcript, transcriptLength);

	const char* intent;
	if(!json.containsKey("intent") || (intent = json["intent"]["name"].as<const char*>())[0] == '\0'){
		result->intent = nullptr;
		result->confidence = 1;
		result->error = IntentResult::INTENT;
		return result;
	}

	result->confidence = json["intent"]["confidence"].as<float>();

	uint32_t intentLength = strlen(intent);
	result->intent = static_cast<char*>(malloc(intentLength + 1));
	memset(result->intent, 0, intentLength+1);
	memcpy(result->intent, intent, intentLength);

	if(!json.containsKey("slots")) return result;

	for(const auto& entityObj : json["slots"].as<JsonObject>()){
		std::string slot = entityObj.key().c_str();
		std::string value = entityObj.value().as<std::string>();

		if(result->entities.find(slot) != result->entities.end()) continue;

		result->entities.insert(std::pair<std::string, std::string>(slot, value));
	}

	return result;
}

void SpeechToIntentRhasspyHttpImpl::compress(const char* inputFilename, const char* outputFilename){
	SerialFlashFile input = SerialFlash.open(inputFilename);
	if(!input){
		Serial.println("Failed opening input file");
		return;
	}

	SerialFlashFile output = SerialFlash.open(outputFilename);
	if(!output){
		Serial.println("Failed opening output file");
		return;
	}

	uint wavSize = 0;
	input.seek(4); //skip RIFF on start of file
	for(int8_t i = 0; i < 4; i++){
		input.read(&(((char*)(void*)&wavSize)[i]), 1);
	}
	wavSize += 8;
	wavSize -= 44;
	input.seek(44); // wavHeaderSize
	output.seek(44); // wavHeaderSize

	const uint16_t samplesPerProcess = 32 * 100;

	Compression comp(16000, 10, 5, -26, 5, 5, 0.003f, 0.250f);
	int16_t* inputBuf = static_cast<int16_t*>(malloc(sizeof(int16_t) * samplesPerProcess));
	int16_t* outputBuf = static_cast<int16_t*>(malloc(sizeof(int16_t) * samplesPerProcess));

	size_t totalProcessed = 0;
	while(input.read(inputBuf, samplesPerProcess * sizeof(int16_t))){
		comp.process(inputBuf, outputBuf, samplesPerProcess);
		output.write(outputBuf, samplesPerProcess * sizeof(int16_t));

		totalProcessed += samplesPerProcess * sizeof(int16_t);
		if(totalProcessed >= wavSize) break;
	}

	input.close();
	output.close();
	free(inputBuf);
	free(outputBuf);
}


void SpeechToIntentRhasspyHttpImpl::readRhasspySettings(){
	// see also https://arduinojson.org/v6/example/config/
	// Open file for reading
	SPIFFS.begin();
	File file = SPIFFS.open("/settings/rhasspy_settings.json");

	// Allocate a temporary JsonDocument
	// Don't forget to change the capacity to match your requirements.
	// Use arduinojson.org/v6/assistant to compute the capacity.
	StaticJsonDocument<512> doc;

	// Deserialize the JSON document
	DeserializationError error = deserializeJson(doc, file);
	if (error){
		Serial.println(F("Failed to read file, using default settings"));
	}

	// Copy values from the JsonDocument to the settings
	rhasspySettings.baseUrl = doc["baseUrl"].as<std::string>();
	Serial.print("Rhasspy base url: ");
	Serial.println(rhasspySettings.baseUrl.c_str());

	// Close the file (Curiously, File's destructor doesn't close the file)
	file.close();
}