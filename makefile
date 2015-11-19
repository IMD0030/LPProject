Utils.o: Utils.h Utils.cpp
	g++ Utils.cpp -c

Nave.o: Nave.h Nave.cpp
	g++ Nave.cpp -c

GameObject.o: GameObject.h GameObject.cpp
	g++ GameObject.cpp -c

Asteroide.o: GameObject.o Asteroide.h Asteroide.cpp
	g++ Asteroide.cpp -c

Bullet.o: GameObject.o Bullet.h Bullet.cpp
	g++ Bullet.cpp -c

GameObjectList.o: GameObject.o GameObjectList.h GameObjectList.cpp
	g++ GameObjectList.cpp -c

main: main.cpp Utils.o Nave.o GameObject.o GameObjectList.o Bullet.o Asteroide.o
	g++ main.cpp Utils.o Nave.o GameObject.o GameObjectList.o Bullet.o Asteroide.o -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro -lallegro_primitives -lallegro_main -o main 

clean:
	rm -f *.o main
