QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

#INCLUDEPATH += C:\opencv\build\include

#LIBS += C:\opencv\build\bin\libopencv_core3414.dll
#LIBS += C:\opencv\build\bin\libopencv_highgui3414.dll
#LIBS += C:\opencv\build\bin\libopencv_imgcodecs3414.dll
#LIBS += C:\opencv\build\bin\libopencv_imgproc3414.dll
#LIBS += C:\opencv\build\bin\libopencv_features2d3414.dll
#LIBS += C:\opencv\build\bin\libopencv_calib3d3414.dll

INCLUDEPATH += $$(OPENCV_SDK_DIR)/include

LIBS += -L$$(OPENCV_SDK_DIR)/x64/mingw/lib \
        -lopencv_core3414        \
        -lopencv_highgui3414     \
        -lopencv_imgcodecs3414   \
        -lopencv_imgproc3414     \
        -lopencv_features2d3414  \
        -lopencv_calib3d3414

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
