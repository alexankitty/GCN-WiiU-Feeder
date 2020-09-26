#include "RumbleControl.h"

namespace Rumble{

    Control::Control(class GCN::Adapter& adapterInstance, class GCN::Adapter::Control& ctlInstance, unsigned short padId)
        : adapter(adapterInstance)
        , ctl(ctlInstance)
        , id(padId)
        , pwmFreqRatio(0)
    {

    }

    void Rumble::Control::RumbleCalc(UCHAR smallMotor, UCHAR largeMotor, Rumble::Control* RumbleObj) {
        float lgMotorFloat = largeMotor;
        float smMotorFloat = smallMotor;
        float rumbleMaths = smMotorFloat * MotorBias;
        float freqOn;
        float freqOff;
        if (rumbleMaths >= lgMotorFloat) {
            rumbleMaths = lgMotorFloat / XInputMotorMaxStrength;
        }
        else {
            rumbleMaths += lgMotorFloat;
            rumbleMaths /= MotorQuantity;
            rumbleMaths /= XInputMotorMaxStrength;
        }
        freqOn = PWMFrequencyLimit * rumbleMaths;
        freqOff = PWMFrequencyLimit - freqOn;
        if (freqOff < MinimumFreq) {
            freqOff = static_cast<float>(MinimumFreq);
        }
        RumbleObj->pwmFreqRatio = ceil(freqOn / freqOff);//How many times do we need to teach you the vibration old man?
        printf("Vibration calculated adjusted to %d\n", static_cast<int>(rumbleMaths));
        printf("PWM Ratio calculated as %d\n", pwmFreqRatio);
    }

    void Rumble::Control::ThreadFunction(Rumble::Control* RumbleObj) {
        RumbleObj->ThreadAlive = true;
        RumbleObj->Rumbling = true;
            for (int i = 0; i < RumbleObj->pwmFreqRatio; i++) {
                if (i == 0) {
                    if (ctl.Rumble[id] == RumbleOn) {
                        ctl.Rumble[id] = RumbleOff;
                    }
                    else {
                        ctl.Rumble[id] = RumbleOn;
                    }
                    adapter.Write(ctl);
                }
                while (RumbleObj->Rumbling && RumbleObj->pwmFreqRatio == 60) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Frame));
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(Frame));
                if (!(i < RumbleObj->pwmFreqRatio)) {
                    i = 0;
                    RumbleObj->pwmFreqRatio = 1 / RumbleObj->pwmFreqRatio;
                }
                if (!RumbleObj->Rumbling) {
                    break;
                }
            }
            ThreadTerminate(RumbleObj); //Cleaning up and exiting thread.
            //ctl.Rumble[id] = RumbleOn;
            //    adapter.Write(ctl);
            //return;
            //std::this_thread::sleep_for(std::chrono::milliseconds(pwmTimeOn));
            //while(pwmTimeOn == OneSecond) {
            //    std::this_thread::sleep_for(std::chrono::milliseconds(QuarterSecond));
            //}
            //if (!Rumbling)
            //    continue;
            //ctl.Rumble[id] = RumbleOff;
            //adapter.Write(ctl);
            //std::this_thread::sleep_for(std::chrono::milliseconds(pwmTimeOn)); 
    }

    void Rumble::Control::ThreadStart(Rumble::Control* RumbleObj) {
        RumbleObj->ThreadFunction(RumbleObj);
    }

    void Rumble::Control::ThreadTerminate(Rumble::Control* RumbleObj) {
        RumbleObj->Rumbling = false;
        ctl.Rumble[id] = RumbleStop;
        adapter.Write(ctl);
        std::this_thread::sleep_for(std::chrono::milliseconds(RumbleDelay));
        ctl.Rumble[id] = RumbleOff;
        adapter.Write(ctl);
        RumbleObj->ThreadAlive = false;
        printf("Terminating vibration thread on controller %d\n", id);
    }

     void Rumble::Control::Feedback(UCHAR smallMotor, UCHAR largeMotor, Rumble::Control* RumbleObj) {
         if (smallMotor == 0 && largeMotor == 0) {
             RumbleObj->Rumbling = false;
             return;
         }
        RumbleObj->RumbleCalc(smallMotor, largeMotor, RumbleObj);
        if (RumbleObj->ThreadAlive) {
            return;
        }
        std::thread rumbleThread(ThreadStart, RumbleObj);
        rumbleThread.detach();
    }
}