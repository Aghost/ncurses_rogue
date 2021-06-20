# Rogue

PROJECT_NAME =? Rogue

.PHONY = compile clear

compile:
	gcc -o Rogue.out -O3 main.c -lncurses
	
clean:
	rm -f Rogue.out
