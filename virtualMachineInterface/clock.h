#pragma once 
#include "../defines.h"

/*
@brief : this just flips the computor's clock on or off
*/
void updateClock();

/*
@brief : this tells if it is a rising edge, or if the clock was previously low and is now high
*/
FORGE_API bool isRisingEdge();

/*
@brief : this tells if it is a falling edge, or if the clock was previously high and is now low
*/
FORGE_API bool isFallingEdge();

/*
@brief : this tells if the clock is high, although for now 12/21/2024 00:49 it is completely pointless since nothing takes
more than one clock cycle
*/
FORGE_API bool isClockHigh();

/*
@brief : this tells if the clock is low, although for now 12/21/2024 00:49 it is completely pointless since nothing takes
more than one clock cycle
*/
FORGE_API bool isClockLow();
