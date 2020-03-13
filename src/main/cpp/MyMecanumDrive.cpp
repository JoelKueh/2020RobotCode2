
#include "MyMecanumDrive.h"
#include <frc/drive/MecanumDrive.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

    ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelBackLeft {3};
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelBackRight {4};
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelFrontRight {2};
    ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelFrontLeft {1};

    frc::MecanumDrive Mecanums {WheelFrontLeft , WheelBackLeft , WheelFrontRight , WheelBackRight};

MyMecanumDrive::MyMecanumDrive()
{
    WheelFrontLeft.SetInverted(true);
    WheelBackRight.SetInverted(true);
    WheelBackLeft.SetInverted(true);
}

void MyMecanumDrive::RunMecanums(double xboxLX, double xboxLY, double xboxRX)
{   
    Mecanums.DriveCartesian(xboxLX , xboxLY , xboxRX);
}
