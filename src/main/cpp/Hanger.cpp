
#include "Hanger.h"
#include <frc/VictorSP.h>
#include <frc/DigitalInput.h>

//Motors
frc::VictorSP HangerRaise {4};
frc::VictorSP HangerBalance {0};

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

void Hanger::RunHanger(double yokeX, double yokeY)
{
    if(yokeX > 0)
    {
        HangerBalance.Set(.25);
    }
    else if(yokeX < 0)
    {
        HangerBalance.Set(-.25);
    }
    else
    {
        HangerBalance.Set(0);
    }
    
    if(yokeY > 0 && !hangerTopLimit)
    {
        HangerBalance.Set(.25);
    }
    else if(yokeY < 0 && !hangerBottomLimit)
    {
        HangerBalance.Set(-.25);
    }
    else
    {
        HangerBalance.Set(0);
    }
}