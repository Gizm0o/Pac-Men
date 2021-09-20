TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    nos_fichiers/gamemanagement.cpp \
    nos_fichiers/kbhit.cpp \
    nos_fichiers/menumanagement.cpp \
    nos_fichiers/scoreboard.cpp

LIBS += -lncurses

HEADERS += \
    nos_fichiers/type.h \
    nos_fichiers/kbhit.h \
    nos_fichiers/type.h \
    nos_fichiers/gamemanagement.h \
    nos_fichiers/menumanagement.h \
    nos_fichiers/scoreboard.h
