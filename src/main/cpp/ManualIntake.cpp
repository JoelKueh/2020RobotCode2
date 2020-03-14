
#include "ManualIntake.h"
#include <frc/Solenoid.h>
#include <frc/Relay.h>
#include <frc/VictorSP.h>

frc::Relay::Relay IntakeMotor ;

frc::Solenoid IntakeOut {0};
frc::Solenoid IntakeIn {1};

frc::VictorSP ElevatorTop {0};
frc::VictorSP ElevatorBottom {1};

ManualIntake::ManualIntake()
{
    IntakeOut.SetPulseDuration(.1);
    IntakeIn.SetPulseDuration(.1);

    IntakeMotor.kForwardOnly
}

ManualIntake RunManualIntake(bool xboxA, bool xboxRB)
{
    if(xboxRB)
    {
        IntakeOut.StartPulse();
        IntakeMotor.Set(kForward);

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
    else
    {
        IntakeIn.StartPulse();
        IntakeMotor.kOff;
    }
}