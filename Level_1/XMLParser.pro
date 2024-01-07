QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Compression.cpp \
    GraphDialog.cpp \
    GraphViewer.cpp \
    Helpers.cpp \
    XMLToJson.cpp \
    correcterrors.cpp \
    displayproblematicxml.cpp \
    globals.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    prettify.cpp \
    user.cpp \
    xmlparser.cpp

HEADERS += \
    Compression.h \
    GraphDialog.h \
    GraphViewer.h \
    Helpers.h \
    XMLToJson.h \
    correcterrors.h \
    displayproblematicxml.h \
    globals.h \
    graph.h \
    mainwindow.h \
    prettify.h \
    user.h \
    xmlparser.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
