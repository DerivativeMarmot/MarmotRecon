EXE=marmotrecon.mrexe

all: $(EXE)

marmotrecon.mrexe:
	gcc marmotrecon.c map.c character.c -o marmotrecon.mrexe

clean:
	rm $(EXE)