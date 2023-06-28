#include "Clock.h"

bool Clock::checkTime(float timeInSeconds)
{
    return glfwGetTime() - time >= timeInSeconds;
}

void Clock::restart()
{
    time = glfwGetTime();
}

void Clock::setClock()
{
    time = glfwGetTime();
}
