EXE=marmotrecon.mrexe
OBJ=marmotrecon.o cJSON.o util.o map.o character.o inventory.o savemgr.o skills.o

all: $(EXE)

marmotrecon.mrexe: $(OBJ)
	gcc $(OBJ) -o marmotrecon.mrexe

marmotrecon.o: marmotrecon.c
	gcc -c marmotrecon.c

character.o: character.c
	gcc -c character.c

savemgr.o: savemgr.c
	gcc -c savemgr.c

inventory.o: inventory.c
	gcc -c inventory.c

map.o: map.c
	gcc -c map.c

skills.o: skills.c
	gcc -c skills.c

cJSON.o: cJSON/cJSON.c
	gcc -c cJSON/cJSON.c

clean:
	rm $(EXE) $(OBJ)