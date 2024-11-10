CC = g++
CXXFLAGS = -Wall -O2 -std=gnu++20

AST_DIR = ast

AST_SRC = $(AST_DIR)/AST.cpp
NUM_SRC = $(AST_DIR)/Num.cpp
ADD_SRC = $(AST_DIR)/Add.cpp
SUB_SRC = $(AST_DIR)/Sub.cpp
WITH_SRC = $(AST_DIR)/With.cpp
ID_SRC = $(AST_DIR)/Id.cpp
FUN_SRC = $(AST_DIR)/Fun.cpp
APP_SRC = $(AST_DIR)/App.cpp
IF_SRC = $(AST_DIR)/If.cpp
OR_SRC = $(AST_DIR)/Or.cpp
EQ_SRC = $(AST_DIR)/Eq.cpp
MULT_SRC = $(AST_DIR)/Mult.cpp
PARSER_SRC = Parser.cpp
INTERPETER_SRC = Interpreter.cpp
MAIN_SRC = main.cpp

MAIN_TARGET = main


$(MAIN_TARGET) : $(AST_SRC) $(NUM_SRC) $(ADD_SRC) $(SUB_SRC) $(WITH_SRC) $(ID_SRC) $(FUN_SRC) $(APP_SRC) $(IF_SRC) $(OR_SRC) $(EQ_SRC) $(MULT_SRC) $(PARSER_SRC) $(INTERPETER_SRC) $(MAIN_SRC)
	$(CC) $(CXXFLAGS) -o $(MAIN_TARGET) $(AST_SRC) $(NUM_SRC) $(ADD_SRC) $(SUB_SRC) $(WITH_SRC) $(ID_SRC) $(FUN_SRC) $(APP_SRC) $(IF_SRC) $(OR_SRC) $(EQ_SRC) $(MULT_SRC) $(PARSER_SRC) $(INTERPETER_SRC) $(MAIN_SRC)

clean:
	rm -f $(MAIN_TARGET)