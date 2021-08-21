
#include "Turret.h"
#include "WiringDiagram.h"
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/VictorSP.h>
#include <frc/Encoder.h>
#include <frc2/command/PIDCommand.h>
#include <frc2/command/PIDSubsystem.h>
#include <iostream>
#include <frc/Digitalinput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/Timer.h>

ctre::phoenix::motorcontrol::can::WPI_TalonSRX TurretRaise {WiringDiagram::turretRaisePort};
double turretRaiseSetValue = 0;
double lastTurretRaiseSetValue = 0;
ctre::phoenix::motorcontrol::can::WPI_TalonSRX TurretRotate {WiringDiagram::turretRotatePort};
double turretRotateSetValue = 0;
double lastTurretRotateSetValue = 0;

frc::DigitalInput turretRotateLeftLimit {WiringDiagram::leftTurretLimitPort};
frc::DigitalInput turretRotateRightLimit {WiringDiagram::rightTurretLimitPort};

// DEBUG
// frc::DigitalInput TopA {WiringDiagram::launcherTopEncoderA};
// frc::DigitalInput TopB {WiringDiagram::launcherTopEncoderB};

// frc::DigitalInput BottomA {WiringDiagram::launcherBottomEncoderA};
// frc::DigitalInput BottomB {WiringDiagram::launcherBottomEncoderB};

//PWM
frc::VictorSP LauncherTopMotor {WiringDiagram::launcherTopPort};
frc::VictorSP LauncherBottomMotor {WiringDiagram::launcherBottomPort};

// ? BLUE ? Yellow
frc::Encoder LauncherTopEncoder(WiringDiagram::launcherTopEncoderA, 
    WiringDiagram::launcherTopEncoderB, 
    true, frc::CounterBase::EncodingType::k4X);
double launcherTopDistance;
double launcherTopRate;
double kP_Top = 0.06;
double kI_Top = 0.0;
double kD_Top = 0.0;

// ? BLUE ? Yellow 
frc::Encoder LauncherBottomEncoder(WiringDiagram::launcherBottomEncoderA, 
    WiringDiagram::launcherBottomEncoderB, 
    true, frc::CounterBase::EncodingType::k4X);
double launcherBottomDistance;
double launcherBottomRate;
double kP_Bottom = 0.06;
double kI_Bottom = 0.0;
double kD_Bottom = 0.0;

// 14 Blue 15 Yellow
frc::Encoder TurretRaiseEncoder(WiringDiagram::turretRaiseEncoderYellow,
    WiringDiagram::turretRaiseEncoderGreen,
    true, frc::CounterBase::EncodingType::k4X);
double turretRaiseDistance;
double turretRaiseRate;
frc::DigitalInput turretRaiseLimit {WiringDiagram::turretRaiseLimitPort};


// New, Good PID
frc2::PIDController turretTopPID(kP_Top, kI_Top, kD_Top);
frc2::PIDController turretBottomPID(kP_Bottom, kI_Bottom, kD_Bottom);

double kP_Raise = 1;
double kI_Raise = 0.2;
double kD_Raise = 0.1;
double turretRaiseDistanceSet = 0;
frc2::PIDController turretRaisePID(kP_Raise, kI_Raise, kD_Raise);

double kP_Rotate = .05;
double kI_Rotate = 0;
double kD_Rotate = 0;
frc2::PIDController turretRotatePID(kP_Rotate, kI_Rotate, kD_Rotate);

int averageCount = 0;
double averageTemporary = 0;
double averageSpeed = 0;

double topSetValue = 0;
int topSetpoint = -3500;
double topRate = 0;

double bottomSetValue = 0;
int bottomSetpoint = 2500;
double bottomRate = 0;

bool limelightDetected = false;
double limelightXOffset = 0;
double limelightYOffset = 0;

frc::Timer myTimer;
long double currentTime = 0;
long double lastRotateDirectionFlipTime = 0;
long double lastRaiseDirectionFlipTime = 0;

Turret::Turret()
{
    // Setting required values for Top Encoder
    LauncherTopEncoder.SetDistancePerPulse(1./33.5051125);
    LauncherTopEncoder.SetMaxPeriod(.1);

    // Setting required values for Bottom Encoder
    LauncherBottomEncoder.SetDistancePerPulse(1./33.5051125);
    LauncherBottomEncoder.SetMaxPeriod(.1);

    // Setting required values for Raise Encoder
    TurretRaiseEncoder.SetDistancePerPulse(1/134.4);
    TurretRaiseEncoder.SetMaxPeriod(1);

    // Setting required values for Top PID
    turretTopPID.SetTolerance(50);
    turretBottomPID.SetTolerance(50);

    turretRotatePID.SetTolerance(.25);
    turretRaisePID.SetTolerance(.06);
}

