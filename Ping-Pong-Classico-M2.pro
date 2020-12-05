TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        game.cpp \
        main.cpp \
        menu.cpp \
        twoPlayers.cpp

macx: LIBS += -L$$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/include
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/include

macx: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/lib/libSDL2.a

win32: LIBS += -L$$PWD/../SDL2-2.0.9/i686-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../SDL2-2.0.9/i686-w64-mingw32/include
DEPENDPATH += $$PWD/../SDL2-2.0.9/i686-w64-mingw32/include

HEADERS += \
    game.h \
    menu.h \
    twoPlayers.h

win32: LIBS += -L$$PWD/../SDL2_ttf-2.0.15/i686-w64-mingw32/lib/ -lSDL2_ttf

INCLUDEPATH += $$PWD/../SDL2_ttf-2.0.15/i686-w64-mingw32/include
DEPENDPATH += $$PWD/../SDL2_ttf-2.0.15/i686-w64-mingw32/include
