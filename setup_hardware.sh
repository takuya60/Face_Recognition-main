#!/bin/sh
echo "--- 正在初始化硬件接口 ---"

LED_PATH="/sys/class/leds/sys-led"
PWM_PATH="/sys/class/pwm/pwmchip1/pwm0"

# 1. 导出 GPIO 3 (用于 LED)
if [ ! -d /sys/class/gpio/gpio3 ]; then
    echo "none" > $LED_PATH/trigger
    echo 0 > $LED_PATH/brightness
fi

echo "---  PWM ($PWM_PATH) ---"

if [ ! -d "$PWM_PATH" ]; then
    echo 0 > /sys/class/pwm/pwmchip1/export
    sleep 0.1
fi

echo "PWM 处于禁用状态"

# 确保 PWM 处于禁用状态
echo 0 > $PWM_PATH/enable


echo "周期"

# 设置周期 (20ms)
echo 20000000 > $PWM_PATH/period

# 设置初始占空比 (1.5ms, "停止"状态)
echo 1500000 > $PWM_PATH/duty_cycle

# 设置极性
echo "normal" > $PWM_PATH/polarity

echo "启用"
# 启用 PWM
echo 1 > $PWM_PATH/enable

echo "--- 硬件初始化完成 ---"