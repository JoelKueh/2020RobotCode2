
#pragma once

class Turret
{
 public:
  Turret();
  void RunAutoTurret();
  void RunManualTurret(bool xboxYToggle);
  bool Aim();

 private:
  double ProportionalController(double input, double percentSpeed, double setpoint, double sensitivity);
  void PIDControll();
  void PersonalProportional();
};
