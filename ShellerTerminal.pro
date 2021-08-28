QT += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    core.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Serial as external static library
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libs/serial/build/release/ -lserial
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libs/serial/build/debug/ -lserial
else:unix: LIBS += -L$$PWD/../../Libs/serial/build/ -lserial

INCLUDEPATH += $$PWD/../../Libs/serial
DEPENDPATH += $$PWD/../../Libs/serial

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/serial/build/release/libserial.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/serial/build/debug/libserial.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/serial/build/release/serial.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/serial/build/debug/serial.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../Libs/serial/build/libserial.a
