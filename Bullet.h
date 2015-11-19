#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include <iostream>
#include <cstring>
#include <allegro5/allegro.h>
#include "GameObject.h"
#include <math.h> 
#include "Nave.h"
#include "Utils.h"

class Bullet: public GameObject{
	public:
		float raio;
		int	id;

		Bullet();

		void Novo(Nave n, GameObjectList *Bullets);

		void Start();

		void Update();

		//void Update(GameObject *item, GameObjectList *Lista);

		bool Devo_Morrer();

		void Render();
};

#endif // BULLET_H_INCLUDED

