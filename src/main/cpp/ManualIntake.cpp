
#include "ManualIntake.h"
#include <frc/Solenoid.h>
#include <frc/Relay.h>
#include <frc/VictorSP.h>

frc::Relay IntakeMotor {2};

frc::Solenoid IntakeOut {0};
frc::Solenoid IntakeIn {1};

frc::VictorSP ElevatorTop {0};
frc::VictorSP ElevatorBottom {1};

ManualIntake::ManualIntake()
{
    IntakeOut.SetPulseDuration(.1);
    IntakeIn.SetPulseDuration(.1);
}

void ManualIntake::RunManualIntake(bool xboxA, bool xboxRB, bool xboxRTrBool)
{
    if(xboxRB)
    {
        // IntakeOut.StartPulse();
        IntakeMotor.Set(frc::Relay::kForward);
    }
    else if(xboxRTrBool)
    {
        IntakeMotor.Set(frc::Relay::kReverse);
    }
    else
    {
        // IntakeIn.StartPulse();
        IntakeMotor.Set(frc::Relay::kOff);
    }

    if(xboxA)
    {
        ElevatorTop.Set(-.6);
        ElevatorBottom.Set(-.6);
    }
    else
    {
        ElevatorTop.Set(0);
        ElevatorBottom.Set(0);
    }
}