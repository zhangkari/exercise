PROJ := detector
CC := g++

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp,  %.o,  $(SRC))

$(PROJ) : $(OBJ)
	$(CC) $^ -o $@

clean:
	@rm $(PROJ) $(OBJ) -rvf
