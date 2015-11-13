#include <iostream>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <typeinfo>
#include "GameObject.h"


GameObject::GameObject(std::string nome, float px, float py, float vx, float vy, float atr, float s){
	this->nome = nome;
	this->posicao_x = px;
	this->posicao_y = py;
	this->velocidade_x=vx;
	this->velocidade_y=vy;
	this->atrito=atr;
	this->size=s;
}

void GameObject::Start(){
	std::cout << "Eu sou um objeto de nome: " << this->nome << "." << std::endl;
}

void GameObject::Update(){
//void GameObject::Update(GameObject *item, GameObjectList *Lista){
	//std::cout << "Eu atualizei meu objeto: " << this->nome << "." << std::endl;
}

bool GameObject::Devo_Morrer(){
	return false;
}

void GameObject::Render(){
	std::cout << "Eu renderizei meu objeto: " << this->nome << "." << std::endl;
}

int GameObject::MouseDown(float x, float y){
	return 0;
}

void GameObject::AplicarForca(float x, float y, float forca){
	//this->posicao_x += x;
	//this->posicao_y += y;
	//this->velocidade_x= 
	//this->velocidade_y=
}

