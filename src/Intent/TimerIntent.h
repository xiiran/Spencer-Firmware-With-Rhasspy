#ifndef SPENCER_TIMERINTENT_H
#define SPENCER_TIMERINTENT_H

#include <Arduino.h>
#include "Intent.hpp"
#include "../Services/TimeService/DateTime.hpp"

enum class TimerState{
	waitingState, runningState, finishedState  
};

class TimerIntent: public Intent
{
public:
	TimerIntent(TimeSpan timerDuration);
	virtual ~TimerIntent() override;
	void loop(uint _time) override;
	void enter() override;
	void exit() override;
	
private:
	static TimerIntent* instance;
    DateTime end;
	TimerState state = TimerState::waitingState;
    TimeSpan timerDuration;
	TimeSpan timeDiff;
	bool stopTalkingFlag = 0;
	uint finishedTime = 0;
	uint blinkTime = 0;
	bool blinkState = 0;

	void drawTime(uint minutes, uint seconds);
    bool isTimerFinished();
    void setTimerFinishedSettingsAndPlaySound();
};


#endif