#pragma once

enum FeederErrors
{
    FE_OK = 0,
    FE_CONFIG_INVALID,
    FE_CONFIG_READ,
    FE_CONFIG_PARSE,
    FE_EMU_LIB,
    FE_USB_LIB,
    FE_ADAPTER,
};

enum ControllerStrings : unsigned short
{
    ControllerConnected = 20,
    ControllerDisconnected = 4,
    ControllerQuantity = 4,
};

enum RumbleValues {
    RumbleOff = 0x0,
    RumbleOn = 0x1,
    RumbleStop = 0x2, //Potentially dangerous, use this sparingly
    RumbleDelay = 20,
};

enum RumbleInts {
    MotorQuantity = 2,
    XInputMotorMaxStrength = 255,
    PWMFrequencyLimit = 60,
    OneSecond = 1000,
    QuarterSecond = 250,
    Frame = 16,
    MinimumFreq = 1,
    MaxRatio = 1,
};


const float MotorBias = 1.5;