
#include "ManualIntake.h"
#include <frc/Solenoid.h>
#include <frc/Relay.h>
#include <frc/VictorSP.h>

frc::Relay IntakeMotor {2, frc::Relay::kForwardOnly};

frc::Solenoid IntakeOut {0};
frc::Solenoid IntakeIn {1};

frc::VictorSP ElevatorTop {0};
frc::VictorSP ElevatorBottom {1};

ManualIntake::ManualIntake()
{
    IntakeOut.SetPulseDuration(.1);
    IntakeIn.SetPulseDuration(.1);
}

void ManualIntake::RunManualIntake(bool xboxA, bool xboxRBSwitch)
{
    if(xboxRBSwitch)
    {
        IntakeOut.StartPulse();
        IntakeMotor.Set(frc::Relay::kOn);
    }
    else
    {
        IntakeIn.StartPulse();
        IntakeMotor.Set(frc::Relay::kOff);
    }

    if(xboxA)
    {
        ElevatorTop.Set(-.5);
        ElevatorBottom.Set(.5);
    }
    else
    {
        ElevatorTop.Set(0);
        ElevatorBottom.Set(0);
    }
}