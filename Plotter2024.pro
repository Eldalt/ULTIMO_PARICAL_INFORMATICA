QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17
QMAKE_CXXFLAGS +=-Wa,-mbig-obj
DEFINES += MUPARSER_STATIC

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

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L"C:\info2_dll\qcustomplot"
INCLUDEPATH += "C:\info2_dll\qcustomplot"

LIBS += -lqcustomplot2

LIBS +=-L"C:\info2_dll\muparser"
INCLUDEPATH +="C:\info2_dll\muparser"
LIBS +=-lMuParserCreationDLL_2024

DISTFILES += \
    Corriente.txt \
    Tension.txt \
    pv_power.dat \
    utn_power.dat \
    vi_1.dat \
    vi_2.dat \
    vi_3.dat \
    vi_4.dat \
    vi_5.dat
