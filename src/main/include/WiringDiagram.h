#pragma once

class WiringDiagram {
 public:
  WiringDiagram();

  // Turret
    // PWM
      static const int launcherTopPort = 6;
      static const int launcherBottomPort = 10;

    // DIO
      static const int launcherTopEncoderA = 5;
      static const int launcherTopEncoderB = 6;
      
      static const int launcherBottomEncoderA = 4;
      static const int launcherBottomEncoderB = 3;

    // CAN
      static const int turretRaisePort = 1;
      static const int turretRotatePort = 2;

  // Intake
    // PWM

  // Hanger
    // PWM

    // DIO

  // Mecanum Drive
    // CAN
      static const int wheelFrontLeftPort = 2;
      static const int wheelFrontRightPort = 1;
      static const int wheelBackLeftPort = 3;
      static const int wheelBackRightPort = 4;
};
