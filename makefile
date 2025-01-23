build:
	gcc ./src/main.c -o ./out/main -lncurses -lGL -lGLU -lglut -lm 
debug: 
	gdb ./out/main
