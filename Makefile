EXE=marmotrecon.mrexe
DEP=cJSON/cJSON.c util.c map.c character.c inventory.c savemgr.c

all: $(EXE)

marmotrecon.mrexe:
	gcc marmotrecon.c $(DEP) -o marmotrecon.mrexe

clean:
	rm $(EXE)