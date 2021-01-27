
#include "Turret.h"
#include "WiringDiagram.h"
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/VictorSP.h>
#include <frc/Encoder.h>
#include <frc2/command/PIDCommand.h>
#include <frc2/command/PIDSubsystem.h>
#include <iostream>
#include <frc/Digitalinput.h>

WiringDiagram *wiringDiagram;

//ctre::phoenix::motorcontrol::can::WPI_TalonSRX TurretRaise {turretRaisePort};
//ctre::phoenix::motorcontrol::can::WPI_TalonSRX TurretRotate {turretRotatePort};

// DEBUG
frc::DigitalInput TopA {wiringDiagram->launcherTopEncoderA};
frc::DigitalInput TopB {WiringDiagram::launcherTopEncoderB};

frc::DigitalInput BottomA {WiringDiagram::launcherBottomEncoderA};
frc::DigitalInput BottomB {WiringDiagram::launcherBottomEncoderB};

//PWM
frc::VictorSP LauncherTopMotor {WiringDiagram::launcherTopPort};
frc::VictorSP LauncherBottomMotor {WiringDiagram::launcherBottomPort};

// 5 BLUE 6 Yellow
// frc::Encoder LauncherTopEncoder(WiringDiagram::launcherTopEncoderA, 
//     WiringDiagram::launcherTopEncoderB, 
//     true, frc::CounterBase::EncodingType::k2X);

int launcherTopDistance;
int launcherTopRate;

// 0 BLUE 1 Yellow 
// frc::Encoder LauncherBottomEncoder(WiringDiagram::launcherBottomEncoderA, 
//     WiringDiagram::launcherBottomEncoderB, 
//     true, frc::CounterBase::EncodingType::k2X);

int launcherBottomDistance;
int launcherBottomRate;

// 14 Blue 15 Yellow
frc::Encoder TurretRaiseEncoder(14, 15, true, frc::CounterBase::EncodingType::k4X);
int turretRaiseDistance;
int turretRaiseRate;

// New, Good PID
frc2::PIDController turretTopPID(.1, .1, .1);
frc2::PIDController turretBottomPID(.1, .1, .1);

Turret::Turret()
{
    //Setting required values for Top Encoder
    // LauncherTopEncoder.SetDistancePerPulse(4./256.);
    // LauncherTopEncoder.SetMaxPeriod(.1);
    // LauncherTopEncoder.SetMinRate(1);

    //Setting required values for Bottom Encoder
    // LauncherBottomEncoder.SetDistancePerPulse(1.);
    // LauncherBottomEncoder.SetMaxPeriod(.1);
    // LauncherBottomEncoder.SetMinRate(1);
}

void Turret::RunAutoTurret()
{

}

void Turret::RunManualTurret(bool xboxYToggle)
{
    if(xboxYToggle)
    {
        //LauncherTop.Set(launcherTopPID.Calculate(launcherTopEncoder.GetDistance(), 5));
        LauncherTopMotor.Set(-.30);
        
        // Debug
        // std::cout << "Raw Top: " << LauncherTopEncoder.GetRaw() << std::endl;
        // std::cout << "Distance Top: " << LauncherTopEncoder.GetDistance() << std::endl;
        // std::cout << "Get Top: " << LauncherTopEncoder.Get() << std::endl;
        // std::cout << "Get Distance Per Pulse Top: " << LauncherTopEncoder.GetDistancePerPulse() << std::endl;

        std::cout << "Top A: " << WiringDiagram::launcherTopPort << std::endl;
        std::cout << "Top B: " << TopB.GetChannel() << std::endl;

        LauncherBottomMotor.Set(.30);

        // DEBUG
        // std::cout << "Raw Bottom: " << LauncherBottomEncoder.GetRaw() << std::endl;
        // std::cout << "Distance Bottom: " << LauncherBottomEncoder.GetDistance() << std::endl;
        // std::cout << "Get Bottom: " << LauncherBottomEncoder.Get() << std::endl;
        // std::cout << "Get Distance Per Pulse Bottom: " << LauncherBottomEncoder.GetDistancePerPulse() << std::endl;

        std::cout << "Bottom A: " << BottomA.GetChannel() << std::endl;
        std::cout << "Bottom B: " << BottomB.GetChannel() << std::endl;
    }
    else
    {
        //LauncherTopMotor.Set(launcherTopPID.Calculate(LauncherTopEncoder.GetDistance(), 0));
        LauncherTopMotor.Set(0);
        LauncherBottomMotor.Set(0);
        
        //std::cout << LauncherTopEncoder.GetStopped() << std::endl;
        //sstd::cout << LauncherBottomEncoder.Get() << std::endl;
    }
}

bool Turret::Aim()
{
    return false;
}