void Turret::RunAutoTurret()
{

}

void Turret::RunManualTurret(bool xboxYToggle, bool xboxLBSwitch)
{
    myTimer.Start();
    currentTime = myTimer.Get();

    if(xboxLBSwitch)
    {
        double tempOne = limelightYOffset + 7;
        double tempTwo = tempOne * tempOne;
        RunRaisePID(-0.005 * tempTwo + 3.65);
        // RunRaisePID(turretRaiseDistanceSet);
        RunRotatePID();   
        nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 0);
    }
    else
    {
        TurretRaise.Set(0);
        TurretRotate.Set(0);
        nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 0);
    }

    if(xboxYToggle)
    {
        topRate = LauncherTopEncoder.GetRate();
        bottomRate = LauncherBottomEncoder.GetRate();

        // PersonalProportional();

        turretTopPID.SetPID(kP_Top, kI_Top, kD_Top);
        turretBottomPID.SetPID(kP_Bottom, kI_Bottom, kD_Bottom);
        turretRaisePID.SetPID(kP_Raise, kI_Raise, kD_Raise);
        turretRotatePID.SetPID(kP_Rotate, kI_Rotate, kD_Rotate);
        PIDControll();

        // Debug

        averageTemporary = averageTemporary + LauncherBottomEncoder.GetRate();
        averageCount++;
        if(averageCount >= 100) {
            averageSpeed = averageTemporary / averageCount;
            averageCount = 0;
            averageTemporary = 0;
        }

        // LauncherTopMotor.Set(-1);
        // LauncherBottomMotor.Set(1);
    }
    else
    {
        LauncherTopMotor.Set(0);
        LauncherBottomMotor.Set(0);

        turretTopPID.Reset();
        turretBottomPID.Reset();
    }
}

void Turret::RaiseAndLowerTurret(int xboxPOV)
{
    // if(xboxPOV == 0)
    // {
        // TurretRaise.Set(0);
        // TurretRotate.Set(0);
    // }
}

bool Turret::Aim()
{
    return false;
}

double Turret::ProportionalController(double inputValue, double percentSpeed, double setpoint, double sensitivity)
{
    double percentError = (setpoint - inputValue) / abs(setpoint);
    return percentSpeed + percentError * sensitivity;
}

void Turret::PIDControll()
{
    turretTopPID.SetSetpoint(topSetpoint);
    double temporaryTop = turretTopPID.Calculate(topRate);
    topSetValue += temporaryTop;
        if(topSetValue > 0)
        {
            topSetValue = 0;
        }
        if(topSetValue < -1)
        {
            topSetValue = -1;
        }
    LauncherTopMotor.Set(topSetValue);

    turretBottomPID.SetSetpoint(bottomSetpoint);
    double temporaryBottom = turretBottomPID.Calculate(bottomRate);
    bottomSetValue += temporaryBottom;
        if(bottomSetValue < 0)
        {
            bottomSetValue = 0;
        }
        if(bottomSetValue > 1)
        {
            bottomSetValue = 1;
        }
    LauncherBottomMotor.Set(bottomSetValue);
}

void Turret::PersonalProportional()
{
    topSetValue = ProportionalController(topRate, topSetValue, topSetpoint, kP_Top);
        if(topSetValue > 0)
        {
            topSetValue = 0;
        }
        if(topSetValue < -1)
        {
            topSetValue = -1;
        }

    bottomSetValue = ProportionalController(bottomRate, bottomSetValue, bottomSetpoint, kP_Bottom);
        if(bottomSetValue < 0)
        {
            bottomSetValue = 0;
        }
        if(bottomSetValue > 1)
        {
            bottomSetValue = 1;
        }

    LauncherTopMotor.Set(topSetValue);
    LauncherBottomMotor.Set(bottomSetValue);

    // std::cout << "Top Rate: " << topSetValue << " :: " << topRate << std::endl;
    // std::cout << "Bottom Rate: " << bottomSetValue << " :: " << bottomRate << std::endl;
}

void Turret::ResetRaiseEncoder()
{
    while(turretRaiseLimit.Get())
    {
        TurretRaise.Set(0.6);
    }
    TurretRaise.Set(0);
    TurretRaiseEncoder.Reset();
}

