CC = clang
LOVE = /home/margo/FloatingTriangles/Love/build/love
CPP = clang++
OBJ_FLAG = -c -O3
LINK_FLAG = -lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CC) main.c $(OBJ_FLAG)
	$(CC) logic.c $(OBJ_FLAG)
	$(LOVE) -f extra_logic.love -o extra_logic.ll
	$(CC) extra_logic.ll $(OBJ_FLAG)
	$(CPP) main.o logic.o extra_logic.o picture.cpp $(LINK_FLAG) -o graphic