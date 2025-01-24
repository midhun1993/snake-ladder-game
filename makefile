shared:
	gcc --shared -fPIC ./src/board.c -o ./out/libboard.so
	gcc --shared -fPIC ./src/player.c -o ./out/libplayer.so
build:
	gcc ./src/main.c -o ./out/main -lncurses -lGL -lGLU -lglut -lm  -L./out -lboard -lplayer
debug: 
	./debug.sh
