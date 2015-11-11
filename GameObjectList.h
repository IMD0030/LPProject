#ifndef GAMEOBJECTLIST_H_INCLUDED
#define GAMEOBJECTLIST_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <typeinfo>
#include "GameObject.h"

class NoDaLista {
public:
	GameObject *valor;
	NoDaLista *prox;
};

class GameObjectList {
public:
    NoDaLista *inicio;

    GameObjectList();

	void Adicionar(GameObject *item);

	void RemoverSeq(GameObject *item);

	void Remover(GameObject *item);

	int MouseDown(float x, float y);
};

#endif // GAMEOBJECTLIST_H_INCLUDED

