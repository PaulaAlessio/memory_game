//
// Created by hifly_admin on 12/28/21.
//

#include <QLCDNumber>
#include "MemoryTimer.h"

void MemoryTimer::startf()  // start player 1 timer
{
    start(1000);
}

void MemoryTimer::countup()  // count up for player 1 timer
{
    simulation++;
    emit updateTimer(simulation);
}

void MemoryTimer::setTimer(int _simulation)
{
    simulation = _simulation;
}
