#include <Loop/LoopManager.h>
#include "ProcessState.h"
#include "../Intent/IntentInfo.hpp"
#include <Spencer.h>
#include <Audio/Playback.h>
#include "../Intent/IntentStore.h"
#include "IdleState.h"
#include "ErrorState.h"
#include "SetupState.h"
#include "../SpeechRhasspy/SpeechToIntentRhasspyHttp.h"

ProcessState::ProcessState(const char* recordingFilename) : recordingFilename(recordingFilename){

}

void ProcessState::processIntent(){
	const IntentInfo* intent;

	bool settings;

	if(intentResult->error == IntentResult::NETWORK){
		delete intentResult;
		intentResult = nullptr;

		if(retried){
			LoopManager::removeListener(this);
			State::changeState(new ErrorState(ErrorType::NETWORK));
			return;
		}

		retried = true;
		SpeechToIntentRhasspyHttp.addJob({ recordingFilename, &intentResult });
		return;
	}else if(intentResult->error == IntentResult::KEY){
		delete intentResult;
		intentResult = nullptr;

		changeState(new ErrorState(ErrorType::APIKEY));
		return;
	}else if(intentResult->error == IntentResult::JSON){
		delete intentResult;
		intentResult = nullptr;

		changeState(new ErrorState(ErrorType::JSON));
	}else if(intentResult->error == IntentResult::INTENT || intentResult->intent == nullptr){

		delete intentResult;
		intentResult = nullptr;

		LEDmatrix.startAnimation(new Animation( new SerialFlashFileAdapter("GIF-questionMark.gif")), true);
		Playback.playMP3(SampleStore::load(Error, "noIntent"));

		Playback.setPlaybackDoneCallback([](){
			changeState(new IdleState());
		});

		return;
	}else{
		settings = (std::string(intentResult->intent) == "Settings");
		if(!settings){
			intent = IntentStore::findIntent(intentResult->intent);
			// if intent == nullptr, it is assumed that the intent is handled by another server connected to rhasspy
			if(intent == nullptr){
				delete intentResult;
				intentResult = nullptr;

				Playback.playMP3(SampleStore::load(SampleGroup::Special, "randomNoise6"));
				Playback.setPlaybackDoneCallback([](){
					Serial.println("Change to IdleState");
					changeState(new IdleState());
				});
				
				return;
			}
		}
	}

	if(settings){
		delete intentResult;
		intentResult = nullptr;

		LEDmatrix.startAnimation(new Animation( new SerialFlashFileAdapter("GIF-talk.gif")), true);
		Playback.playMP3(SampleStore::load(Generic, "setupModeEntering"));

		Playback.setPlaybackDoneCallback([](){
			Serial.println("set");
			changeState(new SetupState());
		});

		return;
	}

	changeState(new IntentState(intent->launch(intentResult->entities), intent->upsell));
}

void ProcessState::bleep(){
	if(random(0,2)) return;

	uint8_t index =  random(0, 12);
	char randomSound[18];
	sprintf(randomSound, "randomNoise%d", index);
	Playback.playMP3(SampleStore::load(SampleGroup::Special, randomSound));
	sprintf(randomSound, "GIF-random%d.gif", index);
	LEDmatrix.startAnimation(new Animation( new SerialFlashFileAdapter(randomSound)), true);
}

void ProcessState::enter(){
	uint8_t loadingAnimationIndex =  random(0, 8);
	char randomAnimation[20];
	sprintf(randomAnimation, "GIF-loading%d.gif", loadingAnimationIndex);
	LEDmatrix.startAnimation(new Animation( new SerialFlashFileAdapter(randomAnimation)), true);
	SpeechToIntentRhasspyHttp.addJob({ recordingFilename, &intentResult });
	LoopManager::addListener(this);
	bleep();
}

void ProcessState::exit(){
	LoopManager::removeListener(this);
	delete intentResult;
}

void ProcessState::loop(uint micros){
	if(intentResult != nullptr){
		processIntent();
	}
}
