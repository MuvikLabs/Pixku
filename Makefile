OBJ+=$(addprefix runt/, runt.o irunt.o basic.o)
OBJ+=lodepng/lodepng.o
OBJ += parse.o
CFLAGS += -Irunt -Ilodepng -std=c89 -Wall -pedantic

default: pixku testimage

pixku: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	$(RM) pixku $(OBJ) testimage
