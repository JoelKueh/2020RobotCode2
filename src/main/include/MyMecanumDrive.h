
#pragma once

class MyMecanumDrive 
{
 private:

 public:
  MyMecanumDrive();
  void RunMecanums(double xboxLX, double xboxLY, double xboxRX);
  void RunNormalWheels(double xboxLX, double xboxLY);
  void TankDrive(double xboxLY, double xboxRY);
};
