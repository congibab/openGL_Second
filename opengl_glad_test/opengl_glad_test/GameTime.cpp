#include "GameTime.h"

GameTime::GameTime()
{
	curentFrame = 0;
	larstFrame = 0;
	deltaTime = 0;
}

void GameTime::Time_Measure()
{
	curentFrame = glfwGetTime();
}

void GameTime::DeltaTime_Update()
{
	deltaTime = curentFrame - larstFrame;
	larstFrame = curentFrame;
}
