
#include "Turret.h"
#include "WiringDiagram.h"
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/VictorSP.h>
#include <frc/Encoder.h>
#include <frc2/command/PIDCommand.h>
#include <frc2/command/PIDSubsystem.h>
#include <iostream>
#include <frc/Digitalinput.h>

//ctre::phoenix::motorcontrol::can::WPI_TalonSRX TurretRaise {turretRaisePort};
//ctre::phoenix::motorcontrol::can::WPI_TalonSRX TurretRotate {turretRotatePort};

// DEBUG
// frc::DigitalInput TopA {WiringDiagram::launcherTopEncoderA};
// frc::DigitalInput TopB {WiringDiagram::launcherTopEncoderB};

// frc::DigitalInput BottomA {WiringDiagram::launcherBottomEncoderA};
// frc::DigitalInput BottomB {WiringDiagram::launcherBottomEncoderB};

//PWM
frc::VictorSP LauncherTopMotor {WiringDiagram::launcherTopPort};
frc::VictorSP LauncherBottomMotor {WiringDiagram::launcherBottomPort};

// 5 BLUE 6 Yellow
frc::Encoder LauncherTopEncoder(WiringDiagram::launcherTopEncoderA, 
    WiringDiagram::launcherTopEncoderB, 
    true, frc::CounterBase::EncodingType::k4X);

int launcherTopDistance;
int launcherTopRate;

// 0 BLUE 1 Yellow 
frc::Encoder LauncherBottomEncoder(WiringDiagram::launcherBottomEncoderA, 
    WiringDiagram::launcherBottomEncoderB, 
    false, frc::CounterBase::EncodingType::k4X);

int launcherBottomDistance;
int launcherBottomRate;

// 14 Blue 15 Yellow
frc::Encoder TurretRaiseEncoder(14, 15, true, frc::CounterBase::EncodingType::k4X);
int turretRaiseDistance;
int turretRaiseRate;

// New, Good PID
frc2::PIDController turretTopPID(1, 0, 0);
frc2::PIDController turretBottomPID(1, 0, 0);

int averageCount = 0;
double averageTemporary = 0;
double averageSpeed = 0;

Turret::Turret()
{
    //Setting required values for Top Encoder
    LauncherTopEncoder.SetDistancePerPulse(1./33.5051125);
    LauncherTopEncoder.SetMaxPeriod(.1);
    LauncherTopEncoder.SetMinRate(1);

    //Setting required values for Bottom Encoder
    LauncherBottomEncoder.SetDistancePerPulse(1./33.5051125);
    LauncherBottomEncoder.SetMaxPeriod(.1);
    LauncherBottomEncoder.SetMinRate(1);

    //Setting required values for Top PID
    turretTopPID.SetTolerance(50);

    turretBottomPID.SetTolerance(50);
}

void Turret::RunAutoTurret()
{

}

void Turret::RunManualTurret(bool xboxYToggle)
{
    if(xboxYToggle)
    {
        turretTopPID.SetSetpoint(3000);
        double temporaryTop = turretTopPID.Calculate(LauncherTopEncoder.GetRate()) / 100;
        LauncherTopMotor.Set(temporaryTop);
        std::cout << "Get Top PID: " << temporaryTop << std::endl;

        turretBottomPID.SetSetpoint(3000);
        double temporaryBottom = turretBottomPID.Calculate(LauncherBottomEncoder.GetRate()) / 100;
        LauncherBottomMotor.Set(temporaryBottom);
        std::cout << "Get Bottom PID: " << temporaryBottom << std::endl;

        averageTemporary = averageTemporary + LauncherBottomEncoder.GetRate();
        averageCount++;
        if(averageCount >= 100) {
            averageSpeed = averageTemporary / averageCount;
            averageCount = 0;
            averageTemporary = 0;
        }
        
        // Debug
        // std::cout << "Raw Top: " << LauncherTopEncoder.GetRaw() << std::endl;
        // std::cout << "Distance Top: " << LauncherTopEncoder.GetDistance() << std::endl;
        // std::cout << "Get Top: " << averageSpeed << std::endl;
        // std::cout << "Get Distance Per Pulse Top: " << LauncherTopEncoder.GetDistancePerPulse() << std::endl;

        // std::cout << "Top A: " << TopA.Get() << std::endl;
        // std::cout << "Top B: " << TopB.Get() << std::endl;

        // LauncherBottomMotor.Set(.30);

        // DEBUG
        // std::cout << "Raw Bottom: " << LauncherBottomEncoder.GetRaw() << std::endl;
        // std::cout << "Distance Bottom: " << LauncherBottomEncoder.Get() << std::endl;
        // std::cout << "Get Bottom: " << LauncherBottomEncoder.GetRate() << std::endl;
        // std::cout << "Get Distance Per Pulse Bottom: " << LauncherBottomEncoder.GetDistancePerPulse() << std::endl;

        // std::cout << "Bottom A: " << BottomA.GetChannel() << std::endl;
        // std::cout << "Bottom B: " << BottomB.GetChannel() << std::endl;
    }
    else
    {
        //LauncherTopMotor.Set(launcherTopPID.Calculate(LauncherTopEncoder.GetDistance(), 0));
        LauncherTopMotor.Set(0);
        LauncherBottomMotor.Set(0);
        
        // std::cout << "Get Top: " << LauncherTopEncoder.GetRate() << std::endl;
        
        // std::cout << LauncherTopEncoder.GetStopped() << std::endl;
        //sstd::cout << LauncherBottomEncoder.Get() << std::endl;
    }
}

bool Turret::Aim()
{
    return false;
}