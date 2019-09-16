CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 -pedantic

SRC_TEST = test.c
BIN_TEST = test

SRC = tinyprintf.c
OBJ = tinyprintf.o
LIB = libtinyprintf.a



test: $(SRC) $(SRC_TEST)
	$(CC) $(CFLAGS) -o $(BIN_TEST) $(SRC) $(SRC_TEST)



library: $(OBJ)
	ar -csr $(LIB) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c -o $(OBJ) $(SRC)



clean:
	$(RM) -f $(OBJ) $(LIB) $(BIN_TEST)
