#pragma once

#include <string>
#include <mutex> // (我们将在这里管理线程安全)
#include <thread>
#include <chrono>
#include <cstdlib> // (用于 system())
#include <iostream>

class HardwareController
{
public:
    HardwareController();
    ~HardwareController();

    void triggerSuccessSequence(const std::string& name);
private:
    /**
     * @brief (私有) 真正执行硬件操作的函数
     * (这个函数将在 *它自己* 的 std::thread 中运行)
     */
    void runSuccessSequence(std::string name);

    std::mutex m_hardwareMutex;
};

