#pragma once
#include "Entity.h"
enum STATE { GO, STOP };
class TrafficLight : public Entity
{
private:
	int state, time;
public:
	TrafficLight();
	TrafficLight(int s, int t);
	int getState();
	int getTime();
	void setState(int state_);
	void setTime(int time_);
	void change(int newTime);
};
