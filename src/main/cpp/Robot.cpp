
#include "Robot.h"
#include 
#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

frc::Joystick Xbox {0};
double XboxLX = 0;
double XboxLY = 0;
double XboxRX = 0;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
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
  
}

void Robot::TeleopPeriodic()
{

}

void Robot::TestPeriodic()
{

}

void Robot::ReadXbox()
{
  XboxLX = Xbox.GetRawAxis(0);
  XboxLY = Xbox.GetRawAxis(1);
  XboxRX = Xbox.GetRawAxis(4);
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
