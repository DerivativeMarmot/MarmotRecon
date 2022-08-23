CC = gcc -c -I include/
SRC = src/
OBJ = build/
BIN = bin/
HEADER = include/
EXE=$(BIN)marmotrecon.mrexe

SOURCEFILES = $(shell find $(SRC) -type f -name "*.c")
OBJECTFILES = $(patsubst $(SRC)%.c,$(OBJ)%.o,$(SOURCEFILES))

all:$(EXE)

$(EXE): $(OBJECTFILES)
	gcc $(OBJECTFILES) -o $(EXE)

$(OBJ)marmotrecon.o: $(SRC)marmotrecon.c $(OBJ)character.o $(OBJ)savemgr.o
	$(CC) $(SRC)marmotrecon.c -o $(OBJ)marmotrecon.o

$(OBJ)savemgr.o: $(SRC)savemgr.c $(HEADER)savemgr.h $(OBJ)util.o
	$(CC) $(SRC)savemgr.c -o $(OBJ)savemgr.o

$(OBJ)character.o: $(SRC)character.c $(HEADER)character.h $(OBJ)map.o $(OBJ)battle.o
	$(CC) $(SRC)character.c -o $(OBJ)character.o

$(OBJ)map.o: $(SRC)map.c $(HEADER)map.h $(OBJ)util.o
	$(CC) $(SRC)map.c -o $(OBJ)map.o

$(OBJ)battle.o: $(SRC)battle.c $(HEADER)battle.h $(OBJ)skills.o $(OBJ)inventory.o
	$(CC) $(SRC)battle.c -o $(OBJ)battle.o

$(OBJ)inventory.o: $(SRC)inventory.c $(HEADER)inventory.h $(OBJ)util.o
	$(CC) $(SRC)inventory.c -o $(OBJ)inventory.o

$(OBJ)skills.o: $(SRC)skills.c $(HEADER)skills.h $(OBJ)util.o
	$(CC) $(SRC)skills.c -o $(OBJ)skills.o

$(OBJ)util.o: $(SRC)util.c $(HEADER)util.h $(HEADER)recon_info.h $(OBJ)cJSON.o
	$(CC) $(SRC)util.c -o $(OBJ)util.o

$(OBJ)cJSON.o: $(SRC)cJSON.c
	$(CC) $(SRC)cJSON.c -o $(OBJ)cJSON.o

clean:
	rm $(OBJ)*

init:
	mkdir $(OBJ) $(BIN)