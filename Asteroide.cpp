#include <iostream>
#include <cstring>
#include <typeinfo>
#include <allegro5/allegro.h>
#include "GameObject.h"
#include "GameObjectList.h"
#include "Asteroide.h"
#include "Utils.h"

Asteroide::Asteroide() {
}

void Asteroide::Novo(GameObjectList *Asteroides, float px, float vel){
	Asteroide *ast = new Asteroide();
	ast->posicao_x = px;
	ast->posicao_y = Utils::getAlturaInfo();
	ast->velocidade_y = vel;
	ast->size=Utils::getAsteroideSize();
	ast->id=Asteroides->idLastObject()+1;
	Asteroides->Adicionar(ast);
}

void Asteroide::Start(){
    std::cout << "Iniciei!" << std::endl;
}

void Asteroide::Update(){
    this->posicao_y += this->velocidade_y;
	if (this->posicao_y >= Utils::getAlturaTela()) {
		this->posicao_y = Utils::getAlturaTela();
	}
}

bool Asteroide::Devo_Morrer(){
	if(this->posicao_y >= Utils::getAlturaTela()){
		//std::cout << "Id do Asteroide que vai morrer eh " << this->id <<"Devo morrer é verdade"<<std::endl;
		return true;
	}
	else{
		return false;
	}
}

void Asteroide::Render(){
    al_draw_filled_circle(this->posicao_x, this->posicao_y, this->size, al_map_rgb(0, 0,255));
}