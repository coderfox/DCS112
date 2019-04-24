CC=clang++
CFLAGS=-Wall -std=c++14 -g
ODIR=obj
BIN=main

_OBJ = main.o lexer.o polynominal.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $(BIN) $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BIN) 

run: $(BIN)
	./$(BIN)
