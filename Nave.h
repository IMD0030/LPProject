#ifndef _NAVE_H_
#define _NAVE_H_
#define MAX_VIDA 100
#define TAMANHO_NAVE 20
#include <iostream>
#include <cstring>
#include <typeinfo>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Nave {
public:
	float p_x, p_y;
	int vida;
	int tamanho;
	int municao;
	int kills;


	Nave();

	void Start();

	void Update();

	void Render();

};

#endif