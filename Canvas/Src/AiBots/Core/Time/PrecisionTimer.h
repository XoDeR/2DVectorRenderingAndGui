#pragma once

#include <chrono>

using std::chrono::microseconds;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

// high performance timer
class PrecisionTimer
{
public:
	PrecisionTimer();
	PrecisionTimer(double fps);
	// call this immediately prior to game loop. Starts the timer.
	void startTimer();
	// determines if enough time has passed to move onto next frame
	// returns true if it is time to move on to the next frame step
	// To be used if FPS is set
	bool getIsReadyForNextFrame();
	// returns time elapsed since last call to this function.
	double getTimeElapsedSinceLastCall();
	double getCurrentTime();
	bool hasTimerStarted() const;
	void setSmoothUpdatesOn();
	void setSmoothUpdatesOff();
private:
	high_resolution_clock::time_point currentTime;
	high_resolution_clock::time_point lastTime;
	high_resolution_clock::time_point lastTimeInTimeElapsed;
	high_resolution_clock::time_point nextTime;
	high_resolution_clock::time_point startTime;

	// in microseconds
	double frameTime = 0.0;
	// how many ticks per second (maximum) do we get
	double perfCountFrequency = 1000 * 1000; // microseconds
	double timeScale = 1.0 / perfCountFrequency;

	double timeElapsed = 0.0;
	double lastTimeElapsed = 0.0;
	

	double normalFramesPerSecond = 0.0;
	double slowFramesPerSecond = 1.0;

	bool timerStarted = false;

	// if true a call to getTimeElapsedSinceLastCall() will return 0 if the current time elapsed is much smaller than the previous
	// Used to counter the problems associated with the user using menus/resizing/moving a window etc
	bool useSmoothUpdates = false;
};