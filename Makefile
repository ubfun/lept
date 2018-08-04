SRC	= lept.c test.c
OBJ	= lept

run: $(OBJ)
	./$(OBJ)

$(OBJ): $(SRC)
	clang -o $@ $^


clean: $(OBJ)
	rm -rf $<
