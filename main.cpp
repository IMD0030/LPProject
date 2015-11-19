#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>
#include <cstring>
#include "Nave.h"
#include "GameObject.h"
#include "GameObjectList.h"
#include "Bullet.h"
#include "Utils.h"
#include <string.h>
#include <sstream>
#include "Asteroide.h"

using namespace std;


int main() {

    if (!al_init()) {
		cout << "Erro inicializando allegro" << endl;
	}

	/*Variavel que verifica estado do jogo*/
    bool finalized = false;
    /*CONTADOR DA FREQUENCIA DE INIMIGO*/
    int astInimigo = 0;
    /* VARIAVEIS PARA MUDAR A POSIÇÃO DO NOVO IMIGO*/
    float astPX = 0;
    bool pause=false;

    /*VARIAVEIS DO ALLEGRO*/
	ALLEGRO_DISPLAY *tela = al_create_display(Utils::getLarguraTela(), Utils::getAlturaTela());
	ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE *fila_eventos = al_create_event_queue();
    ALLEGRO_SAMPLE *shoot=NULL, *explosion=NULL;
    ALLEGRO_EVENT evento;
    ALLEGRO_KEYBOARD_STATE estado_teclado;

    /* INSTALÇÕES DO ALLEGRO */
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_acodec_addon();
	al_install_audio();	
	al_reserve_samples(10);
	shoot = al_load_sample( "Sound/shoot.ogg" );
	explosion = al_load_sample("Sound/explosion.wav");
	/*Iniciar Eventos */
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	al_register_event_source(fila_eventos, al_get_display_event_source(tela));
	al_start_timer(timer);
	

    /*Player Nave Do Jogador*/
    Nave *navePlayer = new Nave(Utils::getLarguraTela()/2, Utils::getAlturaTela());
    /*OBJETOS DO JOGO, BALAS E INIMIGOS */
    Bullet *bullet = new Bullet();
    Asteroide *aste = new Asteroide();

    /*Lista de Objetos (Inimigos ou Asteroides)*/
    GameObjectList *ListaBullets = new GameObjectList();
    GameObjectList *ListaAsteroides = new GameObjectList();
    
	 /*ALLEGRO_EVENT_DISPLAY_CLOSE:
							finalizado = true;*/
	//testes
	//aste->Novo(ListaAsteroides, LARGURA/2, 2, 2);
	//al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
	while (!finalized) {
		al_wait_for_event(fila_eventos, &evento);
		al_get_keyboard_state(&estado_teclado);
		//cout << "O Evento foi de " << evento.type.ALLEGRO_EVENT_DISPLAY_CLOSE << endl;
		switch(evento.type){
			case ALLEGRO_EVENT_TIMER:		
				
				if(al_key_down(&estado_teclado, ALLEGRO_KEY_W) || al_key_down(&estado_teclado, ALLEGRO_KEY_UP)) {
					navePlayer->Up();
				}
				if(al_key_down(&estado_teclado, ALLEGRO_KEY_S) || al_key_down(&estado_teclado, ALLEGRO_KEY_DOWN)) {
					navePlayer->Down();
				}
				if(al_key_down(&estado_teclado, ALLEGRO_KEY_A) || al_key_down(&estado_teclado, ALLEGRO_KEY_LEFT)) {
					navePlayer->Left();
				}
				if(al_key_down(&estado_teclado, ALLEGRO_KEY_D) || al_key_down(&estado_teclado, ALLEGRO_KEY_RIGHT)){
					navePlayer->Right();
				}
				/*if(al_key_down(&estado_teclado, ALLEGRO_KEY_SPACE) || al_key_down(&estado_teclado, ALLEGRO_KEY_SPACE)){
					bullet->Novo(*navePlayer, ListaBullets);
					al_play_sample(shoot, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				}*/

				/*while(oldastPX == astPX){
					astPX = (rand()%(Utils::getLarguraTela()-1))+1;
					//astPX = (rand()%-2+(Utils::getLarguraTela()+1));
				}
				oldastPX=astPX;*/
				//velPY = rand()%(10-2)+2;
				astPX = Utils::getPosicaoAst(astPX);
				
				astInimigo++;
				if(astInimigo >= Utils::getFrequenciaInimigo() && ListaAsteroides->ObjectCont() < Utils::getMaximoInimigo()){
					aste->Novo(ListaAsteroides, astPX, Utils::getVelocidadeAsteroide());
					//aste->Novo(ListaAsteroides, Utils::getLarguraTela()+1, 2);
					astInimigo = 0;
				}

				// desenhar
				ListaBullets->Render();
				ListaAsteroides->Render();
				navePlayer->Render();

				al_flip_display();
				al_clear_to_color(al_map_rgb(255, 255, 255));

				// atualizar estado
				ListaBullets->Update();
				ListaAsteroides->Update();
				navePlayer->Impacto(ListaAsteroides);
				if(navePlayer->DevoMorrer()){
					cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;
	                cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;
	                cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;
	                cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;
	                cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;
	                cout << "DESCULPE, MAS O JOGO ACABOU, O JOGO TERMINOU, DESTRUA A NAVE" << endl;
				}

				if(ListaBullets->ImpactoFirstElement(navePlayer, ListaAsteroides)){
					//al_play_sample(explosion, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

				}
			break;

			case ALLEGRO_EVENT_KEY_DOWN:
				if(evento.keyboard.keycode == ALLEGRO_KEY_P){
					if (pause){
						pause = false;
						al_start_timer(timer);
					}
					else{
						pause=true;
						al_stop_timer(timer);
					}
				}
				else if(evento.keyboard.keycode == 59 || evento.keyboard.keycode==ALLEGRO_KEY_ESCAPE) {
					finalized = true;
				}
				else if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
					bullet->Novo(*navePlayer, ListaBullets);
					//al_play_sample(shoot, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				}
			break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				finalized = true;
			break;
		}
	}
	return 0;
}