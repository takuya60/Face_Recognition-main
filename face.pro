QT += core gui widgets
CONFIG += c++11

OBJECTS_DIR = $$OUT_PWD/obj
DESTDIR = $$OUT_PWD/bin


TARGET = face_app



# 5.1. 从环境变量中获取 Sysroot 路径
SDK_SYSROOT = $$getenv(SDKTARGETSYSROOT)
# 5.2. 检查 Sysroot 是否被正确加载
SDK_SYSROOT = $$getenv(SDKTARGETSYSROOT) # 从环境变量获取
isEmpty(SDK_SYSROOT) {
    error("!!!! 错误：必须先 source NXP SDK 环境脚本! !!!!")
} else {
    message("成功加载 NXP Sysroot: " $${SDK_SYSROOT})
}

INCLUDEPATH += $${SDK_SYSROOT}/usr/include
               $$PWD/inc
           
LIBS += -L$${SDK_SYSROOT}/usr/lib

SOURCES += $$files(src/*.cpp, true)

HEADERS += $$files(inc/*.h, true) \
           $$files(inc/*.hpp, true)


LIBS += -lopencv_core 
        -lopencv_imgproc 
        -lopencv_highgui 
        -lopencv_imgcodecs 
        -lopencv_videoio
LIBS += -lopencv_objdetect
LIBS += -lopencv_face
