#-------------------------------------------------
#
# Project created by QtCreator 2018-02-11T13:56:13
#
#-------------------------------------------------

QT       += core gui \
            multimedia \
            testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gravity-Flip
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

QMAKE_CXXFLAGS += --std=c++0x

SOURCES += \
        main.cpp \
    Game.cpp \
    Player.cpp \
    BackgroundUpdater.cpp \
    Set1.cpp \
    MainWindow.cpp \
    GameOverWindow.cpp \
    BackgroundMusic.cpp \
    SelectPlayersWindow.cpp \
    InstructionWindow.cpp \
    ScoreUpdater.cpp \
    Trail.cpp \
    Set2.cpp \
    PlayerState.cpp \
    RunPlayerWorker.cpp \
    CustomButton.cpp \
    NoobSet.cpp

HEADERS += \
    Game.h \
    Player.h \
    BackgroundUpdater.h \
    Set1.h \
    MainWindow.h \
    GameOverWindow.h \
    BackgroundMusic.h \
    SelectPlayersWindow.h \
    InstructionWindow.h \
    ScoreUpdater.h \
    Trail.h \
    Set2.h \
    PlayerState.h \
    RunPlayerWorker.h \
    GameType.h \
    GameState.h \
    CustomButton.h \
    NoobSet.h

RESOURCES += \
    res.qrc
