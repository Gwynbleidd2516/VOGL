#pragma once

#ifndef CLOCK
#define CLOCK
#include"Tools.h"
class API Clock
{
private:
	float time = 0.0f;
public:
	bool checkTime(float timeInSeconds);

	void restart();

	void setClock();
};

#endif // !CLOCK
