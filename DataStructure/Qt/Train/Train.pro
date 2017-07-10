#-------------------------------------------------
#
# Project created by QtCreator 2017-05-03T01:09:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Train
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    register.cpp \
    queryticket.cpp \
    useroperation.cpp \
    getstring.cpp \
    getnewpassword.cpp \
    plaintable.cpp \
    getint.cpp \
    tickettable.cpp \
    adminoperation.cpp \
    gettraininfo.cpp

HEADERS  += mainwindow.h \
    ../../src/User.hpp \
    ../../src/GeneralUser.hpp \
    ../../src/lib/vector.hpp \
    ../../src/lib/set.hpp \
    ../../src/lib/ptr.hpp \
    ../../src/lib/pair.hpp \
    ../../src/lib/map.hpp \
    ../../src/Exceptions.hpp \
    ../../src/Date.hpp \
    ../../src/File.hpp \
    ../../src/Station.hpp \
    login.h \
    register.h \
    ../../src/Train.hpp \
    ../../src/Tickets.hpp \
    queryticket.h \
    useroperation.h \
    getstring.h \
    getnewpassword.h \
    plaintable.h \
    getint.h \
    ../../src/Log.hpp \
    tickettable.h \
    adminoperation.h \
    gettraininfo.h \
    fromfile.h

FORMS    += mainwindow.ui \
    login.ui \
    register.ui \
    queryticket.ui \
    useroperation.ui \
    getstring.ui \
    getnewpassword.ui \
    plaintable.ui \
    getint.ui \
    tickettable.ui \
    adminoperation.ui \
    gettraininfo.ui

RESOURCES += \
    image.qrc

DISTFILES +=
