# Warning
This software is provided without any explicit warranty and is use-at-your-own-risk. While I've done my best to ensure everything works right, I'm not responsible for any damaged peripherals, though the worst I imagine might happen is a gamecube motor burning out.

# GCN-WiiU-Feeder
Gamecube WiiU Adapter Feeder for ViGEm driver

This Feeder was inspired by the vJoy implementation by m4sv and uses the same approach except the program was rewritten in C++ and designed to be more flexible.

# Features
* Plug-n-Play controllers, automatic registration
* Diagonal Stretching to emulate N64 controllers + power
* Axis Centering, arbitrary transformation value
* Digital button <-> Analog stick/trigger mapping
* Flexible YAML configuration
* Rumble/Vibration/Force Feedback Support (Alpha)

# Used Libraries
* libusb 1.0.23
* ViGEmClient v1.16.107.0 (Updated 9/25/2020)
* yaml-cpp 0.6.3

# How to install and run?
* Install ViGEm Driver https://github.com/ViGEm/ViGEmBus/releases/download/v1.16.112/ViGEmBus_Setup_1.16.115.exe
* Install WiiU Adapter Driver installer (Run with Admin Rights!) https://github.com/aglab2/libwdi/releases/download/wii-u-1.0/WiiUAdapterInstaller.exe
* Download the feeder GCNWiiUFeeder from https://github.com/aglab2/GCN-WiiU-Feeder/releases/download/0.1/GCNWiiUFeeder-x64.exe
* Get example.zip config files and extract them to the same folder as executable file is
* Run the executable with Admin rights and pick normal.yaml config
* If 'Feeder is running!' appeared, the program has successfully started!
* Enjoy and Test!

# Troubleshooting
If program failed to load, it will output the line that you may use to troubleshoot the problem. L=Line, A=Answer.
* L: **No config files detected**
* A: Make sure you have yaml files from examples.zip extract to the same folder as exe file is.
* L: **Failed to read config**
* A: Feeder can't access the config or it is not YAML file. Make sure you launch with Admin rights and use proper config.
* L: **Failed to parse config**
* A: Config is a proper YAML file but Feeder can't parse it. Check the file.
* L: **Failed to detect WiiU Adapter**
* A: Make sure to have WiiU Adapter Driver installed (Run installer Admin Rights!) or use Zadig to replace the WUP-028 driver to WinUSB.
* L: **Failed to detect ViGEm**
* A: Make sure to have ViGEm Driver installed.
* L: **Failed to setup LibUsb**
* L: **Failed to allocate ViGEm**
* A: Report this as an issue on GitHub.
* L: **Failed to start feeding WiiU inputs**
* A: WiiU Adapter is malfunctioning, try reinserting USB device. If it does not help, report this as an issue on GitHub.


# Current To Do List
* Set a default controller position when no data has been received from the controller
* Set a deadzone for rest position to combat joystick and trigger jitter

# Future plans
* Push this code to a library
* Create a C# front end UI
