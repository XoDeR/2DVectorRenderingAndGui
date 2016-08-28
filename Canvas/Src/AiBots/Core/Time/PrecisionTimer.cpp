#include "PrecisionTimer.h"
#include "Core/Debug/Error.h"

PrecisionTimer::PrecisionTimer() 
{
}

PrecisionTimer::PrecisionTimer(double fps)
: normalFramesPerSecond(fps)
{
	// calculate ticks per frame
	frameTime = perfCountFrequency / normalFramesPerSecond;
}

void PrecisionTimer::startTimer()
{
	timerStarted = true;

	timeElapsed = 0.0;

	// get the time
	lastTime = high_resolution_clock::now();

	// keep a record of when the timer was started
	startTime = lastTime;
	lastTimeInTimeElapsed = lastTime;

	// update time to render next frame
	nextTime = lastTime + microseconds(static_cast<long long>(frameTime));

	return;
}

double PrecisionTimer::getTimeElapsedSinceLastCall()
{
	double result = 0.0;

	lastTimeElapsed = timeElapsed;
	currentTime = high_resolution_clock::now();
	timeElapsed = duration_cast<microseconds>(currentTime - lastTimeInTimeElapsed).count() * timeScale;
	lastTimeInTimeElapsed = currentTime;

	const double smoothness = 5.0;

	if (useSmoothUpdates == true)
	{
		if (timeElapsed < (lastTimeElapsed * smoothness))
		{
			result = timeElapsed;
		}
	}
	else
	{
		result = timeElapsed;
	}

	return result;
}

bool PrecisionTimer::getIsReadyForNextFrame()
{
	RIO_ASSERT(normalFramesPerSecond != 0.0, "PrecisionTimer::getIsReadyForNextFrame<No FPS set in timer>");

	currentTime = high_resolution_clock::now();
	if (currentTime > nextTime)
	{
		timeElapsed = duration_cast<microseconds>(currentTime - lastTime).count() * timeScale;
		lastTime = currentTime;

		// update time to render next frame
		nextTime = currentTime + microseconds(static_cast<long long>(frameTime));

		return true;
	}

	return false;
}

double PrecisionTimer::getCurrentTime()
{
	currentTime = high_resolution_clock::now();
	return duration_cast<microseconds>(currentTime - startTime).count() * timeScale;
}

bool PrecisionTimer::hasTimerStarted() const
{
	return timerStarted;
}

void PrecisionTimer::setSmoothUpdatesOn()
{
	useSmoothUpdates = true;
}

void PrecisionTimer::setSmoothUpdatesOff()
{
	useSmoothUpdates = false;
}

