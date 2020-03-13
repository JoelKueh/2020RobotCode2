
#include "MecanumDrive.h"
#include <frc/MecanumDrive.h>
#include <WPI_VictorSPX.h>


MecanumDrive::MecanumDrive()
{
    WPI_VictorSPX WheelBackLeft {3};
    WheelBackLeft.SetInverted(true);

    WPI_VictorSPX WheelBackRight {4};
    WheelBackRight.SetInverted(true);

    WPI_VictorSPX WheelFrontRight {2};

    WPI_VictorSPX WheelFrontLeft {1};
    WheelFrontLeft.SetInverted(true);

    frc::MecanumDrive Mecanums {WheelFrontLeft , WheelBackLeft , WheelFrontRight , WheelBackRight};
}

MecanumDrive::RunMecanums(double xboxLX, double xboxLY, double xboxRX)
{   

}
