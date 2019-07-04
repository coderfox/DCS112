CC=clang++
IDIR=lib . entity interface util
CFLAGS=-Wall -Wextra -std=c++14 -g $(patsubst %,-I %,$(IDIR))
FFLAGS= #-DNO_COLOR_OUTPUT
ODIR=obj
BIN=main
BIN_TEST=main.test

_OBJ = entity/campus_card entity/card entity/credit_card \
	   entity/transaction entity/binding_card \
	   util/utils interface/identifiable ui
OBJ = $(patsubst %,$(ODIR)/%.o,$(_OBJ))

_OBJ_MAIN = main
OBJ_MAIN = $(patsubst %,$(ODIR)/%.o,$(_OBJ_MAIN))

_OBJ_TEST = main.test.o \
			util/utils.test.o util/singleton.test.o \
			entity/transaction.test.o entity/repository.test.o \
			entity/credit_card.test.o entity/campus_card.test.o
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
	mkdir -p $(ODIR)/entity
	mkdir -p $(ODIR)/util
	mkdir -p $(ODIR)/interface

clean:
	rm -f $(OBJ) $(OBJ_MAIN) $(OBJ_TEST) $(BIN)  $(BIN_TEST)

run: $(BIN)
	./$(BIN)

test: $(BIN_TEST)
	./$(BIN_TEST)

test-verbose: $(BIN_TEST)
	./$(BIN_TEST) -s
