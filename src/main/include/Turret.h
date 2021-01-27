
#pragma once

class Turret
{
 public:
  Turret();
  void RunAutoTurret();
  void RunManualTurret(bool xboxYToggle);
  bool Aim();
};
