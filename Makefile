CXX = g++
CXXFLAGS = -std=c++17 -O3 -march=native -Wall
OPENCV_LIBS = 

LIBS = -I/usr/include/opencv4 -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lleptonica -ltesseract

SRC = main.cpp filters.cpp filters.h processing.cpp processing.h
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
