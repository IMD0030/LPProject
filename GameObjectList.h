#ifndef GAMEOBJECTLIST_H_INCLUDED
#define GAMEOBJECTLIST_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <typeinfo>
#include "GameObject.h"
#include <math.h>
#include "Nave.h"

class GameObject;
class Nave;

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

	void LimparLista();

	void Remover(GameObject *item);

	void Render();

	void Update();

	int ObjectCont();

	bool Distancia(int pxdois, int pxum, int pydois, int pyum, float sizedois, float sizeum);

	void Impacto(GameObjectList *Lista);

	bool ImpactoFirstElement(Nave *n, GameObjectList *Lista);

	int MouseDown(float x, float y);

	int idLastObject();
};

#endif // GAMEOBJECTLIST_H_INCLUDED

