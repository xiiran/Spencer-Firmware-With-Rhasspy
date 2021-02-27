#include "TimerIntent.h"
#include <Spencer.h>
#include "../Services/TimeService/TimeService.h"
#include <Audio/Playback.h>
#include <Spencer.h>
TimerIntent* TimerIntent::instance = nullptr;
TimerIntent::TimerIntent(TimeSpan timerDuration)
{
	instance = this;
	state = TimerState::waitingState;
    this->timerDuration = timerDuration;
}
TimerIntent::~TimerIntent()
{
}
void TimerIntent::loop(uint _time)
{
	switch (state)
	{
	case TimerState::waitingState:
		if(stopTalkingFlag){
			blinkTime+=_time;
			if((blinkTime > 500000 && blinkState) || (blinkTime > 200000 && !blinkState)){
				blinkState = !blinkState;
				blinkTime = 0;
			}
			if(blinkState){
				drawTime(timeDiff.minutes(), timeDiff.seconds());
			}else{
				LEDmatrix.clear();
			}
		}
		break;

	case TimerState::runningState:
		timeDiff = TimeSpan(end.unixtime() - TimeService.getTime());
        if(!isTimerFinished()){
            drawTime(timeDiff.minutes(), timeDiff.seconds());
            if(timeDiff.hours() > 0){
                LEDmatrix.clear();
                done();
            }
        }
        else{
            setTimerFinishedSettingsAndPlaySound();
        }
		break;

	case TimerState::finishedState:
		blinkTime+=_time;
		if((blinkTime > 500000 && blinkState) || (blinkTime > 200000 && !blinkState))
		{
			blinkState = !blinkState;
			blinkTime = 0;
		}
		if(finishedTime > 3000000){
			LEDmatrix.stopAnimation();
			done();
			return;
		}
		if(!Playback.isRunning()){
			finishedTime+=_time;
		}
		if(blinkState){
			drawTime(timeDiff.minutes(), timeDiff.seconds());
		}else{
			LEDmatrix.clear();
		}
		break;
	}
}
void TimerIntent::drawTime(uint minutes, uint seconds)
{
	LEDmatrix.clear();
	if(minutes/10 + '0' != '1'){
		LEDmatrix.drawChar(0,7,minutes/10 + '0', 255, 0);
	}else{
		LEDmatrix.drawChar(1,7,minutes/10 + '0', 255, 0);
	}
	LEDmatrix.drawChar(4,7,(minutes%10) + '0', 255, 0);
	LEDmatrix.drawChar(9,7, seconds/10 + '0', 255, 0);
	if(seconds/10 == 1){
		LEDmatrix.drawChar(12,7,(seconds%10) + '0', 255, 0);
	}else{
		LEDmatrix.drawChar(13,7,(seconds%10) + '0', 255, 0);
	}
}

bool TimerIntent::isTimerFinished(){
    return( timeDiff.totalseconds() <= 0 );
}

void TimerIntent::setTimerFinishedSettingsAndPlaySound(){
    timeDiff = TimeSpan();
    instance->state = TimerState::finishedState;
    instance->blinkState = 1;
    instance->blinkTime = 0;

    CompositeAudioFileSource* timerFinishedSound = new CompositeAudioFileSource();
    const uint8_t numberOfTimesToPlaySound = 3;
    for( uint8_t index = 0; index < numberOfTimesToPlaySound; ++index){
        timerFinishedSound->add(SampleStore::load(SampleGroup::Special, "randomNoise7"));
    }
    Playback.playMP3(timerFinishedSound);
}

void TimerIntent::enter()
{
    LEDmatrix.stopAnimation();
    if(timerDuration.totalseconds() > 0){
        Playback.playMP3(SampleStore::load(SampleGroup::Special, "randomNoise6"));
        Playback.setPlaybackDoneCallback([](){
            instance->state = TimerState::runningState;
            instance->end = DateTime((uint32_t)TimeService.getTime()) + instance->timerDuration;
            instance->timeDiff = TimeSpan(instance->end.unixtime() - TimeService.getTime());
        });
    }
    else{
        done();
    }
}

void TimerIntent::exit()
{
}