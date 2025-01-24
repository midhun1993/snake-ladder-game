shared:
	gcc --shared -fPIC ./src/board.c -o ./out/libboard.so
	gcc --shared -fPIC ./src/player.c -o ./out/libplayer.so
	gcc --shared -fPIC ./src/gui.c -o ./out/libgui.so -lGL -lGLU -lglut
build:
	gcc ./src/main.c -o ./out/main -lncurses -lGL -lGLU -lglut -lm  -L./out -lboard -lplayer -lgui
debug: 
	./debug.sh
