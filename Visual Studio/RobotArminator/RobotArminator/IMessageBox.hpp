#pragma once
#include "stdafx.h"
#include "VisionPosition.hpp"
namespace RobotArminator
{
    class IMessageBox
    {
    public:
		IMessageBox();
		virtual ~IMessageBox();
        virtual void addToMessageBox(VisionPosition item)=0;
    };
 
}
