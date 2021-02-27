#ifndef SPENCER_SPEECH2INTENTRHASSPY_H
#define SPENCER_SPEECH2INTENTRHASSPY_H

#include "Speech/SpeechToIntent.h"
#include <string>

class SpeechToIntentRhasspyHttpImpl : public SpeechToIntentImpl {
public:
	SpeechToIntentRhasspyHttpImpl();

protected:
	void doJob(const STIJob& job) override;

private:
	IntentResult* identifyVoice(const char* filename);
	void compress(const char* inputFilename, const char* outputFilename);
	void readRhasspySettings();

	struct RhasspySettings{
		std::string baseUrl;
	};
	RhasspySettings rhasspySettings;
	bool settingsAlreadyRead;
};

extern SpeechToIntentRhasspyHttpImpl SpeechToIntentRhasspyHttp;
#endif