 # -------------------------------------------------------------------
 #            Arquivo: Makefile
 # -------------------------------------------------------------------
 #              Autor: Bruno Krugel
 #               Data: 10/2024
 #      Atualizado em: [07/10/2024, 13h:03m]
 #
 # -------------------------------------------------------------------

$DEPURA=1

SRC_DIR = ./src
BIN_DIR = ./bin

LEX_FILE = $(BIN_DIR)/lex.yy.c
PARSER_FILE = $(BIN_DIR)/compilador.tab.c
PARSER_HEADER = $(BIN_DIR)/compilador.tab.h
COMPILER = $(BIN_DIR)/compilador

SRC_FILES = $(SRC_DIR)/compiladorF.c $(SRC_DIR)/Symbol.c $(SRC_DIR)/Types.c
OBJ_FILES = $(BIN_DIR)/compiladorF.o $(BIN_DIR)/Symbol.o $(BIN_DIR)/Types.o
HEADERS = $(SRC_DIR)/compilador.h $(SRC_DIR)/Symbol.h $(SRC_DIR)/Types.h $(SRC_DIR)/genericVec.h

all: folders $(BIN_DIR)/compilador

$(COMPILER): $(LEX_FILE) $(PARSER_FILE) $(OBJ_FILES)
	cp $(HEADERS) $(BIN_DIR)
	gcc $(LEX_FILE) $(PARSER_FILE) $(OBJ_FILES) -o $(COMPILER) -lfl -ly -lc
	ln -fs $(COMPILER) ./compilador

# analisador léxico
$(LEX_FILE): $(SRC_DIR)/compilador.l $(SRC_DIR)/compilador.h
	flex -o $(LEX_FILE) $(SRC_DIR)/compilador.l

# analisador sintático
$(PARSER_FILE) $(PARSER_HEADER): $(SRC_DIR)/compilador.y $(HEADERS)
	bison -d -v -o $(PARSER_FILE) $(SRC_DIR)/compilador.y

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	gcc -c $< -o $@

folders:
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR) ./compilador ./MEPA

