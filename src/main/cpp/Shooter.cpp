/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shooter.h"
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/controller/PIDController.h>
#include <frc/Encoder.h>

frc::Encoder ShooterTopEncoder(10, 12, false, frc::CounterBase::EncodingType::k4X);
int ShooterTopDistance = 0;
int ShooterTopRate = 0;

frc::Encoder ShooterBottomEncoder(15, 16, false, frc::CounterBase::EncodingType::k4X);
int ShooterBottomDistance = 0;
int ShooterBottomRate = 0;

frc::Encoder ShooterRaiseEncoder(17, 18, false, frc::CounterBase::EncodingType::k4X);
int ShooterRaiseDistance = 0;
int ShooterRaiseRate = 0;

frc::controller::PIDController::PIDController shooterTopPID(0, 0, 0, 20_ms);
frc::controller::PIDController::PIDController shooterBottomPID(0, 0, 0, 20_ms);

Shooter::Shooter()
{

}

void Shooter::RunShooter()
{

}