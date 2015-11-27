#include <iostream>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <typeinfo>
#include "GameObject.h"


GameObject::GameObject(float px, float py, float vx, float vy, float atr, float s){
	this->posicao_x = px;
	this->posicao_y = py;
	this->velocidade_x=vx;
	this->velocidade_y=vy;
	this->atrito=atr;
	this->size=s;
}

void GameObject::Start(){
}

void GameObject::Update(){
}

bool GameObject::Devo_Morrer(){
	return false;
}

void GameObject::Render(){
}

int GameObject::MouseDown(float x, float y){
	return 0;
}

void GameObject::AplicarForca(float x, float y, float forca){
}

