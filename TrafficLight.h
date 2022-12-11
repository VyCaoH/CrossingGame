#pragma once
#include "Entity.h"
#include <Windows.h>

enum STATE { GO, STOP };
class TrafficLight : public Entity
{
private:
	float time;
	bool state;
public:
	
	TrafficLight();
	TrafficLight(int s, float t);
	bool getState();
	int getTime();
	void setState(int state_);
	void setTime(float time_);
	void change(float dt,float time);
};
