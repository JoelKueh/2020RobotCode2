
#include "Robot.h"

//Both Manual and Auto Classes
#include "MyMecanumDrive.h"
#include "Hanger.h"

//Manual Classes
#include "ManualIntake.h"

//Auto Classes
#include "AutoIntake.h"
#include "AutoAim.h"
#include "PixyCam.h"

//Turret Class
#include "Turret.h"

//Libraries and Other things
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <iostream>
//#include <frc/PWMSpeedController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>
#include <frc/Timer.h>
#include <experimental/iterator>

//Motor Controllers


//Joysticks and their inputs (Axes set to doubles because they are decimals)
frc::Joystick Xbox {0};
double xboxLX = 0;
double xboxLY = 0;
double xboxRX = 0;
double xboxRY = 0;
bool xboxA = false;
bool xboxYRaw = false; 
bool xboxYToggle = false;
bool xboxRBSwitch = false;
bool xboxRB = false;
bool xboxRTrBool = false;
bool xboxLBSwitch = false;
int xboxPOV = 0;

frc::Joystick Yoke {1};
double yokeX = 0;
double yokeY = 0;
double yokeWheel = 0;
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
Turret *turret;

frc::Timer myAutoTimer;
long double currentAutoTime = 0;
long double lastAutoTime = 0;

// Auto Struct
// struct MyCustomAuto
// {
//   double *pSpeedArray; 
//   double *pDirectionArray;
//   double *pTimeArray;
// };

// MyCustomAuto basicAuto;
//   basicAuto.pSpeedArray = new double[5] {.1, .2, .3, .4, .5};
//   basicAuto.pDirectionArray = new double[5] {0, 0, .5, 0, -.5};
//   basicAtuo.pTimeArray = new double[5] {1, 3, .5, 2, 1};

// Basic Auto
double basicAutoSA[] = {.1, .2, .3, .4, .5};
double basicAutoDA[] = {0, 0, .5, 0, -.5};
double basicAutoTA[] = {4, 3, .5, 2, 4};
  int basicAutoTALength = 0;
bool basicAutoCompleted = false;

// Light Speed Circuit Auto
double autoLSC_SA[] = {1, .5, .2};
double autoLSC_DA[] = {0, .5, -.5};
double autoLSC_TA[] = {1, 1.5, 1};
  int autoLSC_TA_Length = 0;
bool autoLSC_Completed = false;

// Barrel Racing Auto
double autoBR_SA[] = {0};
double autoBR_DA[] = {0};
double autoBR_TA[] = {0};
  int autoBR_TA_Length = 0;
bool autoBR_Completed = false;

// Slalom Auto
double autoSL_SA[] = {0};
double autoSL_DA[] = {0};
double autoSL_TA[] = {0};
  int autoSL_TA_Length = 0;
bool autoSL_Completed = false;

// Bounce Auto
double autoBN_SA[] = {0};
double autoBN_DA[] = {0};
double autoBN_TA[] = {0};
  int autoBN_TA_Length = 0;
bool autoBN_Completed = false;

// Auto Mecanum Storage
double autoMecanumSpeed = 0;
double autoMecanumDirection = 0;

int autonomousIterator = 0;
double lastAutoDelayTime = 0;
double autoDelayTime = 0;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  m_chooser.AddOption("basicAuto", "basicAuto");
  m_chooser.AddOption("Light Speed Circuit", "Light Speed Circuit");
  m_chooser.AddOption("Barrel Racing", "Barrel Racing");
  m_chooser.AddOption("Slalom", "Slalom");
  m_chooser.AddOption("Bounce", "Bounce");
  m_chooser.AddOption("Autonomous Set Uncompleted", "Autonomous Set Uncompleted");
  frc::SmartDashboard::PutData("Auto Modess", &m_chooser);

  myMecanumDrive = new MyMecanumDrive();
  hanger = new Hanger();

  manualIntake = new ManualIntake();
  
  pixyCam = new PixyCam();
  turret = new Turret();

  myAutoTimer.Start();
}

void Robot::RobotPeriodic() {}

