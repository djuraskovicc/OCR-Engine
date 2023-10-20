CXX = g++
CXXFLAGS = -std=c++17
LIBS = $(shell pkg-config --cflags --libs opencv4) -L/usr/include/leptonica -ltesseract

SRC = main.cpp filters.cpp filters.h processing.cpp processing.h
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
