QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/match.cpp \
    core/matchresult.cpp \
    core/player.cpp \
    core/playercategory.cpp \
    core/tennis.cpp \
    main.cpp \
    mainwindow.cpp \
    playermodel.cpp \
    testmatch.cpp

HEADERS += \
    core/MatchRules.h \
    core/match.h \
    core/matchresult.h \
    core/player.h \
    core/playercategory.h \
    core/tennis.h \
    mainwindow.h \
    playermodel.h \
    testmatch.h

FORMS += mainwindow.ui \
    testmatch.ui

FORMS += testmatch.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    styles.qss

