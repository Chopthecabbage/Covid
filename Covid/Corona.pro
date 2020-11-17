QT       += core gui network webenginewidgets xml charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chartdata.cpp \
    disaster_api.cpp \
    disaster_handler.cpp \
    disaster_msg.cpp \
    google.cpp \
    googledialog.cpp \
    infectinfo.cpp \
    location.cpp \
    main.cpp \
    infectstatus.cpp \
    point.cpp

HEADERS += \
    Common.h \
    chartdata.h \
    disaster_api.h \
    disaster_handler.h \
    disaster_msg.h \
    google.h \
    googledialog.h \
    infectinfo.h \
    infectstatus.h \
    location.h \
    point.h

FORMS += \
    disaster_handler.ui \
    google.ui \
    googledialog.ui \
    infectstatus.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
