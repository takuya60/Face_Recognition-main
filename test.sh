# !/bin/sh

echo "开始测试舵机"

PWM_PATH="/sys/class/pwm/pwmchip1/pwm0"
LED_BRIGHTNESS_FILE="/sys/class/leds/sys-led/brightness"

echo "正转"
echo 1800000 >$PWM_PATH/duty_cycle
sleep 3

echo "停止"
echo 1500000 > $PWM_PATH/duty_cycle
sleep 2

echo "反转"
echo 1200000 > $PWM_PATH/duty_cycle
sleep 3

echo 1500000 > $PWM_PATH/duty_cycle

if [ -f "$LED_BRIGHTNESS_FILE" ]; then
    # 1. 点亮 LED
    echo "LED点亮"
    # 修正：写入 brightness 文件
    echo 1 > $LED_BRIGHTNESS_FILE
    sleep 3
    
    # 2. 熄灭 LED
    echo "LED熄灭"
    # 修正：写入 brightness 文件
    echo 0 > $LED_BRIGHTNESS_FILE
else
    echo "--- 错误: 找不到 LED 控制文件: $LED_BRIGHTNESS_FILE ---"
fi