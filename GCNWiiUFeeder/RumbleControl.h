#pragma once
#include <windows.h>
#include<thread>
#include <atomic>
#include <ViGEm/Client.h>
#include "GCN.h"
#include "Constants.h"

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

        void RumbleCalc(UCHAR smallMotor, UCHAR largeMotor, Rumble::Control* RumbleObj);
        static void Feedback(UCHAR smallMotor, UCHAR largeMotor, Rumble::Control* RumbleObj);
    };
}