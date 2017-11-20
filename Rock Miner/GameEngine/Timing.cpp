#include "Timing.h"
#include <SDL.h>


namespace SPH {

	FPSLimiter::FPSLimiter() {

	}

	void FPSLimiter::init(float maxFPS) {
		setMaxFPS(maxFPS);
	}

	void FPSLimiter::begin() {
		_startTicks = SDL_GetTicks();
	}

	float FPSLimiter::end() {
		calcFPS();

		float frameTicks = SDL_GetTicks() - _startTicks;
		//Limit FPS
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}
		return _fps;
	}

	void FPSLimiter::setMaxFPS(float maxFPS) {
		_maxFPS = maxFPS;
	}

	void FPSLimiter::calcFPS() {
		static const int NUM_SAMPLES = 10; // Get initilized once, then retains its state when func is next called
		static float frameTimes[NUM_SAMPLES];	// Can only create a static array if you use a const for the number of elements
		static int currentFrame = 0;

		static float prevTicks = SDL_GetTicks();
		float currentTicks;

		currentTicks = SDL_GetTicks();

		_frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
		prevTicks = currentTicks;

		int count;

		if (currentFrame < NUM_SAMPLES) {
			count = currentFrame;
		}
		else {
			count = NUM_SAMPLES;
		}

		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++) {
			frameTimeAverage += frameTimes[i];
		}

		frameTimeAverage /= count;

		if (frameTimeAverage > 0) {
			_fps = 1000.0f / frameTimeAverage;
		}
		else {
			_fps = 120.0f;
		}

		currentFrame++;

	}
}