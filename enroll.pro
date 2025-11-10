# ======== enroll_tool.pro ========
# 编译你的录入工具

QT += core gui widgets
CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = enroll_tool

# --- 路径设置 ---
OBJECTS_DIR = $$OUT_PWD/obj/enroll_tool
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
    src/face_opencv.cpp \
    src/enroll_tool.cpp   # <-- 更改了 main 文件

HEADERS += \
    inc/face_opencv.h

# --- 4. 链接库 (与 face_app 相同) ---
LIBS += -L$${SDK_SYSROOT}/usr/lib \
        -lopencv_core \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_imgcodecs \
        -lopencv_videoio \
        -lopencv_objdetect \
        -lopencv_face