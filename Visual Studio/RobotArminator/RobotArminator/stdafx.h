// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"

namespace RobotArminator {
    //Easy access to the high resolution clock
    typedef boost::posix_time::microsec_clock Clock;

    //easy access to the time_point
    typedef boost::posix_time::ptime Time;
}



// TODO: reference additional headers your program requires here
