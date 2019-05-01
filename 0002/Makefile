CC=clang++
CFLAGS=-Wall -Wextra -std=c++14 -g -I lib -I .
FFLAGS= # -DNO_COLOR_OUTPUT
ODIR=obj
BIN=main
BIN_TEST=main.test

_OBJ = polynomial.o evaluator.o \
	parser/span.o parser/lexer.o parser/token.o \
	parser/parser.o parser/error.o parser/ast.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJ_MAIN = main.o
OBJ_MAIN = $(patsubst %,$(ODIR)/%,$(_OBJ_MAIN))

_OBJ_TEST = main.test.o polynomial.test.o evaluator.test.o \
	parser/lexer.test.o parser/token.test.o parser/parser.test.o parser/error.test.o
OBJ_TEST = $(patsubst %,$(ODIR)/%,$(_OBJ_TEST))

$(ODIR)/%.o: %.cpp | $(ODIR)/
	$(CC) -c -o $@ $< $(CFLAGS) $(FFLAGS)

$(BIN): $(OBJ) $(OBJ_MAIN)
	$(CC) -o $(BIN) $^ $(CFLAGS)

$(BIN_TEST): $(OBJ_TEST) $(OBJ)
	$(CC) -o $(BIN_TEST) $^ $(CFLAGS)

.PHONY: clean run test test-verbose

$(ODIR)/:
	mkdir -p $(ODIR)
	mkdir -p $(ODIR)/parser

clean:
	rm -f $(OBJ) $(OBJ_MAIN) $(OBJ_TEST) $(BIN)  $(BIN_TEST)

run: $(BIN)
	./$(BIN)

test: $(BIN_TEST)
	./$(BIN_TEST)

test-verbose: $(BIN_TEST)
	./$(BIN_TEST) -s
