#include "MyMecanumDrive.h"
#include <frc/drive/MecanumDrive.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include "WiringDiagram.h"

ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelBackLeft {WiringDiagram::wheelBackLeftPort};
ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelBackRight {WiringDiagram::wheelBackRightPort};
ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelFrontRight {WiringDiagram::wheelFrontRightPort};
ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelFrontLeft {WiringDiagram::wheelFrontLeftPort};

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

void MyMecanumDrive::RunNormalWheels(double xboxLX, double xboxLY)
{
    Mecanums.DriveCartesian(xboxLX, xboxLY, 0);
}