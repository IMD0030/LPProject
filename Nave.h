#ifndef _NAVE_H_
#define _NAVE_H_
#include <iostream>
#include <cstring>
#include <typeinfo>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "GameObjectList.h"

class GameObjectList;

class Nave {
public:
	int p_x, p_y;
	int vida;
	int tamanho;
	int municao;
	int kills;
	int movimento;


	Nave(int px = 0, int py=0);

	void Up();

	void Down();

	void Left();

	void Right();

	void Start();

	void Update(ALLEGRO_EVENT e);

	void Render();

	bool Impacto(GameObjectList *Lista);

	bool DevoMorrer();
};

#endif