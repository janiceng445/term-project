#pragma once

const int SECOND = 1000;
const int BREATHING_TIME = 2; // how long "active" is enabled

class Timer
{
	private:
	int startTime;
	int currentTime;
	int delay;
	bool active;
	bool ready;

	public:
	Timer(int d);
	void stopTimer();
	void startTimer();
	void runTimer();
	void setDelay(int d);
	void restartTimer();
	bool isReady();
	~Timer();
};
