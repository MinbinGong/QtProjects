QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    analyzer_worker.cpp \
    main.cpp \
    analyzer.cpp

HEADERS += \
    analyzer.h \
    analyzer_worker.h

FORMS += \
    analyzer.ui

TRANSLATIONS += \
    Analyzer_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

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
        -lopencv_videoio

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
