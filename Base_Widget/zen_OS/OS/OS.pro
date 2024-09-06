QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




# Specify sysroot path
QMAKE_SYSROOT = /home/dashnet/rpi-qt/sysroot

# Include paths
INCLUDEPATH += $$QMAKE_SYSROOT/usr/include
INCLUDEPATH += $$QMAKE_SYSROOT/usr/include/arm-linux-gnueabihf

# Library paths
LIBS += -L$$QMAKE_SYSROOT/usr/lib
LIBS += -L$$QMAKE_SYSROOT/usr/lib/arm-linux-gnueabihf

# Link against GLESv2, EGL, pthread, and m libraries
LIBS += -lGLESv2 -lEGL -lpthread -lm

# Cross-compiler settings
QMAKE_CXX = /home/dashnet/rpi-qt/tools/cross-pi-gcc-10.2.0-2/bin/arm-linux-gnueabihf-g++
QMAKE_CC = /home/dashnet/rpi-qt/tools/cross-pi-gcc-10.2.0-2/bin/arm-linux-gnueabihf-gcc




# Include paths for GStreamer
INCLUDEPATH += /home/dashnet/rpi-qt/sysroot/usr/include/gstreamer-1.0
INCLUDEPATH += /home/dashnet/rpi-qt/sysroot/usr/include/glib-2.0
#INCLUDEPATH += /home/dashnet/rpi-qt/sysroot/usr/lib/glib-2.0/include

INCLUDEPATH += /home/dashnet/rpi-qt/sysroot/usr/lib/arm-linux-gnueabihf/glib-2.0/include

# Library paths
LIBS += -L/home/dashnet/rpi-qt/sysroot/usr/lib/ -lgstreamer-1.0 -lgstapp-1.0 -lgstbase-1.0 -lgstvideo-1.0 -lgstpbutils-1.0 -lgobject-2.0 -lglib-2.0









SOURCES += \
    clickablelabel.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    clickablelabel.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
