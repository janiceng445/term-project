#include "Timer.h"

Timer::Timer(int d)
{
	startTime = 0;
	currentTime = 0;
	delay = d;
	active = true;
	ready = false;
}

void Timer::startTimer() {
	active = true;
}
void Timer::stopTimer() {
	active = false;
}
void Timer::runTimer() {
	if (active) {
		currentTime++;
		if (currentTime > delay && currentTime < delay + BREATHING_TIME) {
			ready = true;
		}
		else if (currentTime > delay + BREATHING_TIME) {
			ready = false;
			restartTimer();
		}
	}
}
void Timer::restartTimer() {
	startTime = 0;
	currentTime = 0;
}
void Timer::setDelay(int d) {
	delay = d;
}
bool Timer::isReady() {
	return ready;
}

Timer::~Timer()
{
}