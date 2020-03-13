
#include "Robot.h"
#include "MyMecanumDrive.h"
#include "Hanger.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

//Motors


//Joysticks
frc::Joystick Xbox {0};
double xboxLX = 0;
double xboxLY = 0;
double xboxRX = 0;

frc::Joystick Yoke {1};

//Variables


//Class Objects
MyMecanumDrive *myMecanumDrive;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  myMecanumDrive = new MyMecanumDrive();
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom)
  {
    // Custom Auto goes here
  }
  else
  {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic()
{
  if (m_autoSelected == kAutoNameCustom)
  {
    // Custom Auto goes here
  }
  else
  {
    // Default Auto goes here
  }
}

void Robot::TeleopInit()
{
  myMecanumDrive->RunMecanums(xboxLX, xboxLY, xboxRX);
}

void Robot::TeleopPeriodic()
{

}

void Robot::TestPeriodic()
{

}

void Robot::ReadXbox()
{
  xboxLX = Xbox.GetRawAxis(0);
  xboxLY = Xbox.GetRawAxis(1);
  xboxRX = Xbox.GetRawAxis(4);
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
