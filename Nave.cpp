#include <iostream>
#include <cstring>
#include <typeinfo>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Nave.h"
#include "GameObjectList.h"
#include "Utils.h"

using namespace std;


Nave::Nave(){
	this->vida = Utils::getMaxVida();
	this->p_x = Utils::getLarguraTela()/2;
	this->p_y = Utils::getAlturaTela()-Utils::getTamanhoDaNave();
	this->tamanho = Utils::getTamanhoDaNave();
	this->municao = 100;
    this->movimento = Utils::getMovimento();
	this->kills=0;
}

void Nave::Up(){
	if (this->p_y <= Utils::getAlturaInfo()) {
		this->p_y = Utils::getAlturaInfo();
	}
	else {
		this->p_y-=movimento;
	}
}

void Nave::Down(){
	if (this->p_y + this->tamanho >= Utils::getAlturaTela()) {
		this->p_y = Utils::getAlturaTela() - this->tamanho;
	}
	else {
		this->p_y+=movimento;
	}
}

void Nave::Left(){
    if (this->p_x <= 0) {
        this->p_x = 0;
    }
    else {
        this->p_x-=movimento;
    }
}

void Nave::Right(){
    if (this->p_x >= Utils::getLarguraTela() - this->tamanho) {
        this->p_x = Utils::getLarguraTela() - this->tamanho;
    }
    else {
        this->p_x+=movimento;
    }
}


void Nave::Start(){
    this->vida = Utils::getMaxVida();
    this->p_x = Utils::getLarguraTela()/2;
    this->p_y = Utils::getAlturaTela()-Utils::getTamanhoDaNave();
    this->kills=0;
}

void Nave::Update(ALLEGRO_EVENT e){
    std::cout << "Nave Atualizada!" << std::endl;
    std::cout << "KEYDOWN: " << e.keyboard.keycode << endl;
    switch (e.keyboard.keycode) {
    	case ALLEGRO_KEY_D: case 83:
    		this->p_x+=10;
    		break;
    	case ALLEGRO_KEY_A: case 82:
    		this->p_x-=10;
    		break;
    	case ALLEGRO_KEY_W: case 84:
    		Up();
    		break;
    	case ALLEGRO_KEY_S: case 85:
    		Down();
    		break;
    	case 75:
    		std::cout << "SPACE: "<< endl;
    		break;
    }
    //cout << "Teste";
}

void Nave::Render(){
    al_draw_filled_rectangle(this->p_x, this->p_y, this->p_x+tamanho, this->p_y+tamanho, al_map_rgb(255, 0, 0));
}

bool Nave::Impacto(GameObjectList *Lista){
    NoDaLista *aux = Lista->inicio;
    NoDaLista *aux_prox;
    float centrox, centroy;
    centrox = this->p_x + this->tamanho/2;
    centroy= this->p_y+this->tamanho/2;
    //cout<<"Verificando impacto da nave: "<<endl;
    while(aux !=NULL){
        if(Lista->Distancia(aux->valor->posicao_x, centrox, 
             aux->valor->posicao_y, centroy, 
              aux->valor->size, this->tamanho)){
            if(aux->prox != NULL){
                aux_prox = aux->prox;
            }
            else {
                aux_prox = NULL;
            }
            Lista->Remover(aux->valor);
            aux= aux_prox;
            this->vida = this->vida - 25;
            return true;
            ///cout << "Nave ATINGIDA, HOUSTON, WE HAVE A PROBLEM A VIDA EH " << this->vida  << endl;
        }
        if(aux!= NULL){
            aux=aux->prox;    
        }
        else{
            aux = NULL;
        }
    }
    return false;
}	

bool Nave::DevoMorrer(){
    if(this->vida <=0){
        return true;
    }
    else{
        return false;
    }
}