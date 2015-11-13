#ifndef _NAVE_H_
#define _NAVE_H_
#define MAX_VIDA 100
#define TAMANHO_NAVE 25
#include <iostream>
#include <cstring>
#include <typeinfo>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Nave {
public:
	int p_x, p_y;
	int vida;
	int tamanho;
	int municao;
	int kills;


	Nave(int px = 0, int py=0);

	void Up();

	void Down();

	void Left();

	void Right();

	void Start();

	void Update(ALLEGRO_EVENT e);

	void Render();

};

#endif