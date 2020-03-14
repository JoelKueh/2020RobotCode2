
#include "Hanger.h"
#include <frc/VictorSP.h>
#include <frc/DigitalInput.h>

//Motors
frc::VictorSP HangerRaise {4};
frc::VictorSP HangerBalance {3};

//DigitalInputs and Corresponding Variables
frc::DigitalInput HangerBottomLimit {5};
bool hangerBottomLimit;
frc::DigitalInput HangerTopLimit {6};
bool hangerTopLimit;

Hanger::Hanger()
{
    hangerBottomLimit = HangerBottomLimit.Get();
    hangerTopLimit = HangerTopLimit.Get();
}

void Hanger::RunHanger(bool yokeUp, bool yokeDown, bool yokeLeft, bool yokeRight)
{
    if(yokeUp)
    {
        HangerRaise.Set(1);
    }
    else if(yokeDown)
    {
        HangerRaise.Set(-1);
    }
    else
    {
        HangerRaise.Set(0);
    }
    
    if(yokeLeft)
    {
        HangerBalance.Set(1);
    }
    else if(yokeRight)
    {
        HangerBalance.Set(-1);
    }
    else
    {
        HangerBalance.Set(0);
    }
}