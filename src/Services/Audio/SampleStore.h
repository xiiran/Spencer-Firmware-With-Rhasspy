#ifndef SPENCER_SAMPLESTORE_H
#define SPENCER_SAMPLESTORE_H
#include <AudioFileSource.h>

enum SampleGroup{
	Months, Numbers, Jokes, Generic
};

class SampleStore
{
public:
	static AudioFileSource* load(SampleGroup group, char* label);
	static AudioFileSource* load(SampleGroup group, const char* label);
};

extern SampleStore sampleStore;
#endif