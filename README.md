# ESP32-Robot-Controller
Repo for the library to run an FRC-style robot from an ESP32 microcontroller with a Bluetooth joystick and PWM control for motors.

# General Information
Originally, this library was for an ESP32 and a PS3 controller connected via Bluetooth.  It has since been updated for the ESP32-S3 and now uses Bluepad32 to allow connections to a wider range of controllers.  Please note that on the ESP32-S3, only BLE controllers can be used (not classic Bluetooth).  While still a work in progress, common classes such as the motor controllers, SPI, and PWM provide simple interfaces to easily allow the library to be extended if desired.

This library is designed with a specific custom board in mind that was created by members of Team 967.  However, it should be able to be easily modified to function on most other boards that use a controller from the ESP32 family.  If you are interested in the custom board, please feel free to reach out to us!

# Installation and Setup
You will need a computer with the Arduino IDE or PlatformIO installed to use this library.  For both, make sure you install Bluepad32 to enable connection to Bluetooth game controllers.  Instructions for installing Bluepad32 can be found [here](https://bluepad32.readthedocs.io/en/latest/getting_started/).  Both of these environments work without any currently known limitations, but the rest of the instructions assume the Arduino IDE since that is what we use with students.  If you are installing this library from a tag, simply download the provided library zip file and import it into your Arduino IDE.  Instructions for importing a zipped library into Arduino can be found [here](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries/#importing-a-zip-library).  If you have cloned the repository (such as to make your own modifications), simply run the `export_arduino_lib.sh` script in the bin directory and import the resulting zip file.

Importing the library into Arduino will result in the tank drive example showing up in the Arduino examples menu.  You can use this as a quick compilation test to make sure things are set up correctly.

# Limitations
This library has limited support for more complex items like sensors, brushless motors, etc.  These are currently beyond the scope of what we are looking to achieve with the platform, but more features may be added in the future.
