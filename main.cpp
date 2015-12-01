#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include "Nave.h"
#include "GameObject.h"
#include "GameObjectList.h"
#include "Bullet.h"
#include "Utils.h"
#include "Asteroide.h"
#include "RankingList.h"
#include "Ranking.h"


using namespace std;


int main() {

    if (!al_init()) {
		cout << "Erro inicializando allegro" << endl;
	}

	/*Variavel que verifica estado do jogo*/
    bool finalized = false;
    bool menu = true;
    bool verranking = false;
    /*CONTADOR DA FREQUENCIA DE INIMIGO*/
    int astInimigo = 0;
    int cont=0;
    /* VARIAVEIS PARA MUDAR A POSIÇÃO DO NOVO IMIGO*/
    float astPX = 0;
    bool pause=false;
    bool concluido = false;
    char str[18];

    /*VARIAVEIS DO ALLEGRO*/
	ALLEGRO_DISPLAY *tela = al_create_display(Utils::getLarguraTela(), Utils::getAlturaTela());
	ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE *fila_eventos = al_create_event_queue();
    ALLEGRO_SAMPLE *shoot=NULL, *explosion=NULL, *shipExplosion=NULL;
    ALLEGRO_EVENT evento;
    ALLEGRO_KEYBOARD_STATE estado_teclado;

    /* INSTALÇÕES DO ALLEGRO */
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_acodec_addon();
	al_install_audio();	
	al_reserve_samples(15);
	al_init_font_addon();
	al_init_ttf_addon();

	shoot = al_load_sample( "Sound/shoot.ogg" );
	shipExplosion = al_load_sample("Sound/shipImpact.ogg");
	explosion = al_load_sample("Sound/meteoroCrash.ogg");
	ALLEGRO_FONT *fonte = al_load_ttf_font("fonte/ARCADE.TTF", 50, 0);
	ALLEGRO_FONT *digitar = al_load_ttf_font("fonte/LDFComicSans.ttf", 20,0);
	/*Iniciar Eventos */
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	al_register_event_source(fila_eventos, al_get_display_event_source(tela));
	al_start_timer(timer);
	
	/*Player Nave Do Jogador*/
	Nave *navePlayer = new Nave();
    
    /*OBJETOS DO JOGO, BALAS E INIMIGOS */
    Bullet *bullet = new Bullet();
    Asteroide *aste = new Asteroide();
    Ranking *rk = new Ranking();
    
    /*Lista de Objetos (Inimigos ou Asteroides)*/
    GameObjectList *ListaBullets = new GameObjectList();
    GameObjectList *ListaAsteroides = new GameObjectList();
    RankingList *ListaDoRanking = new RankingList();
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();
    strcpy(str, ""); 

	while (!finalized) {
		al_wait_for_event(fila_eventos, &evento);
		al_get_keyboard_state(&estado_teclado);
		
		if(menu){
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_draw_text(fonte, al_map_rgb(255,0,0), Utils::getLarguraTela()/2, (Utils::getAlturaTela()/2)-al_get_font_ascent(fonte),ALLEGRO_ALIGN_CENTRE, "NOME DO JOGO aqui");
			al_draw_text(fonte, al_map_rgb(255,0,0), 300, 50,ALLEGRO_ALIGN_LEFT, "Novo Jogo");
			al_draw_text(fonte, al_map_rgb(255,0,0), 80, 515-al_get_font_ascent(fonte),ALLEGRO_ALIGN_LEFT, "Ranking");
			al_draw_text(fonte, al_map_rgb(255,0,0), 580, 515-al_get_font_ascent(fonte),ALLEGRO_ALIGN_LEFT, "Sair");
			switch (evento.type){
				case ALLEGRO_EVENT_KEY_DOWN:
					cout << "KEYDOWN: " << evento.keyboard.keycode << endl;
					if(evento.keyboard.keycode == 59 || evento.keyboard.keycode==ALLEGRO_KEY_ESCAPE) {
						finalized = true;
						break;
					}
				case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
					cout << "Mouse Px: " << evento.mouse.x << " Py: " << evento.mouse.y << endl;
					//abrir jogo
					if (evento.mouse.x >=302 && evento.mouse.x <=525 && evento.mouse.y >= 59 && evento.mouse.y <=88){
						al_clear_to_color(al_map_rgb(255, 255, 255));
						//al_flip_display();
						navePlayer->Start();
						menu = false;
						cont = 0;
						break;
					}
					//abrir ranking
					else if(evento.mouse.x >=83 && evento.mouse.x <=232 && evento.mouse.y >= 483 && evento.mouse.y <=513){
						al_clear_to_color(al_map_rgb(255, 255, 255));
						//al_flip_display();
						verranking = true;
						menu = false;
						cont = 0;
						cout << verranking << endl;
						cout << "Devo ir pra o Ranking";
						break;
					}
					//sair
					else if(evento.mouse.x >=585 && evento.mouse.x <=657 && evento.mouse.y >= 483 && evento.mouse.y <=505){
						finalized = true;
						break;
					}
			}
			//al_draw_text(fonte, al_map_rgb(255,0,0), Utils::getLarguraTela()/2, (Utils::getAlturaTela()/2)-al_get_font_ascent(fonte),ALLEGRO_ALIGN_CENTRE, "PLAY");
			al_flip_display();
		}
		else if (verranking){
			int y=25;
			string line;
	        string player, pontos;
	        ifstream abrir ("data/raking.txt");
	        if (abrir.is_open()){
	        	al_flip_display();
	        	al_clear_to_color(al_map_rgb(255, 255, 255));
	        	if (abrir.is_open()){
	        	//al_clear_to_color(al_map_rgb(255, 255, 255)); antigo
		        	for (int i = 0; i < 7; ++i){
		        		getline (abrir,line);
		        		if(line != "!!"){
		                	//cout << line << endl;
			                player=line.substr(0,line.find("|"));
			                pontos=line.substr(line.find("|")+1);
			                al_draw_textf(fonte, al_map_rgb(255,0,0), 25, y,  0, "Player: %s    Kills: %s", Utils::getStringToChar(player), Utils::getStringToChar(pontos));   
		                	y = y+al_get_font_ascent(fonte) +5;
		                }
		                else{
		                	break;
		                }
		        	}
		        }
				al_draw_text(fonte, al_map_rgb(255,0,0), 80, 515-al_get_font_ascent(fonte),ALLEGRO_ALIGN_LEFT, "Voltar");
				al_draw_text(fonte, al_map_rgb(255,0,0), 580, 515-al_get_font_ascent(fonte),ALLEGRO_ALIGN_LEFT, "Sair");
				abrir.close();
			}
			switch (evento.type){
				case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
					cout << "Mouse Px: " << evento.mouse.x << " Py: " << evento.mouse.y << endl;
					if (evento.mouse.x >=81 && evento.mouse.x <=203 && evento.mouse.y >= 483 && evento.mouse.y <=508){
						al_clear_to_color(al_map_rgb(255, 255, 255));
						menu = true;
						cont = 0;
						verranking = false;
						break;
					}
					else if (evento.mouse.x >=582 && evento.mouse.x <=657 && evento.mouse.y >= 483 && evento.mouse.y <=508){
						al_clear_to_color(al_map_rgb(255, 255, 255));
						menu = true;
						cont = 0;
						verranking = false;
						finalized = true;
						break;
					}
			}	
		}
		else{
			//al_clear_to_color(al_map_rgb(255, 255, 255));
			//if(true){
			al_draw_filled_rectangle(0, 0, Utils::getLarguraTela(), Utils::getAlturaInfo(), al_map_rgb(0, 0, 0));
			al_draw_textf(fonte, al_map_rgb(255,0,0), 0, 0,  0, "Kills: %d    Life: %d", navePlayer->kills, navePlayer->vida);
			if(navePlayer->DevoMorrer()){
				al_draw_text(fonte, al_map_rgb(255,0,0), Utils::getLarguraTela()/2, (Utils::getAlturaTela()/2)-al_get_font_ascent(fonte),ALLEGRO_ALIGN_CENTRE, "GAME OVER!");
				al_draw_text(digitar, al_map_rgb(255,0,0), Utils::getLarguraTela()/2, (Utils::getAlturaTela() - al_get_font_ascent(digitar)) / 2,ALLEGRO_ALIGN_CENTRE, "Player: ");
				if(!concluido){
					if(evento.type == ALLEGRO_EVENT_KEY_CHAR){
						if (strlen(str) <= 16){
				            char temp[] = {evento.keyboard.unichar, '\0'};
				            if (evento.keyboard.unichar == ' '){
				                strcat(str, temp);
				            }
				            else if (evento.keyboard.unichar >= '0' &&
				                     evento.keyboard.unichar <= '9'){
				                strcat(str, temp);
				            }
				            else if (evento.keyboard.unichar >= 'A' &&
				                     evento.keyboard.unichar <= 'Z'){
				                strcat(str, temp);
				            }
				            else if (evento.keyboard.unichar >= 'a' &&
				                     evento.keyboard.unichar <= 'z'){
				                strcat(str, temp);
				            }
				        }
				        if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0){
		            		str[strlen(str) - 1] = '\0';
		        		}
				    }
				    if (evento.type == ALLEGRO_EVENT_KEY_DOWN && (evento.keyboard.keycode == ALLEGRO_KEY_ENTER || evento.keyboard.keycode == 91 )){
	                    concluido = true;
	                    string line;
	                    string player;
	                    int pontos=0;
	                    ifstream abrir ("data/raking.txt");
	                    cout<<"O Nome digitado foi: " << str << endl;
	                    if (abrir.is_open()){
	                    	while (! abrir.eof()){
	                    		getline (abrir,line);
	                    		if(line == "!!" ){
	                    			break;
	                    		}
	                    		else{
		                    		cout << line << endl;
		                    		player=line.substr(0,line.find("|"));
		                    		//cout << "A linha ficou assim, apos a quebra: " << line << endl;
		                    		//cout << "O ponto deve ficar assim: " << line.find("|") << endl;
		                    		//cout << "A Pontuacao é: " << line.substr(line.find("|"));
		                    		pontos=Utils::getStringToNumber(line.substr(line.find("|")+1));
		                    		//cout << "Player: " << player << " Pontos: " << pontos << endl;
		                    		rk->Novo(ListaDoRanking, player, pontos);
	                    		}
						    }
						    abrir.close();
						    ///string retornoDaLista;
						    /*retornoDaLista = ListaDoRanking->RetornarLista();
						    cout << "A string montada eh " << retornoDaLista << endl;
						    cout << "Sai do Retornar Lista" << endl;*/
						}

				        ofstream myfile ("data/raking.txt");
				        string raking(str);
				        raking.append("|"); 
				        raking.append(Utils::getNumberToString(navePlayer->kills));
				        //cout << "A String eh " << raking << endl;
				        //cout << "String inserida foi: " << raking << endl;
				        Ranking *nrk = new Ranking(str, navePlayer->kills);
				        ListaDoRanking->Adicionar(nrk);
				        cout << "Devo organizar a lista agora";
				        ListaDoRanking->AdicionarOrdenar();
				        cout << "Sai da lista" <<endl;
				        string retornoDaLista = ListaDoRanking->RetornarLista();
						cout << "A string montada eh " << retornoDaLista << endl;
						cout << "Sai do Retornar Lista" << endl;
						int qtdRanking = Utils::getCountChar(retornoDaLista, ";");
						string inserir;
						int busca;
				        if (myfile.is_open()){
				        	//cout << "A quantidade de ; eh de " << qtdRanking << endl;
				        	//cout << "Entrei no arquivo aberto" << endl;
				        	for (int i = 0; i < qtdRanking; ++i){
				        		busca = retornoDaLista.find(";");
				        		inserir = retornoDaLista.substr(0,busca);
				        		myfile << inserir+"\n";
				        		retornoDaLista = retornoDaLista.erase(0,busca+1);
				        		//cout << "O Retorno depois de apagado ficou: " << retornoDaLista << endl;
				        	}
				        	inserir = "!!";
				        	myfile << inserir;
						    myfile.close();
						    //cout << "Raking salvo" << endl;
						}
						ListaDoRanking->LimparLista();
						
	                }
	            }   
	            //int al_get_text_width(const ALLEGRO_FONT *f, const char *str)
			    if (strlen(str) > 0){
	        		al_draw_text(digitar, al_map_rgb(255, 0, 0), (Utils::getLarguraTela() / 2),
	                     (Utils::getAlturaTela() / 2)+10,
	                     ALLEGRO_ALIGN_CENTRE, str);
	    		}
	 			al_flip_display();
		        al_clear_to_color(al_map_rgb(255, 255, 255));
		        al_draw_text(fonte, al_map_rgb(255,0,0), 80, 515-al_get_font_ascent(fonte),ALLEGRO_ALIGN_LEFT, "Menu");
				al_draw_text(fonte, al_map_rgb(255,0,0), 580, 515-al_get_font_ascent(fonte),ALLEGRO_ALIGN_LEFT, "Sair");
				if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
					cout << "Mouse Px: " << evento.mouse.x << " Py: " << evento.mouse.y << endl;
					//abrir o ranking
					if (concluido == true && evento.mouse.x >=82 && evento.mouse.x <=177 && evento.mouse.y >= 483 && evento.mouse.y <=505){
						cout << "Devo ir pra o menu" << endl;
						menu = true;
						strcpy(str, "");
						concluido = false;
					}
					if (evento.mouse.x >=583 && evento.mouse.x <=658 && evento.mouse.y >= 483 && evento.mouse.y <=505){
						al_clear_to_color(al_map_rgb(255, 255, 255));
						cout << "Devo encerrar" << endl;
						finalized = true;
					}
				}	
			}
			//al_draw_text(fonte, al_map_rgb(255,0,0), Utils::getLarguraTela()/2, Utils::getAlturaTela()/2,ALLEGRO_ALIGN_CENTRE, "GAME OVER!");
			//cout << "O Evento foi de " << evento.type.ALLEGRO_EVENT_DISPLAY_CLOSE << endl;
			switch(evento.type){
				case ALLEGRO_EVENT_TIMER:
					//if(true){
					if(!navePlayer->DevoMorrer() ){
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
						astPX = Utils::getPosicaoAst(astPX);
						
						astInimigo++;
						if(astInimigo >= Utils::getFrequenciaInimigo() && ListaAsteroides->ObjectCont() < Utils::getMaximoInimigo()){
							aste->Novo(ListaAsteroides, astPX, Utils::getVelocidadeAsteroide());
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
						if(navePlayer->Impacto(ListaAsteroides)){
							al_play_sample(shipExplosion, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
						}
						if(ListaBullets->ImpactoFirstElement(navePlayer, ListaAsteroides)){
							al_play_sample(explosion, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
						}	
					}
					else{
						ListaBullets->LimparLista();
						ListaAsteroides->LimparLista();
					}
				break;

				case ALLEGRO_EVENT_KEY_DOWN:
					switch (evento.keyboard.keycode){
						case ALLEGRO_KEY_P:
							if (pause){
								pause = false;
								al_start_timer(timer);
							}
							else{
								pause=true;
								al_stop_timer(timer);
							}
							break;
						case ALLEGRO_KEY_ESCAPE:
							if(pause){
								ListaBullets->LimparLista();
								ListaAsteroides->LimparLista();
								al_start_timer(timer);
								al_clear_to_color(al_map_rgb(255, 255, 255));
								pause = false;
								menu = true;
							}
							else{
								finalized = true;
							}
							break;
						case ALLEGRO_KEY_SPACE:
							if(navePlayer->DevoMorrer()==false && pause	 == false){
								bullet->Novo(*navePlayer, ListaBullets);
								al_play_sample(shoot, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
							}
							break;
					}

					/*if(evento.keyboard.keycode == ALLEGRO_KEY_P){
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
					else if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE && navePlayer->DevoMorrer() == false && pause == false){
						bullet->Novo(*navePlayer, ListaBullets);
						al_play_sample(shoot, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
					}*/
				break;

				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					finalized = true;
				break;
			}
		}

		
	}
	return 0;
}