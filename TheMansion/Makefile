CC = g++
FLAGS = -g -Wall
OBJS = build/Character.o build/Enemy.o build/Entity.o build/Item.o build/main.o build/MansionGame.o build/Map.o build/Player.o build/Room.o build/TextureSet.o

all: TheMansion

TheMansion: $(OBJS)
	$(CC) $^ -o $@ -framework OpenGL -framework GLUT $(FLAGS)

build/Character.o: src/Character.cpp src/Character.h src/Include.h
	$(CC) -c $< -o $@ $(FLAGS)

build/Enemy.o: src/Enemy.cpp src/Enemy.h src/Include.h
	$(CC) -c $< -o $@ $(FLAGS)

build/Entity.o: src/Entity.cpp src/Entity.h src/Include.h
	$(CC) -c $< -o $@ $(FLAGS)

build/Item.o: src/Item.cpp src/Item.h src/Include.h
	$(CC) -c $< -o $@ $(FLAGS)

build/main.o: src/main.cpp src/Include.h
	$(CC) -c $< -o $@ $(FLAGS)

build/MansionGame.o: src/MansionGame.cpp src/MansionGame.h src/Include.h
	$(CC) -c $< -o $@ $(FLAGS)

build/Map.o: src/Map.cpp src/Map.h src/Include.h
	$(CC) -c $< -o $@ $(FLAGS)

build/Player.o: src/Player.cpp src/Player.h src/Include.h
	$(CC) -c $< -o $@ $(FLAGS)

build/Room.o: src/Room.cpp src/Room.h src/Include.h
	$(CC) -c $< -o $@ $(FLAGS)

build/TextureSet.o: src/TextureSet.cpp src/TextureSet.h src/Include.h
	$(CC) -c $< -o $@ $(FLAGS)

clean:
	rm -f build/*.o TheMansion
