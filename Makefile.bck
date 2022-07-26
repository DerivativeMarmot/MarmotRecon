EXE=marmotrecon.mrexe
OBJ=marmotrecon.o savemgr.o character.o map.o battle.o inventory.o skills.o util.o cJSON.o   
BLDD=build

all: $(EXE)

marmotrecon.mrexe: $(OBJ)
	gcc $(OBJ) -o marmotrecon.mrexe

marmotrecon.o: marmotrecon.c character.o savemgr.o
	gcc -c marmotrecon.c

savemgr.o: savemgr.c util.o
	gcc -c savemgr.c

character.o: character.c map.o battle.o
	gcc -c character.c

map.o: map.c util.o
	gcc -c map.c

battle.o: battle.c skills.o  inventory.o
	gcc -c battle.c

inventory.o: inventory.c util.o
	gcc -c inventory.c

skills.o: skills.c util.o
	gcc -c skills.c

$(BLDD)/util.o: util.c recon_info.h cJSON.o
	gcc -c util.c

cJSON.o: cJSON/cJSON.c
	gcc -c cJSON/cJSON.c

clean:
	rm $(EXE) $(OBJ)

init:
	mkdir BLDD