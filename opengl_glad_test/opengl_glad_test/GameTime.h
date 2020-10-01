#pragma once
#include<glfw/glfw3.h>
class GameTime
{
public:
	GameTime();
	float GetDeltaTime() { return deltaTime; };
	void Time_Measure();
	void DeltaTime_Update();	
private:
	float curentFrame;
	float larstFrame;
	float deltaTime;

};

