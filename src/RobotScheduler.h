/**************************************************************************************************************************************

Author(s): Nathan Stark

Created: 6-21-2021

Last Updated: 6-21-2021

This header provides a class that provides scheduling capabilities using the ESP32's built-in timers.  This allows for code to be run
at fixed periodic intervals to allow for more precise timings and easier calculations for tasks such as kinematics.

**************************************************************************************************************************************/

#ifndef ROBOTSCHEDULER_H
#define ROBOTSCHEDULER_H

#include "RobotSubsystem.h"
#include <vector>

namespace team967 {

    class RobotScheduler {

        private:
            static RobotScheduler* instance;

            // frequency at which to call periodic functions
            int frequency;
            std::vector<RobotSubsystem> registeredSubsystems;
            RobotScheduler();

        public:
            static RobotScheduler& getInstance();

            ~RobotScheduler();
            void begin(void);
            void pause(void);
            bool registerSubsystem(RobotSubsystem& subsystem);
            void resume(void);

    };

}

#endif