//Runs once. What the robot does just before autonomous.
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  basicAutoTALength = sizeof(basicAutoTA)/sizeof(basicAutoTA[0]);
  autoLSC_TA_Length = sizeof(autoLSC_TA)/sizeof(autoLSC_TA[0]);
  autoBR_TA_Length = sizeof(autoBR_TA)/sizeof(autoBR_TA[0]);
  autoSL_TA_Length = sizeof(autoSL_TA)/sizeof(autoSL_TA[0]);
  autoBN_TA_Length = sizeof(autoBN_TA)/sizeof(autoBN_TA[0]);

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
  // std::cout << "Hello" << std::endl;
  myMecanumDrive->RunNormalWheels(autoMecanumDirection, autoMecanumSpeed);
  autoDelayTime = myAutoTimer.Get();
  currentAutoTime = myAutoTimer.Get();

  frc::SmartDashboard::PutNumber("Auto Speed", autoMecanumSpeed);
  frc::SmartDashboard::PutNumber("Auto Direction", autoMecanumDirection);
 
  /*
  if (m_autoSelected == kAutoNameCustom)
  {
    
  }
  else if (m_autoSelected == "basicAuto" && !basicAutoCompleted)
  {
    std::cout << "basicAuto" << std::endl;
    basicAutoCompleted = ReadAndRunCustomAuto(basicAutoSA, basicAutoDA, basicAutoTA, basicAutoTALength);
  }
  else if (m_autoSelected == "Light Speed Circuit" && !autoLSC_Completed)
  {
    std::cout << "LSC" << std::endl;
    autoLSC_Completed = ReadAndRunCustomAuto(autoLSC_SA, autoLSC_DA, autoLSC_TA, autoLSC_TA_Length);
  }
  else if (m_autoSelected == "Barrel Racing" && !autoBR_Completed)
  {
    std::cout << "BR" << std::endl;
    autoBR_Completed = ReadAndRunCustomAuto(autoBR_SA, autoBR_DA, autoBR_TA, autoBR_TA_Length);
  }
  else if (m_autoSelected == "Slalom" && !autoSL_Completed)
  {
    std::cout << "SL" << std::endl;
    autoSL_Completed = ReadAndRunCustomAuto(autoSL_SA, autoSL_DA, autoSL_TA, autoSL_TA_Length);
  }
  else if (m_autoSelected == "Bounce" && !autoBN_Completed)
  {
    std::cout << "BN" << std::endl;
    autoBN_Completed = ReadAndRunCustomAuto(autoBN_SA, autoBN_DA, autoBN_TA, autoBN_TA_Length);
  }
  else if (m_autoSelected == "Autonomous Set Uncompleted")
  {
    basicAutoCompleted = false;
    autoLSC_Completed = false;
    autoBR_Completed = false;
    autoSL_Completed = false;
    autoBN_Completed = false;
  }
  else
  {

  }
  */

  if(!basicAutoCompleted)
  {
    // basicAutoCompleted = ReadAndRunCustomAuto(basicAutoSA, basicAutoDA, basicAutoTA, basicAutoTALength);
  }
  else
  {
    lastAutoTime = currentAutoTime;
  }

  if(!autoLSC_Completed)
  {
    autoLSC_Completed = ReadAndRunCustomAuto(autoLSC_SA, autoLSC_DA, autoLSC_TA, autoLSC_TA_Length);
  }
  else
  {
    lastAutoTime = currentAutoTime;
  }
  
  if(!autoBR_Completed)
  {
    // autoBR_Completed = ReadAndRunCustomAuto(autoBR_SA, autoBR_DA, autoBR_TA, autoBR_TA_Length);
  }
  else
  {
    lastAutoTime = currentAutoTime;
  }

  if(!autoSL_Completed)
  {
    // autoSL_Completed = ReadAndRunCustomAuto(autoSL_SA, autoSL_DA, autoSL_TA, autoSL_TA_Length);
  }
  else
  {
    lastAutoTime = currentAutoTime;
  }

  if(!autoBN_Completed)
  {
    // autoBN_Completed = ReadAndRunCustomAuto(autoBN_SA, autoBN_DA, autoBN_TA, autoBN_TA_Length);
  }
  else
  {
    lastAutoTime = 0;
  }

  if(basicAutoCompleted || autoLSC_Completed || autoBR_Completed || autoSL_Completed || autoBN_Completed)
  {
    if(lastAutoDelayTime + 10 < autoDelayTime)
    {
      basicAutoCompleted = false;
      autoLSC_Completed = false;
      autoBR_Completed = false;
      autoSL_Completed = false;
      autoBN_Completed = false;
    }
  }
  else
  {
    lastAutoDelayTime = autoDelayTime;
  }
}

