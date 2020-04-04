
#include "Robot.h"

//Both Manual and Auto Classes
#include "MyMecanumDrive.h"
#include "Hanger.h"

//Manual Classes
#include "ManualIntake.h"
//#include "ManualShooter.h"

//Auto Classes
#include "AutoIntake.h"
#include "AutoAim.h"
#include "AutoShooter.h"
#include "PixyCam.h"

//Libraries and Other things
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <iostream>
//#include <frc/PWMSpeedController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>

//Motor Controllers


//Joysticks and their inputs (Axes set to doubles because they are decimals)
frc::Joystick Xbox {0};
double xboxLX = 0;
double xboxLY = 0;
double xboxRX = 0;
bool xboxA = false;
bool xboxYRaw = false
bool xboxYToggle = false;
bool xboxRBSwitch = false;

frc::Joystick Yoke {1};
double yokeX = 0;
double yokeY = 0;
bool yokeUp = false;
bool yokeDown = false;
bool yokeLeft = false;
bool yokeRight = false;

//Digital Inputs
frc::DigitalInput TurretLeftLimit {3};
bool turretLeftLimit = 0;
frc::DigitalInput TurretRightLimit {4};
bool turretRightLimit = 0;

//Variables


//Class Objects
MyMecanumDrive *myMecanumDrive;
Hanger *hanger;

ManualIntake *manualIntake;

PixyCam *pixyCam;
AutoAim *autoAim;
AutoShooter *autoShooter;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //Why do we need this?
  myMecanumDrive = new MyMecanumDrive();
  hanger = new Hanger();

  manualIntake = new ManualIntake();
  
  pixyCam = new PixyCam();
  autoShooter = new AutoShooter();
}

void Robot::RobotPeriodic() {}

//Runs once. What the robot does just before autonomous.
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

//What the robot does during autonomous.
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

//Runs once. What the robot does when Teleop starts
void Robot::TeleopInit()
{

}

//What the robot does when we gain controll
void Robot::TeleopPeriodic()
{
  //Classes and objects for managability
  myMecanumDrive->RunMecanums(xboxLX, xboxLY, xboxRX);
  hanger->RunHanger(yokeUp, yokeDown, yokeLeft, yokeRight);
  manualIntake->RunManualIntake(xboxA, xboxRBSwitch);
  autoAim->RunAutoAim();
  autoShooter->RunAutoShooter();

  if(xboxYToggle)
  {
    pixyCam->GetStr();
    pixyCam->GetValX();
    pixyCam->GetValY();
    
  }

  //Reading Inputs and setting them to variables to save up resources.
  ReadXbox();
  ReadYoke();
}

void Robot::TestPeriodic()
{

}

void Robot::ReadXbox()
{
  xboxLX = Xbox.GetRawAxis(0);
  if(xboxLX < .2 && xboxLX > -.2)
  {
    xboxLX = 0;
  }

  xboxLY = Xbox.GetRawAxis(1);
  if(xboxLY < .2 && xboxLY > -.2)
  {
    xboxLY = 0;
  }

  xboxRX = Xbox.GetRawAxis(4);
  if(xboxRX < .2 && xboxRX > -.2)
  {
    xboxRX = 0;
  }

  // xboxPOV = Xbox.GetPOV();

  xboxA = Xbox.GetRawButton(1);
  
  if(!xboxYToggle && Xbox.GetRawButton(4))
  {
    xboxYToggle = true;
  }

  if(Xbox.GetRawButtonPressed(6))
  {
    xboxRBSwitch = !xboxRBSwitch;
  }
}

void Robot::ReadYoke()
{
  yokeX = Yoke.GetRawAxis(0);
  if(yokeX < .2 && yokeX > -.2)
  {
    yokeX = 0;
  }

  yokeY = Yoke.GetRawAxis(2);
  if(yokeY < .2 && yokeY > -.2)
  {
    yokeY = 0;
  }

  yokeUp = Yoke.GetRawButton(3);
  yokeDown = Yoke.GetRawButton(2);
  yokeRight = Yoke.GetRawButton(5);
  yokeLeft = Yoke.GetRawButton(4);
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
