#include <iostream>
#include <cstring>
#include <typeinfo>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Nave.h"
#include "GameObjectList.h"

using namespace std;


Nave::Nave(int px, int py){
	this->vida = MAX_VIDA;
	this->p_x = px;
	this->p_y = py-TAMANHO_NAVE;
	this->tamanho = TAMANHO_NAVE;
	this->municao = 100;
	this->kills =0;
}

void Nave::Up(){
	if (this->p_y <= 0) {
		this->p_y = 0;
	}
	else {
		this->p_y-=MOVIMENTO;
	}
}

void Nave::Down(){
	if (this->p_y + this->tamanho >= 600) {
		this->p_y = 600 - this->tamanho;
	}
	else {
		this->p_y+=MOVIMENTO;
	}
}

void Nave::Left(){
    if (this->p_x <= 0) {
        this->p_x = 0;
    }
    else {
        this->p_x-=MOVIMENTO;
    }
}

void Nave::Right(){
    if (this->p_x >= 800 - this->tamanho) {
        this->p_x = 800 - this->tamanho;
    }
    else {
        this->p_x+=MOVIMENTO;
    }
}


void Nave::Start(){
    std::cout << "Nave Inciada!" << std::endl;
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

void Nave::Impacto(GameObjectList *Lista){
    NoDaLista *aux = Lista->inicio;
    NoDaLista *aux_prox;
    float centrox, centroy;
    centrox = this->p_x + this->tamanho/2;
    centroy= this->p_y+this->tamanho/2;

    while(aux !=NULL){
        if(Lista->Distancia(aux->valor->posicao_x, centrox, 
             aux->valor->posicao_y, centroy, 
              aux->valor->size, this->tamanho)){
            aux_prox = aux->prox;
            Lista->Remover(aux->valor);
            aux= aux_prox;
            this->vida = this->vida - 25;
            ///cout << "Nave ATINGIDA, HOUSTON, WE HAVE A PROBLEM A VIDA EH " << this->vida  << endl;
            if(this->vida <= 0){
                cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;
                cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;
                cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;
                cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;
                cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;
                cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;

            }
        }
        aux=aux->prox;
    }
}	