//Runs once. What the robot does to initiate Teleop
void Robot::TeleopInit()
{
  turret->PrepSmartDashboard();
  turret->ResetRaiseEncoder();

  basicAutoTALength = sizeof(basicAutoTA)/sizeof(basicAutoTA[0]);
  autoLSC_TA_Length = sizeof(autoLSC_TA)/sizeof(autoLSC_TA[0]);
  autoBR_TA_Length = sizeof(autoBR_TA)/sizeof(autoBR_TA[0]);
  autoSL_TA_Length = sizeof(autoSL_TA)/sizeof(autoSL_TA[0]);
  autoBN_TA_Length = sizeof(autoBN_TA)/sizeof(autoBN_TA[0]);
  
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  m_chooser.AddOption("basicAuto", "basicAuto");
  m_chooser.AddOption("Light Speed Circuit", "Light Speed Circuit");
  m_chooser.AddOption("Barrel Racing", "Barrel Racing");
  m_chooser.AddOption("Slalom", "Slalom");
  m_chooser.AddOption("Bounce", "Bounce");
  m_chooser.AddOption("Autonomous Set Uncompleted", "Autonomous Set Uncompleted");
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  frc::SmartDashboard::PutString("AutoString", "AutoString");
}

//What the robot does when we gain controll
void Robot::TeleopPeriodic()
{
  //Loading the classes up to be used. Somewhat like calling a function.
  myMecanumDrive->RunNormalWheels(xboxRX, xboxLY);
  // myMecanumDrive->TankDrive(xboxLY, xboxRY);
  // hanger->RunHanger(yokeUp, yokeDown, yokeLeft, yokeRight);
  manualIntake->RunManualIntake(xboxA, xboxRB, xboxRTrBool);
  
  // autoAim->RunAutoAim(); // TODO
  turret->RunManualTurret(xboxYToggle,xboxLBSwitch);
  turret->RaiseAndLowerTurret(xboxPOV);

  // NOT USING MECANUMS, DO NOT UNCOMMENT THIS FUNCTION
  // myMecanumDrive->RunMecanums(xboxLX, xboxLY, xboxRX);

  //Running a functions that read inputs and sets them to variables to save up resources.
  ReadXbox();
  //ReadYoke();

  // Printing a couple values to the SmartDashboard
  turret->DisplayToSmartDashboard();
  turret->UpdateLimelight();
  
  // m_autoSelected = frc::SmartDashboard::GetString("AutoString", "Default");
  // std::cout << m_autoSelected << std::endl;
  // AutonomousPeriodic();
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

  if(Xbox.GetRawAxis(3) > .2)
  {
    xboxRTrBool = true;
  }
  else
  {
    xboxRTrBool = false;
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

  xboxRY = Xbox.GetRawAxis(5);
  if(xboxRY < .2 && xboxLY > -.2)
  {
    xboxRY = 0;
  }

  xboxPOV = Xbox.GetPOV();
  // std::cout << xboxPOV << std::endl;

  xboxA = Xbox.GetRawButton(1);
  
  if(Xbox.GetRawButtonPressed(4))
  {
    xboxYToggle = !xboxYToggle;
  }

  if(Xbox.GetRawButtonPressed(6))
  {
    xboxRBSwitch = !xboxRBSwitch;
  }

  xboxRB = Xbox.GetRawButton(6);

  if(Xbox.GetRawButtonPressed(5))
  {
    xboxLBSwitch = !xboxLBSwitch;
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

  yokeWheel = Yoke.GetRawAxis(2);

  yokeUp = Yoke.GetRawButton(3);
  yokeDown = Yoke.GetRawButton(2);
  yokeRight = Yoke.GetRawButton(5);
  yokeLeft = Yoke.GetRawButton(4);
}

bool Robot::ReadAndRunCustomAuto(double sArray[], double dArray[], double tArray[], int tArraySize)
{
  std::cout << tArraySize << std::endl;

  myAutoTimer.Start();
  currentAutoTime = myAutoTimer.Get();
  std::cout << currentAutoTime << std::endl;

  if(autonomousIterator > tArraySize)
  {
    autoMecanumSpeed = 0;
    autoMecanumDirection = 0;
    autonomousIterator = 0;
    return true;
  }

  if(autonomousIterator < tArraySize)
  {
    autoMecanumSpeed = sArray[autonomousIterator];
    autoMecanumDirection = dArray[autonomousIterator];
  }
  
  if(currentAutoTime > lastAutoTime + tArray[autonomousIterator])
  {
    lastAutoTime = currentAutoTime;
    autonomousIterator++;
  }

  return false;
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif