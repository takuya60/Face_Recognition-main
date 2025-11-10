# ======== capture_tool.pro ========
# 编译你的抓拍工具

QT += core gui widgets
CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = capture_tool

# --- 路径设置 ---
OBJECTS_DIR = $$OUT_PWD/obj/capture_tool
DESTDIR = $$OUT_PWD/bin

# --- 1. 获取 SDK 环境 ---
SDK_SYSROOT = $$getenv(SDKTARGETSYSROOT)
isEmpty(SDK_SYSROOT) {
    error("❌ 未检测到 SDK 环境，请先执行：source /opt/fsl-imx-x11/4.1.15-2.1.0/environment-setup-...")
}

# --- 2. 头文件路径 (已修正) ---
INCLUDEPATH += \
    $$PWD/inc \
    $$PWD/src \
    $${SDK_SYSROOT}/usr/include \
    $${SDK_SYSROOT}/usr/include/opencv2   # <-- 已修正为 opencv2

# --- 3. 源文件 ---
SOURCES += \
    src/capture_tool.cpp   # <-- 只需要这一个 main 文件

# (不需要 face_opencv.h)

# --- 4. 链接库 (需要的库更少) ---
LIBS += -L$${SDK_SYSROOT}/usr/lib \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_imgcodecs \
        -lopencv_videoio 
        
# (这个工具不需要 objdetect 或 face 库)