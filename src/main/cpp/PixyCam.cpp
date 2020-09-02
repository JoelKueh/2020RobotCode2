#include "PixyCam.h"
#include <frc/SerialPort.h>
#include <iostream>

static constexpr auto usb = frc::SerialPort::Port::kUSB;
frc::SerialPort PixyCamPort {9600, usb};
std::string PixyCamStr = "";
char PixyArray [80];
char PixyArrayOutput [1];
int pixyCamX = 0;
int pixyCamY = 0;
bool inputFinished = false;

PixyCam::PixyCam() {}

void PixyCam::GetStr()
{
    if(!inputFinished)
    {
        int size = PixyCamPort.Read(PixyArray, 80);
        PixyCamStr.clear();
        for(int i = 0; i < size; i++) 
        {
            PixyCamStr += PixyArray[i];
            if(PixyArray[i] == '\n')
            {
                PixyCamPort.Write(PixyArrayOutput, 1);
                PixyCamPort.Flush();
                inputFinished = true;
            }
        }
    }
    std::cout << PixyCamStr;
}

bool PixyCam::InputFinished()
{
    return inputFinished;
}

void PixyCam::ClearPixyStr()
{
    PixyCamStr.clear();
    inputFinished = false;
}

int PixyCam::GetValY()
{
    return pixyCamY;
}

int PixyCam::GetValX()
{
    return pixyCamX;
}