void Turret::RunRaisePID(double distanceRotations)
{
    turretRaisePID.SetPID(kP_Raise, kI_Raise, kD_Raise);
    
    turretRaiseDistance = TurretRaiseEncoder.GetDistance();
    turretRaisePID.SetSetpoint(distanceRotations);
    turretRaiseSetValue = -turretRaisePID.Calculate(turretRaiseDistance);
        if(turretRaiseSetValue > 1)
        {
            turretRaiseSetValue = 1;
        }
        if(turretRaiseSetValue < -1)
        {
            turretRaiseSetValue = -1;
        }
        if(!turretRaiseLimit.Get() || turretRaiseDistance < .25)
        {
            if(turretRaiseSetValue > 0)
            {
                turretRaiseSetValue = 0;
            }
        }
        
        TurretRaise.Set(turretRaiseSetValue);

        // if(currentTime > lastRaiseDirectionFlipTime + .1)
        // {
            // if(lastTurretRaiseSetValue > 0 && turretRaiseSetValue > 0)
            // {
            //     TurretRaise.Set(turretRaiseSetValue);
            //     lastTurretRaiseSetValue = turretRaiseSetValue;
            // }
            // else if(lastTurretRaiseSetValue < 0 && turretRaiseSetValue < 0)
            // {
            //     TurretRotate.Set(turretRaiseSetValue);
            //     lastTurretRaiseSetValue = turretRaiseSetValue;
            // }
            // else
            // {
            //     lastTurretRaiseSetValue = turretRaiseSetValue;
            //     lastRaiseDirectionFlipTime = currentTime;
            // }
        // }
        // else
        // {
            // TurretRaise.Set(0);
        // }
        
}

void Turret::RunRotatePID()
{
    if(limelightDetected)
    {
        turretRotatePID.SetSetpoint(1.5);
        turretRotateSetValue = turretRotatePID.Calculate(limelightXOffset);
            if(turretRotateSetValue > .2)
            {
                turretRotateSetValue = .2;
            }
            if(turretRotateSetValue < -.2)
            {
                turretRotateSetValue = -.2;
            }
            if(!turretRotateLeftLimit.Get())
            {
                if(turretRotateSetValue > 0)
                {
                    turretRotateSetValue = 0;
                }
            }
            if(!turretRotateRightLimit.Get())
            {
                if(turretRotateSetValue < 0)
                {
                    turretRotateSetValue = 0;
                }
            }

            
            TurretRotate.Set(turretRotateSetValue);
    
        // if(currentTime > lastRotateDirectionFlipTime + .1)
        // {
            // if(lastTurretRotateSetValue > 0 && turretRotateSetValue > 0)
            // {
            //     lastTurretRotateSetValue = turretRotateSetValue;
            // }
            // else if(lastTurretRotateSetValue < 0 && turretRotateSetValue < 0)
            // {
            //     TurretRotate.Set(turretRotateSetValue);
            //     lastTurretRotateSetValue = turretRotateSetValue;
            // }
            // else
            // {
            //     lastTurretRotateSetValue = turretRotateSetValue;
            //     lastRotateDirectionFlipTime = currentTime;
            // }
        // }
        // else
        // {
            // TurretRotate.Set(0);
        // }
        
    }
}

