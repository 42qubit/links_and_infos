TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    PerlinNoise/TerrainGenerator.cpp \
    TgaReader/TgaImage.cpp \
    Various/functionsStringFile.cpp

DISTFILES +=

HEADERS += \
    PerlinNoise/TerrainGenerator.hpp \
    Stack/stack_array.hpp \
    Stack/stack_interface.hpp \
    Stack/stack_list.hpp \
    TgaReader/TgaImage.hpp \
    Various/functionsStringFile.hpp
