#pragma once
#include <chrono>

class Clock
{
private:
	uint64_t lastRecordSimple;
	std::chrono::steady_clock::time_point lastRecord;
	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::milliseconds ms;

public:

	Clock();

	//miliseconds since last check
	float GetSimpleDeltaTime();
	double GetDeltaTime();
};

