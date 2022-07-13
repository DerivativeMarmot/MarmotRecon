EXE=marmotrecon.mrexe
DEP=map.c character.c inventory.c util.c cJSON/cJSON.c 

all: $(EXE)

marmotrecon.mrexe:
	gcc marmotrecon.c $(DEP) -o marmotrecon.mrexe

clean:
	rm $(EXE)