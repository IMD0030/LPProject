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

//void Asteroide::Update(GameObject *item, GameObjectList *Lista){
void Asteroide::Update(){
	//std :: cout << "esse Asteroide tem velocidade" << this->velocidade_y<< std::endl;
    this->posicao_y += this->velocidade_y;
	if (this->posicao_y >= Utils::getAlturaTela()) {
		this->posicao_y = Utils::getAlturaTela();
		//std :: cout << "esse Asteroide precisa ser destruida" << std::endl;
		//return 1;
	}
}

bool Asteroide::Devo_Morrer(){
	if(this->posicao_y >= Utils::getAlturaTela()){
		std::cout << "Id do Asteroide que vai morrer eh " << this->id <<"Devo morrer é verdade"<<std::endl;
		return true;
	}
	else{
		return false;
	}
}

void Asteroide::Render(){
	//ALLEGRO_FONT *fonte = al_load_ttf_font("fonte/Timeless.ttf",15,0);
    al_draw_filled_circle(this->posicao_x, this->posicao_y, this->size, al_map_rgb(0, 0,255));
    //al_draw_textf(Utils::getFonteAlvo(), al_map_rgb(0,0,0), this->posicao_x-6, this->posicao_y-6,  0, "%d", this->id);
}