#include "MyMecanumDrive.h"
#include <frc/drive/MecanumDrive.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include "WiringDiagram.h"
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>

ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelBackLeft {WiringDiagram::wheelBackLeftPort};
ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelBackRight {WiringDiagram::wheelBackRightPort};
ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelFrontRight {WiringDiagram::wheelFrontRightPort};
ctre::phoenix::motorcontrol::can::WPI_VictorSPX WheelFrontLeft {WiringDiagram::wheelFrontLeftPort};

frc::MecanumDrive Mecanums {WheelFrontLeft , WheelBackLeft , WheelFrontRight , WheelBackRight};

frc::SpeedControllerGroup WheelsLeft {WheelFrontLeft, WheelBackLeft};
frc::SpeedControllerGroup WheelsRight {WheelFrontRight, WheelBackRight};
frc::DifferentialDrive Differential {WheelsLeft, WheelsRight};

MyMecanumDrive::MyMecanumDrive()
{
    WheelFrontLeft.SetInverted(true);
    WheelBackRight.SetInverted(true);
    WheelBackLeft.SetInverted(true);
}

void MyMecanumDrive::RunMecanums(double xboxLX, double xboxLY, double xboxRX)
{   
    // Mecanums.DriveCartesian(xboxLX , xboxLY , xboxRX);
}

void MyMecanumDrive::RunNormalWheels(double xboxLX, double xboxLY)
{
    Mecanums.DriveCartesian(xboxLX, xboxLY, 0);
    // Differential.ArcadeDrive(xboxLX, xboxLY);

    // double leftSpeed = xboxLX + xboxLY;
    // double rightSpeed = xboxLX - xboxLY;

    // WheelBackLeft.Set(leftSpeed);
    // WheelBackRight.Set(rightSpeed);
    // WheelFrontLeft.Set(leftSpeed);
    // WheelFrontRight.Set(rightSpeed);
}

void MyMecanumDrive::TankDrive(double xboxLY, double xboxRY)
{
    WheelFrontLeft.Set(xboxLY);
    WheelBackLeft.Set(xboxLY);
    WheelFrontRight.Set(xboxRY);
    WheelBackRight.Set(xboxRY);
}