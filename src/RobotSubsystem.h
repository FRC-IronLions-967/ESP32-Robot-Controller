/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-21-2021

Last Updated: 6-21-2021

This header provides a class that provides scheduling capabilities using the ESP32's built-in timers.  This allows for code to be run
at fixed periodic intervals to allow for more precise timings and easier calculations for tasks such as kinematics.

**************************************************************************************************************************************/

#ifndef ROBOTSUBSYSTEM_H
#define ROBOTSUBSYSTEM_H

namespace team967 {

    class RobotSubsystem {

        public:
            // called when the subsystem is first registered to the scheduler
            virtual void onRegister() = 0;
            // called at whatever frequency the scheduler runs at
            virtual void periodic() = 0;

    };

}

#endif