TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Cell.cpp \
        Eingabe.cpp \
        Field.cpp \
        main.cpp \
        minesweeper.cpp \
        spieler.cpp

HEADERS += \
    Cell.h \
    Eingabe.h \
    Field.h \
    minesweeper.h \
    spieler.h