TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Cell.cpp \
        Eingabe.cpp \
        Field.cpp \
        Minesweeper_Game.cpp \
        Player.cpp \
        main.cpp

HEADERS += \
    Cell.h \
    Eingabe.h \
    Field.h \
    Minesweeper_Game.h \
    Player.h
