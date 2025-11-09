QT += core gui widgets
CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = face_app

# 指定输出路径
OBJECTS_DIR = $$OUT_PWD/obj
DESTDIR = $$OUT_PWD/bin

# ========================
# 1. 获取并检测 NXP SDK 环境
# ========================
SDK_SYSROOT = $$getenv(SDKTARGETSYSROOT)

isEmpty(SDK_SYSROOT) {
    error("❌ 未检测到 SDK 环境，请先执行：source /opt/fsl-imx-x11/4.1.15-2.1.0/environment-setup-cortexa7hf-neon-poky-linux-gnueabi")
} else {
    message("✅ 已加载 NXP Sysroot: " $${SDK_SYSROOT})
}

# ========================
# 2. 设置头文件路径
# ========================
INCLUDEPATH += \
    $$PWD/inc \
    $$PWD/src \
    $${SDK_SYSROOT}/usr/include \
    $${SDK_SYSROOT}/usr/include/opencv4

# ========================
# 3. 源文件与头文件
# ========================
SOURCES += \
    src/face_opencv.cpp \
    src/test.cpp

HEADERS += \
    inc/face_opencv.h

# ========================
# 4. 链接 OpenCV 库
# ========================
LIBS += -L$${SDK_SYSROOT}/usr/lib \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_imgcodecs \
        -lopencv_videoio \
        -lopencv_objdetect \
        -lopencv_face 