void Turret::DisplayToSmartDashboard()
{
    frc::SmartDashboard::PutNumber("Top Rate", topRate);
    frc::SmartDashboard::PutNumber("Bottom Rate", bottomRate);

    frc::SmartDashboard::PutNumber("Top Set Value", topSetValue);
    frc::SmartDashboard::PutNumber("Bottom Set Value", bottomSetValue);

    frc::SmartDashboard::PutNumber("Turret Raise Limit", turretRaiseLimit.Get());
    frc::SmartDashboard::PutNumber("Turret Left Limit", turretRotateLeftLimit.Get());
    frc::SmartDashboard::PutNumber("Turret Right Limit", turretRotateRightLimit.Get());

    frc::SmartDashboard::PutBoolean("Limelight Detected", limelightDetected);
    frc::SmartDashboard::PutNumber("X Offset", limelightXOffset);
    frc::SmartDashboard::PutNumber("Y Offset", limelightYOffset);

    topSetpoint = frc::SmartDashboard::GetNumber("Top Setpoint", topSetpoint);
    bottomSetpoint = frc::SmartDashboard::GetNumber("Bottom Setpoint", bottomSetpoint);

    kP_Top = frc::SmartDashboard::GetNumber("kP Top", kP_Top);
    kI_Top = frc::SmartDashboard::GetNumber("kI Top", kI_Top);
    kD_Top = frc::SmartDashboard::GetNumber("kD Top", kD_Top);

    kP_Bottom = frc::SmartDashboard::GetNumber("kP Bottom", kP_Bottom);
    kI_Bottom = frc::SmartDashboard::GetNumber("kI Bottom", kI_Bottom);
    kD_Bottom = frc::SmartDashboard::GetNumber("kD Bottom", kD_Bottom);

    kP_Raise = frc::SmartDashboard::GetNumber("kP Raise", kP_Raise);
    kI_Raise = frc::SmartDashboard::GetNumber("kI Raise", kI_Raise);
    kD_Raise = frc::SmartDashboard::GetNumber("kD Raise", kD_Raise);
    frc::SmartDashboard::PutNumber("Raise Distance", TurretRaiseEncoder.GetDistance());
    turretRaiseDistanceSet = frc::SmartDashboard::GetNumber("Raise Set Distance", turretRaiseDistanceSet);

    kP_Rotate = frc::SmartDashboard::GetNumber("kP Rotate", kP_Rotate);
    kI_Rotate = frc::SmartDashboard::GetNumber("kI Rotate", kI_Rotate);
    kD_Rotate = frc::SmartDashboard::GetNumber("kD Rotate", kD_Rotate);
    frc::SmartDashboard::PutNumber("Rotate Set Value", turretRotateSetValue);

    frc::SmartDashboard::PutNumber("Raise Set Value", turretRaiseSetValue);
    int LEDMode = frc::SmartDashboard::GetNumber("Limelight LED Mode", 0);
    // nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", LEDMode);
}

void Turret::PrepSmartDashboard()
{
    frc::SmartDashboard::PutNumber("Top Rate", topRate);
    frc::SmartDashboard::PutNumber("Bottom Rate", bottomRate);

    frc::SmartDashboard::PutNumber("Top Setpoint", topSetpoint);
    frc::SmartDashboard::PutNumber("Bottom Setpoint", bottomSetpoint);
    
    frc::SmartDashboard::PutNumber("Turret Raise Limit", turretRaiseLimit.Get());
    frc::SmartDashboard::PutNumber("Turret Raise Limit", turretRotateLeftLimit.Get());
    frc::SmartDashboard::PutNumber("Turret Raise Limit", turretRotateRightLimit.Get());

    frc::SmartDashboard::PutBoolean("Limelight Detected", limelightDetected);
    frc::SmartDashboard::PutNumber("X Offset", limelightXOffset);
    frc::SmartDashboard::PutNumber("Y Offset", limelightYOffset);

    frc::SmartDashboard::PutNumber("kP Top", kP_Top);
    frc::SmartDashboard::PutNumber("kI Top", kI_Top);
    frc::SmartDashboard::PutNumber("kD Top", kD_Top);

    frc::SmartDashboard::PutNumber("kP Bottom", kP_Bottom);
    frc::SmartDashboard::PutNumber("kI Bottom", kI_Bottom);
    frc::SmartDashboard::PutNumber("kD Bottom", kD_Bottom);

    frc::SmartDashboard::PutNumber("kP Raise", kP_Raise);
    frc::SmartDashboard::PutNumber("kI Raise", kI_Raise);
    frc::SmartDashboard::PutNumber("kD Raise", kD_Raise);
    frc::SmartDashboard::PutNumber("Raise Distance", turretRaiseDistance);
    frc::SmartDashboard::PutNumber("Raise Set Distance", turretRaiseDistanceSet);
    
    frc::SmartDashboard::PutNumber("kP Rotate", kP_Rotate);
    frc::SmartDashboard::PutNumber("kI Rotate", kI_Rotate);
    frc::SmartDashboard::PutNumber("kD Rotate", kD_Rotate);
    frc::SmartDashboard::PutNumber("Rotate Set Value", turretRotateSetValue);

    frc::SmartDashboard::PutNumber("Raise Set Value", turretRaiseSetValue);

    frc::SmartDashboard::PutNumber("Top Set Value", topSetValue);
    frc::SmartDashboard::PutNumber("Bottom Set Value", bottomSetValue);

    frc::SmartDashboard::PutNumber("Limelight LED Mode", 0);

    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline",1);
}

void Turret::UpdateLimelight()
{
    limelightDetected = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv",0.0);
    limelightXOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0);
    limelightYOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0);
}