
#include "AutoShooter.h"
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/Encoder.h>
#include <frc2/command/PIDCommand.h>
#include <frc2/command/PIDSubsystem.h>

ctre::phoenix::motorcontrol::can::WPI_TalonSRX ShooterTop {1};
ctre::phoenix::motorcontrol::can::WPI_TalonSRX ShooterBottom {2};

frc::Encoder ShooterTopEncoder(10, 12, false, frc::CounterBase::EncodingType::k4X);
int shooterTopDistance;
int shooterTopRate;

frc::Encoder ShooterBottomEncoder(15, 16, false, frc::CounterBase::EncodingType::k4X);
int shooterBottomDistance;
int shooterBottomRate;

frc::Encoder ShooterRaiseEncoder(17, 18, false, frc::CounterBase::EncodingType::k4X);
int shooterRaiseDistance;
int shooterRaiseRate;

// New, Good PID
frc2::PIDController shooterTopPID(.1, .1, .1);
frc2::PIDController shooterBottomPID(.1, .1, .1);

AutoShooter::AutoShooter()
{

}

void AutoShooter::RunAutoShooter()
{

}