#include "stdafx.h"
#include "Clock.h"

Clock::Clock() {
	lastRecordSimple = SDL_GetTicks64();
	lastRecord = clock::now();
}

float Clock::GetSimpleDeltaTime() {
	uint64_t ms = (SDL_GetTicks64() - lastRecordSimple);
	lastRecordSimple = SDL_GetTicks64();
	return (float)ms/1000.0f;//seconds
}
double Clock::GetDeltaTime() {
	std::chrono::duration<double> deltaTime = clock::now() - lastRecord;
	double dTime = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime).count();
	lastRecord = clock::now();
	return dTime / 1000000.0f;// miliseconds 
}
//will think what to do about different return types later