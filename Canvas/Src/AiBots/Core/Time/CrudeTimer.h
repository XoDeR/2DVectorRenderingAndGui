#pragma once
#include <chrono>

using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

// timer to measure time in seconds
class CrudeTimer
{
public:
	static CrudeTimer& getInstance();
	
	// returns how much time has elapsed (in seconds) since the timer was started
	double getCurrentTime()
	{
		milliseconds millisecs = duration_cast<milliseconds>(high_resolution_clock::now() - startTime);
		return millisecs.count() * 0.001;
	}
private:
	// set to the time when class is instantiated
	high_resolution_clock::time_point startTime;

	// set the start time
	CrudeTimer()
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	// no copying, no assignment
	CrudeTimer(const CrudeTimer&) = delete;
	CrudeTimer& operator=(const CrudeTimer&) = delete;
};
