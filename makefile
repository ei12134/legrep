CC = g++
PROG = legrep
CFLAGS = -Wall -std=c++11
SRCS = src/*.cpp
BIN_DIR = bin

all: mkBinDir compile

mkBinDir:
	mkdir -p ${BIN_DIR}

compile:
	$(CC) $(SRCS) -o $(BIN_DIR)/$(PROG) $(CFLAGS)

clean:
	@rm -f $(BIN_DIR)/$(PROG) $(BIN_DIR)/*.o core
