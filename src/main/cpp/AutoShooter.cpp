
#include "AutoShooter.h"
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/PIDController.h>
#include <frc/PIDBase.h>
#include <frc/PIDSource.h>
#include <frc/PIDInterface.h>
#include <frc/PIDOutput.h>
#include <frc/Encoder.h>

ctre::phoenix::motorcontrol::can::WPI_TalonSRX ShooterTop;
ctre::phoenix::motorcontrol::can::WPI_TalonSRX ShooterBottom;

frc::Encoder ShooterTopEncoder(10, 12, false, frc::CounterBase::EncodingType::k4X);
int shooterTopDistance;
int shooterTopRate;

frc::Encoder ShooterBottomEncoder(15, 16, false, frc::CounterBase::EncodingType::k4X);
int shooterBottomDistance;
int shooterBottomRate;

frc::Encoder ShooterRaiseEncoder(17, 18, false, frc::CounterBase::EncodingType::k4X);
int shooterRaiseDistance;
int shooterRaiseRate;

frc::PIDController shooterTopPID(.8, .1, .1, ShooterTopEncoder, ShooterTop);
frc::PIDController shooterBottomPID(.8, .1, .1, ShooterBottomEncoder, ShooterBottom);

AutoShooter::AutoShooter()
{

}

void AutoShooter::RunAutoShooter()
{

}