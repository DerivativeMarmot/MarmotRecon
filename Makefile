EXE=marmotrecon.mrexe
OBJ=marmotrecon.o cJSON.o util.o map.o character.o inventory.o savemgr.o skills.o

all: $(EXE)

marmotrecon.mrexe: $(OBJ)
	gcc $(OBJ) -o marmotrecon.mrexe

marmotrecon.o: marmotrecon.c character.o savemgr.o
	gcc -c marmotrecon.c

character.o: character.c inventory.o map.o skills.o
	gcc -c character.c

savemgr.o: savemgr.c util.o
	gcc -c savemgr.c

inventory.o: inventory.c util.o
	gcc -c inventory.c

map.o: map.c util.o
	gcc -c map.c

skills.o: skills.c util.o
	gcc -c skills.c

util.o: util.c recon_info.h
	gcc -c util.c

cJSON.o: cJSON/cJSON.c
	gcc -c cJSON/cJSON.c

clean:
	rm $(EXE) $(OBJ)