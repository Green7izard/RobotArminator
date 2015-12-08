// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>

#include <chrono>

namespace RobotArminator {
    //https://www.guyrutenberg.com/2013/01/27/using-stdchronohigh_resolution_clock-example/

    //Easy access to the high resolution clock
    typedef std::chrono::high_resolution_clock Clock;

    //easy access to the time_point
    typedef std::chrono::time_point<Clock> timePoint;
}



// TODO: reference additional headers your program requires here
