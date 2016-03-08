#------------------------------------------------------------------------------
#
#
#------------------------------------------------------------------------------
CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

TARGET = dithering
SRC_FILES = main.cpp OpenCV_util.cpp

.PHONY: clean

$(TARGET):
	g++ $(SRC_FILES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f *.o *~ ./$(TARGET) 

iterate:
	make clean && make
