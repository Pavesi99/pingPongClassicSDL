TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

macx: LIBS += -L$$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/include
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/include

macx: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/lib/libSDL2.a

win32: LIBS += -L$$PWD/../SDL2-2.0.9/i686-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../SDL2-2.0.9/i686-w64-mingw32/include
DEPENDPATH += $$PWD/../SDL2-2.0.9/i686-w64-mingw32/include
