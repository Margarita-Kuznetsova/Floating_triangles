CC = clang
LOVE = /home/margo/FloatingTriangles/Love/build/love
CPP = clang++
OBJ_FLAG = -c -O3

all:
	$(LOVE) -f test1_if.love -o test1_if.love.ll
	$(LOVE) -f test2_while.love -o test2_while.love.ll
	$(LOVE) -f test3_function.love -o test3_function.love.ll
	$(CC) test1_if.love.ll -o a1.out
	$(CC) test2_while.love.ll -o a2.out
	$(CC) test3_function.love.ll -o a3.out
	./a1.out
	./a2.out
	./a3.out