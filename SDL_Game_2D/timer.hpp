#pragma once

class Timer {
	float length, time;
	bool timeout;
public:
	Timer(float length) : length(length), time(0), timeout(false) {}
	void step(float deltaTime) {
		time += deltaTime;
		if (time >= length) { 
			time -= length;
			timeout = true;
		}
	}

	bool isTimeout() { return timeout; }
	float getTime() { return time; }
	float getLength() { return length; }
	void reset() { time = 0; timeout = false; }
};