CC=g++
CFLAGS=-O3 -Wall -std=c++11
LDFLAGS=

EXEC=main

SRC=./src/color/RGB2YUV.cpp \
	./src/color/YUV2RGB.cpp \
	./src/tools/analysis.cpp \
	./src/tools/converter.cpp \
	./src/tools/img_diff.cpp \
	./src/main.cpp
	
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

main: $(OBJ)
	$(CC) $(CFLAGS) -o ./bin/$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	find . -name "*.o" -delete
	find ./bin/$(EXEC) -delete
