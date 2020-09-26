#pragma once
#include <windows.h>
#include<thread>
#include <atomic>
#include <ViGEm/Client.h>
#include "GCN.h"

namespace Rumble {
    class Control {
    public:
        unsigned short id;
        unsigned short pwmFreqRatio;
        GCN::Adapter& adapter;
        GCN::Adapter::Control& ctl;
        std::atomic<bool> Rumbling = false;
        std::atomic<bool> ThreadAlive = false;

        Control(class GCN::Adapter& adapterInstance, class GCN::Adapter::Control& ctlInstance, unsigned short padId);

        void ThreadFunction(Rumble::Control* rumbleObj);
        static void ThreadStart(Rumble::Control* RumbleObj);
        void ThreadTerminate(Rumble::Control* RumbleObj);


        //To Do: Cleanup old enums
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
        void RumbleCalc(UCHAR smallMotor, UCHAR largeMotor, Rumble::Control* RumbleObj);
        static void Feedback(UCHAR smallMotor, UCHAR largeMotor, Rumble::Control* RumbleObj);
    };
}