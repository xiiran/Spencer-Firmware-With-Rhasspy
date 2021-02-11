#include <Arduino.h>
#include <Spencer.h>
#include "State/State.h"
#include <Util/FlashTools.h>
#include "State/IdleState.h"
#include "Intent/IntentStore.h"
#include "Services/TimeService/TimeService.h"
#include "Intent/TimeIntent.h"
#include "SerialID.h"
#include "Services/SerialSetup.h"
#include "State/StartupState.h"
#include "Services/UpdateChecker.h"
#include "HardwareTest.h"

bool checkJig(){
	if(Settings.get().calibrated) return false;

	pinMode(22, OUTPUT);
	pinMode(21, INPUT_PULLDOWN);

	digitalWrite(22, HIGH);
	delay(10);
	if(digitalRead(21) != HIGH) return false;

	digitalWrite(22, LOW);
	delay(10);
	if(digitalRead(21) != LOW) return false;

	return true;
}

void setup(){
	Serial.begin(115200);

	disableCore0WDT();
	disableCore1WDT();

	if(checkJig()){
		HardwareTest test;
		test.start();
		for(;;);
	}
	Spencer.begin();

	IntentStore::fillStorage();

	SerialID.start();
	LoopManager::addListener(&TimeService);
	LoopManager::addListener(&UpdateChecker);

	Net.addStateListener(&TimeService);
	Net.addStateListener(&UpdateChecker);

	bool firstTime = Spencer.loadSettings();
	State::changeState(new StartupState(firstTime));

	LoopManager::startTask(2, 1);
}

void loop(){
	vTaskDelete(nullptr);
}