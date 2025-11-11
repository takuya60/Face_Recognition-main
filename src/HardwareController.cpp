#include "HardwareController.h"

HardwareController::HardwareController()
{

}

HardwareController::~HardwareController()
{

}

void HardwareController::triggerSuccessSequence(const std::string&name)
{
    if (m_hardwareMutex.try_lock())
    {
        std::thread(&HardwareController::runSuccessSequence,this,name).detach();
    }
    else
    {
        std::cout<< "[Hardware] Hardware is busy. Ignoring trigger." << std::endl;
    }
}

void HardwareController::runSuccessSequence(std::string name)
{
    try
    {
        //LED
        std::cout << "[Hardware] LED On" << std::endl;
        

        //语音
        std::cout << "[Hardware] Playing 'Success' sound for " << name << std::endl;
        std::string cmd = "aplay /mnt/tf/sounds/success.wav";
        system(cmd.c_str());

        //舵机
        std::cout << "[Hardware] Servo Open" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));

        //舵机和LED灭
        std::cout << "[Hardware] Servo Close & LED Off" << std::endl;
    }
    catch(...)
    {
        std::cerr << "[Hardware] Exception in hardware thread!" << std::endl;
    }

    m_hardwareMutex.unlock();

}