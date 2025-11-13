#include "HardwareController.h"

HardwareController::HardwareController()
{

}

HardwareController::~HardwareController()
{

}

void HardwareController::triggerSuccessSequence(int person_id)
{
    if (m_hardwareMutex.try_lock())
    {
        std::thread(&HardwareController::runSuccessSequence,this,person_id).detach();
    }
    else
    {
        std::cout<< "[Hardware] Hardware is busy. Ignoring trigger." << std::endl;
    }
}

void HardwareController::runSuccessSequence(int person_id)
{
    try
    {
        //LED
        //std::cout << "[Hardware] LED On" << std::endl;
        

        //语音


        if (person_id==24)
        {
        std::cout << "老大我想你了 " << std::endl;
        std::string cmd = "aplay /mnt/tf/sounds/manbaout.WAV";
        system(cmd.c_str());
        }

        else if (person_id==17)
        {
        std::cout << "当网红稳了 " << std::endl;
        std::string cmd = "aplay /mnt/tf/sounds/wang.WAV";
        system(cmd.c_str());
        }
        else
        {
        std::cout << "[Hardware] Playing 'Success' sound  " << std::endl;
        std::string cmd = "aplay /mnt/tf/sounds/man.WAV";
        system(cmd.c_str());
        }

        //舵机
        //std::cout << "[Hardware] Servo Open" << std::endl;
        //std::this_thread::sleep_for(std::chrono::seconds(3));

        //舵机和LED灭
        //std::cout << "[Hardware] Servo Close & LED Off" << std::endl;
    }
    catch(...)
    {
        std::cerr << "[Hardware] Exception in hardware thread!" << std::endl;
    }

    m_hardwareMutex.unlock();

}