TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

macx|win32: LIBS += -L$$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/include
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/lib/SDL2.lib
else:macx|win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/Cellar/sdl2/2.0.12_1/lib/libSDL2.a
