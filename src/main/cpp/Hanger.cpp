
#include "Hanger.h"
#include <frc/VictorSP.h>
#include <frc/DigitalInput.h>

//Motors
frc::VictorSP HangerRaise {4};
frc::VictorSP HangerBalance {3};

//DigitalInputs and Corresponding Variables
frc::DigitalInput HangerLLimit {5};
bool hangerLLimit = 0;
frc::DigitalInput HangerRLimit {6};
bool hangerRLimit = 0;

Hanger::Hanger()
{
    hangerLLimit = HangerLLimit.Get();
    hangerRLimit = HangerRLimit.Get();
}

void Hanger::RunHanger(bool yokeUp, bool yokeDown)
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
    
    if(hangerRLimit)
    {
        HangerBalance.Set(1);
    }
    else if(hangerLLimit)
    {
        HangerBalance.Set(-1);
    }
    else
    {
        HangerBalance.Set(0);
    }
}