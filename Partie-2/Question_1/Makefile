CC=g++ -O2 -Wall
CFLAGS=
LDFLAGS=
EXEC=main
SRC=./src/main.cpp
	
OBJ= $(SRC:.cpp=.o)

CFLAGS=

all: $(EXEC)

main: $(OBJ)
	$(CC) $(CFLAGS) -o ./bin/$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	find . -name "*.o" -delete
	find ./bin/$(EXEC) -delete

mrproper: clean
	rm $(EXEC)
