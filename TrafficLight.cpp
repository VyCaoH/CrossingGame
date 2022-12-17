#include "TrafficLight.h"
TrafficLight::TrafficLight()
{
	state = true;
	time = 100;
}

TrafficLight::TrafficLight(int state, float time)
{
	this->state = state;
	this->time = time;
}

bool TrafficLight::getState()
{
	return state;
}
int TrafficLight::getTime()
{
	return time;
}

void TrafficLight::setState(int state_)
{
	this->state = state_;
}
void TrafficLight::setTime(float time_)
{
	this->time = time_;
}

void TrafficLight::change(float dt, float time_ )
{
	while (time < 0)
	{
		state = !state;
		time = time_;
	}
	time = time - dt;
}