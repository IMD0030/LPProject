#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <typeinfo>
#include "GameObjectList.h"

class GameObjectList;

class GameObject{
    public:
		std::string nome;
		float posicao_x, posicao_y;
		float velocidade_x, velocidade_y;
		float atrito;
		float size;

		GameObject(std::string nome="", float px=0, float py=0, float vx=0, float vy=0, float atr=0, float s=0);

		virtual void Start();

		//virtual void Update(GameObject *item, GameObjectList *Lista);

		virtual void Update();

		virtual bool Devo_Morrer();

		virtual void Render();

		virtual int MouseDown(float x, float y);

		virtual void AplicarForca(float x = 2, float y = 1, float forca = 10);
};



#endif // GAMEOBJECT_H_INCLUDED
