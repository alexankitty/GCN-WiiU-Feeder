#include "EmuController.h"
#include "RumbleControl.h"

namespace Emu
{
    Lib::Lib() 
        : Client(vigem_alloc())
        , IsConnected(false)
    { }

    Lib::~Lib()
    {
        if (Client)
        {
            if (IsConnected)
                vigem_disconnect(Client);

            vigem_free(Client);
        }
    }

    bool Lib::Connect()
    {
        IsConnected = VIGEM_SUCCESS(vigem_connect(Client));
        return IsConnected;
    }

    Device::Device(class Lib& lib, class Rumble::Control& RumbleDeviceInstance)
        : Lib(lib)
        , Target(vigem_target_x360_alloc())
        , IsConnected(false)
        , RumbleDevice(RumbleDeviceInstance)
    {

    }

    Device::~Device()
    {
        if (Target)
        {
            Disconnect();
            vigem_target_x360_unregister_notification(Target);
            vigem_target_free(Target);
        }
    }

    bool Device::Connect()
    {
        if (IsConnected)
            return true;

        IsConnected = VIGEM_SUCCESS(vigem_target_add(*Lib, Target));
        vigem_target_x360_register_notification(*Lib, Target, &RumbleNotify, &RumbleDevice);
        return IsConnected;
    }

    bool Device::Disconnect()
    {
        if (!IsConnected)
            return false;
        vigem_target_x360_unregister_notification(Target);
        vigem_target_remove(*Lib, Target);
        IsConnected = false;
        return IsConnected;
    }

    bool Device::Update(X360::Controller& c)
    {
        return VIGEM_SUCCESS(vigem_target_x360_update(*Lib, Target, c));
    }

    VOID CALLBACK RumbleNotify(
        PVIGEM_CLIENT Client,
        PVIGEM_TARGET Target,
        UCHAR LargeMotor,
        UCHAR SmallMotor,
        UCHAR LedNumber,
        LPVOID UserData
    ){
        //To Do: Investigate why ViGEm always spits out the same value for both motors
        printf("Small motor %d\n", SmallMotor);
        printf("Large Motor %d\n", LargeMotor);
        Rumble::Control* RumbleObj = static_cast<Rumble::Control*>(UserData);
        printf("Starting Vibration on Controller ID: %d\n", RumbleObj->id);
        RumbleObj->Feedback(SmallMotor, LargeMotor, RumbleObj);

    }
}