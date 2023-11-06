QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FaceDetector.cpp \
    analyzer.cpp \
    analyzerworker.cpp \
    main.cpp

HEADERS += \
    FaceDetector.h \
    analyzer.h \
    analyzerworker.h

FORMS += \
    analyzer.ui

CONFIG += lrelease

INCLUDEPATH += /usr/local/include/opencv4

LIBS += -L/usr/local/lib  \
        -lopencv_core                   \
        -lopencv_highgui                \
        -lopencv_imgcodecs              \
        -lopencv_imgproc                \
        -lopencv_features2d             \
        -lopencv_flann                  \
        -lopencv_calib3d                \
        -lopencv_video                  \
        -lopencv_videoio                \
        -lopencv_objdetect

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    cascades/haarcascade_frontalface_default.xml
