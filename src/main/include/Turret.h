
#pragma once

class Turret
{
 public:
  Turret();
  void RunAutoTurret();
  void RunManualTurret(bool xboxYToggle);
  bool Aim();
  void RaiseAndLowerTurret(int xboxPOV);
  void DisplayToSmartDashboard();
  void PrepSmartDashboard();
  void ResetRaiseEncoder();
  void RunRaisePID(double distanceRotations);
  void RunRotatePID();
  void UpdateLimelight();

 private:
  double ProportionalController(double input, double percentSpeed, double setpoint, double sensitivity);
  void PIDControll();
  void PersonalProportional();
};
