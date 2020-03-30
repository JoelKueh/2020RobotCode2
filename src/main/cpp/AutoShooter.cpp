
#include "AutoShooter.h"
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/PIDController.h>
#include <frc/PIDBase.h>
#include <frc/PIDSource.h>
#include <frc/PIDInterface.h>
#include <frc/PIDOutput.h>
#include <frc/Encoder.h>

ctre::phoenix::motorcontrol::can::WPI_VictorSPX ShooterTop;
ctre::phoenix::motorcontrol::can::WPI_VictorSPX ShooterBottom;

frc::Encoder ShooterTopEncoder(10, 12, false, frc::CounterBase::EncodingType::k4X);
int shooterTopDistance = 0;
int shooterTopRate = 0;

frc::Encoder ShooterBottomEncoder(15, 16, false, frc::CounterBase::EncodingType::k4X);
int shooterBottomDistance = 0;
int shooterBottomRate = 0;

frc::Encoder ShooterRaiseEncoder(17, 18, false, frc::CounterBase::EncodingType::k4X);
int shooterRaiseDistance = 0;
int shooterRaiseRate = 0;

frc::PIDController ShooterTopPID(.8, 0.1, 0.1, .1, ShooterTopEncoder.GetDistance(), ShooterTop);
frc::PIDController ShooterBottomPID(8, 0.1, 0.1, .1, ShooterBottomEncoder.GetDistance(), ShooterBottom);

AutoShooter::AutoShooter() {}

void AutoShooter::RunAutoShooter()
{

}