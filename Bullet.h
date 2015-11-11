#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include <iostream>
#include <cstring>
#include <allegro5/allegro.h>
#include "GameObject.h"
#include <math.h> 
#include "Nave.h"


class Bullet: public GameObject{
	public:
		float raio;
		int	id;


		Bullet();

		void Novo();

		void Start();

		void Update();

		void Render();
};

#endif // BULLET_H_INCLUDED

