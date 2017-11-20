#pragma once

namespace SPH {

	class FPSLimiter {
	public:
		FPSLimiter();
		void init(float maxFPS);

		void begin();
		float end();

		void setMaxFPS(float maxFPS);

	private:
		void calcFPS();

		float _frameTime;
		float _fps;
		float _maxFPS;
		unsigned int _startTicks;
	};



}
