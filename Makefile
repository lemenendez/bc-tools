CC = g++
BIN = bin
MAIN = main.cpp
BITLIBS = /home/dev/bitcoin-lib/lib
INC = /home/dev/bitcoin-lib/include
LIBS =-lbitcoin -lboost_system -lboost_program_options -lboost_regex -lsecp256k1 -lboost_thread

b-tools: $(MAIN) includes/bc-tools.hpp includes/p-options.hpp
	$(CC) -I$(INC) includes/bc-tools.hpp includes/p-options.hpp $(MAIN) -Iincludes -L$(BITLIBS) $(LIBS) -o $(BIN)/b-tools -std=c++11 -lpthread



