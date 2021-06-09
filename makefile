# makefile hearts game

TARGET= gameApp.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= deck.o vector.o game.o gameApp.o player.o round.o utilFuncs.o ui.o


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

ui.o: ui.c ui.h
	$(CC) $(CFLAGS) -c ui.c

deck.o: deck.c deck.h
	$(CC) $(CFLAGS) -c deck.c

vector.o: ../vector/vector.c ../vector/vector.h
	$(CC) $(CFLAGS) -c ../vector/vector.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

gameApp.o: gameApp.c
	$(CC) $(CFLAGS) -c gameApp.c

player.o: player.c player.h
	$(CC) $(CFLAGS) -c player.c

round.o: round.c round.h
	$(CC) $(CFLAGS) -c round.c

utilFuncs.o: utilFuncs.c utilFuncs.h
	$(CC) $(CFLAGS) -c utilFuncs.c

run: $(TARGET)
	./$(TARGET)
clean:
	rm -f $(TARGET) $(OBJS)
