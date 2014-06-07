include(../defaults.pri)

TARGET= bitmonero-qt
TEMPLATE = app
QT += qml quick

CONFIG += console c++11

SOURCES += main.cpp \
    MoneroGUI.cpp

HEADERS += MoneroGUI.h

RESOURCES += qml.qrc

LIBS += -L../src -lbitmonero-qt-static

OTHER_FILES +=
