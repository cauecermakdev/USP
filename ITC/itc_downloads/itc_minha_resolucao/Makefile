MAIN=Trabalho_1.c
BINARY=executable

all:
	gcc -march=native -Wall -Wextra -g $(MAIN) -o $(BINARY) -lm

run:
	./$(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)