#ifndef ASTEROIDE_H_INCLUDED
#define ASTEROIDE_H_INCLUDED
#include <iostream>
#include <cstring>
#include <typeinfo>
#include <allegro5/allegro.h>
#include "GameObject.h"

class Asteroide: public GameObject{
	public:
		float vida;
		int power;

		Asteroide();

		void Novo(GameObjectList *Asteroides, float px, float vel);

		void Start();

		void Update();

		bool Devo_Morrer();

		void Render();
};

#endif	