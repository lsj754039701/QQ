#-------------------------------------------------
#
# Project created by QtCreator 2016-04-03T10:49:08
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqV2
TEMPLATE = app

HEADERS += \
    titlewidget.h \
    logindlg.h \
    bottomwidget.h \
    resources.h \
    basedialog.h \
    workstation.h \
    linesignatrue.h \
    userdefine.h \
    friendtoolbox.h \
    friendwidget.h \
    friendtabbar.h \
    client_h/myclient.h \
    client_h/dataformat.h \
    client_h/datatype.h \
    registerdlg.h \
    finddlg.h \
    recommendwidget.h \
    messagelab.h \
    classifyfriend.h \
    chatdlg.h

SOURCES += \
    titlewidget.cpp \
    logindlg.cpp \
    main.cpp \
    bottomwidget.cpp \
    resources.cpp \
    basedialog.cpp \
    workstation.cpp \
    linesignatrue.cpp \
    friendtoolbox.cpp \
    friendwidget.cpp \
    friendtabbar.cpp \
    client_cpp/myclient.cpp \
    client_cpp/dataformat.cpp \
    registerdlg.cpp \
    finddlg.cpp \
    recommendwidget.cpp \
    messagelab.cpp \
    classifyfriend.cpp \
    chatdlg.cpp

RESOURCES += \
    image.qrc

FORMS += \
    workstation.ui \
    friendwidget.ui \
    friendtabbar.ui \
    registerdlg.ui \
    finddlg.ui \
    recommendwidget.ui \
    classifyfriend.ui \
    chatdlg.ui

CONFIG += c++11
