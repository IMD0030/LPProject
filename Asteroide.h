#ifndef ASTEROIDE_H_INCLUDED
#define ASTEROIDE_H_INCLUDED
#include <iostream>
#include <cstring>
#include <typeinfo>
#include <allegro5/allegro.h>
#include "GameObject.h"

class Asteroide: public GameObject{
	public:
		int id, ponto;
		float vida;

		//Asteroide(std::string nome="Asteroide", float px=0, float py=0, float vx=0, float vy=0, float atr=0, float r=1);

		Asteroide();

		void Novo(GameObjectList *Asteroides, float px, int s, float vel);

		void Start();

		void Update();

		//void Update(GameObject *item, GameObjectList *Lista);

		bool Devo_Morrer();

		void Render();
};

#endif	