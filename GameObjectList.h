#ifndef GAMEOBJECTLIST_H_INCLUDED
#define GAMEOBJECTLIST_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <typeinfo>
#include "GameObject.h"
#include <math.h>

class GameObject;

class NoDaLista {
public:
	GameObject *valor;
	NoDaLista *prox;
};

class GameObjectList {
public:
    NoDaLista *inicio;
    //float tam_x, tam_y;

    GameObjectList();

	void Adicionar(GameObject *item);

	void RemoverSeq(GameObject *item);

	void Remover(GameObject *item);

	void Render();

	void Update();

	//void Update(GameObjectList *Lista);

	void Impacto(GameObjectList *Lista);

	int MouseDown(float x, float y);
};

#endif // GAMEOBJECTLIST_H_INCLUDED

