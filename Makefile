CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 -pedantic

SRC_TEST = test.c
BIN_TEST = test

SRC = tinyprintf.c my_itoa_base.c
OBJ = tinyprintf.o my_itoa_base.o
LIB = libtinyprintf.a



test: $(SRC) $(SRC_TEST)
	$(CC) $(CFLAGS) -o $(BIN_TEST) $(SRC) $(SRC_TEST)



library: $(OBJ)
	ar -csr $(LIB) $(OBJ)

$(OBJ):



clean:
	$(RM) -f $(OBJ) $(LIB) $(BIN_TEST)
