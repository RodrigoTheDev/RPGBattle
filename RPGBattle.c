#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Criado por @RodrigoTheDev
//Favor deixar créditos caso use este código


//statuso dos monstros
struct stats
{
	char nome[20];
	int hp;
	int mp;
};

struct statsp2
{
	char nome[20];
	int hp;
	int mp;
};

struct monster_stats
{
	int hp;
	int dmg;
};

struct magic
{
	//fireball[dmg, cost]
	
	//dano
	int fireball[2]; //dano entre 15 e 30
	int punch[2]; //dano entre 0 e 4
	int swordslash[2]; //dano entre 5 e 10
	
	//status
	int cura[2]; //cura instantaneamente uma quantidade de hp (entre 8 e 10)
};

int main()
{
	setlocale(LC_ALL, "Portuguese");
	srand(time(NULL));
	
	FILE *arq;
	FILE *xp;
	
	struct stats Stats;
	struct statsp2 p2;
	struct monster_stats Mstats;
	struct magic Magic;
	
	//variáveis de controle
	int select;
	int selectp2;
	
	//controle de loop
	int game=1;
	int menu=1;
	int arcade=0;
	int partida=0;
	int multiplayer = 0;
	
	int i;
	//pontuação
	int score = 0;
	int hScore = 0;
	int printscore = 0;
	
	//xp points
	int exp = 0;
	int level = 0;
	
	int critrate;
	int climit = 2;

	//loop universal de todas as coisas
	while(game==1)
	{
		//Menu principal
		while(menu == 1)
		{
			//abrindo o arquivo
			arq = fopen("highscore.txt", "r");
			fscanf(arq, "%d", &printscore);
			
			//carregando seu xp:
			xp = fopen("lvlcount.txt", "r");
			fscanf(xp, "%d %d", &exp, &level);
			fclose(arq);
			
			printf("=====TXTale=====\n");
			printf("===Versão 1.2b==\n");
			printf("Maior pontuação: %d |Seu nível: %d\n", printscore, level);
			printf("[1]Jogar modo arcade\n[2]Jogar modo multijogador\n[3]Como jogar\n[0]sair\n[10]Changelog(NOVIDADES)\n");
			printf("ação: ");
			scanf("%i", &select);
			fflush(stdin);
			
			system("cls");
			
			switch(select)
			{
				case 1:
					
					menu = 0;
					arcade = 1;
					partida = 1;
					break;
				case 2:
					menu = 0;
					multiplayer = 1;
					break;
					
				case 3:
					
					printf("====INSTRUÇÕES====\n");
					printf("> O jogo é dividido por turnos, onde cada um tem a sua vez de atacar\n> Todos os ataques custam MANA, então não gaste tudo de uma vez\n> No final de cada rodada, você recebe +3 de mana\n");
					printf("====MOVIMENTOS====\n");
					printf("punch: você dá um soco, causando entre 0 e 4 de dano\n");
					printf("fireball: você lança uma bola de fogo, causando entre 15 e 30 de dano\n");
					printf("sword slash: você ataca com a espada, causando entre 5 e 10 de dano\n");
					printf("heal: Você cura entre 8 e 10 de hp\n");
					printf("[0]Voltar\n");
					scanf("%i", &select);
					system("cls");
					break;
					
				case 10:
					
					printf("=====VERSÃO 1.2b=====\n");
					printf("> adicionado sistema de xp e level, ainda em desenvolvimento\n");
					printf("=====VERSÃO 1.2=====\n");
					printf("> adicionado modo multiplayer\n");
					printf("> adicionado changelogs\n");
					sleep(5);
					system("cls");
					break;
					
				case 0:
					system("pause");
					return 0;
					
			} //fechando a decisão do menu switch(select)
			
		} //fechando o menu while(menu==1)
		
		fclose(arq);
		
		//Stats de inicio de jogo
		Stats.hp = 30;
		Stats.mp = 20;
		
		p2.hp = 30;
		p2.mp = 20;
		
		//definindo o custo de cada magia
		Magic.punch[1] = 0;
		Magic.fireball[1] = 10;
		Magic.swordslash[1] = 2;
		Magic.cura[1] = 10;
		
		system("cls");
		
		//escolhendo nome
		printf("Insira o nome do aventureiro: ");
		gets(Stats.nome);
		
		if(select == 2)
		{
			printf("Insira o nome do player 2: ");
			gets(p2.nome);
		}
		
		//COMBATE ARCADE
		while(arcade == 1)
		{
			Mstats.hp = (5+rand()%5+1)*10;
			while(partida == 1)
			
			{
				//critico
				critrate = rand()%9;
				
				//randomizando o dano
				Magic.punch[0] = (level/3) + rand()%4+1;
				Magic.fireball[0] = (level/3) + 15+rand()%15;
				Magic.swordslash[0] = (level/3) + 5+rand()%5;
				
				//randomizando o status
				Magic.cura[0] = (level/3) + 10;
				
				//dano do monstro
				Mstats.dmg = rand()%7+1;
				
				//Menu de opções de ataques
				
				printf("pontuação atual: %i\n",score);
				
				printf("Monstro: %i   %s: %i\n",Mstats.hp, Stats.nome, Stats.hp);
				printf("Mana points: %i\n", Stats.mp);
				
				printf("[1]punch(Custo:%i) | [2]fireball(Custo:%i)\n[3]sword slash(Custo:%i) | [4]heal(Custo:%i)\n"
				,Magic.punch[1], Magic.fireball[1], Magic.swordslash[1], Magic.cura[1]);
				
				printf("ação>>> ");
				scanf("%i", &select);
				fflush(stdin);
				
				//executando a ação
				switch(select)
				{
					case 1:
						sleep(1);
						
						//chance de critico
						if(critrate <= climit)
						{
							printf("CRÍTICO!\n");
							Magic.punch[0] = Magic.punch[0] * 2;
						}
						
						if(Stats.mp < Magic.punch[1])
						{
							printf("Voce não tem mana o suficiente\n");
							break;
						}
						printf("Voce atacou com SOCO e causou %i de dano\n", Magic.punch[0]);
						Mstats.hp = (Mstats.hp)-(Magic.punch[0]); // Dano que o inimigo toma
						Stats.mp = Stats.mp-Magic.punch[1]; // Custo de mana
						break;
						
					case 2:
						sleep(1);
						
						//pouca magia:
						if(Stats.mp < Magic.fireball[1])
						{
							printf("Voce não tem mana o suficiente\n");
							break;
						}
						
						//chance de critico
						if(critrate <= climit)
						{
							printf("CRÍTICO!\n");
							Magic.fireball[0] = Magic.fireball[0] * 2;
						}
						
						printf("Voce atacou com BOLA DE FOGO e causou %i de dano\n", Magic.fireball[0]);
						Mstats.hp = (Mstats.hp)-(Magic.fireball[0]); // Dano que o inimigo toma
						Stats.mp = (Stats.mp) - (Magic.fireball[1]); // Custo de mana
						break;
						
					case 3:
						sleep(1);
						
						//pouca magia:
						if(Stats.mp < Magic.swordslash[1])
						{
							printf("Voce não tem mana o suficiente\n");
							break;
						}
						
						//chance de critico
						if(critrate <= climit)
						{
							printf("CRÍTICO!\n");
							Magic.swordslash[0] = Magic.swordslash[0] * 2;
						}

						printf("Voce atacou com ESPADADA e causou %i de dano\n", Magic.swordslash[0]);
						Mstats.hp = (Mstats.hp)-(Magic.swordslash[0]); // Dano que o inimigo toma
						Stats.mp = (Stats.mp) - (Magic.swordslash[1]); // Custo de mana
						break;
					case 4:
						sleep(1);
						//pouca magia:
						if(Stats.mp < Magic.cura[1])
						{
							printf("Voce não tem mana o suficiente\n");
							break;
						}
						//condições de vida máxima
						if(Stats.hp == 30)
						{
							printf("Voce já esta com a vida máxima\n");
							break;
						}
						
						printf("Você curou %i de hp\n", Magic.cura[0]);
						
						Stats.hp = Stats.hp + Magic.cura[0];
						Stats.mp = (Stats.mp) - (Magic.cura[1]);
						break;
					case 0:
						
						printf("Você desistiu!\n");
						Stats.hp = 0;
						
						sleep(1);
						
						break;
					default:
						printf("comando não reconhecido\n");
						break;
				}
		
				//Condição de vitória
				if(Mstats.hp <= 0 && Stats.hp > 0)
				{
					sleep(2);
					
					system("cls");
					
					printf("\nVOCE VENCEU!\n");
					
					exp += 5;
					if(exp >= 20) {
						
						printf("Você subiu de nível!\n");
						
						level++;
						
						exp = 0;
						
					}
					//score
					score = score + 100;
					sleep(2);
					system("cls");
					break;
				}
				
				//ataque do monstro
				sleep(1);
				
				printf("O monstro atacou e causou %i de dano\n\n", Mstats.dmg);
				
				Stats.hp = (Stats.hp) - (Mstats.dmg);
				
				// condição de vida máxima
				if(Stats.hp > 30)
				{
					Stats.hp = 30;
				}
				
				sleep(2);
				system("cls"); //limpa a tela
				
		
				//condição de derrota
				if (Stats.hp <= 0 && Mstats.hp > 0)
				{
					printf("\nVOCE PERDEU!\n");
					printf("E MARCOU %i pontos", score);
					
					hScore = printscore;
					
					//salvando a pontuação maior
					if(hScore < score)
					{
						hScore = score;
						arq = fopen("highscore.txt", "w");
						fprintf(arq, "%d", hScore);
						fclose(arq);
					}
					
					//salvando seu xp:
					xp = fopen("lvlcount.txt", "w");
					fprintf(xp, "%d %d", exp, level);
					fclose(arq);
					
					partida = 0;
					arcade = 0;
					menu = 1;
					sleep(2);
					system("cls");
				}
				score = score+10;
				Stats.mp = level + Stats.mp + 3;
			}
		} //fechando o loop do modo arcade
		
		//COMBATE MULTIPLAYER
		while(multiplayer == 1)
		{
			
			//critico
			critrate = rand()%9;
			
			//randomizando o dano
			Magic.punch[0] = rand()%4+1;
			Magic.fireball[0] = 15+rand()%15;
			Magic.swordslash[0] = 5+rand()%5;
			
			//randomizando o status
			Magic.cura[0] = 10;
			
			//HUD
			//player 1
			printf("%s: %i\n",Stats.nome,Stats.hp);
			printf("Mana points: %i\n", Stats.mp);
			
			printf("[1]punch(Custo:%i) | [2]fireball(Custo:%i)\n[3]sword slash(Custo:%i) | [4]heal(Custo:%i)\n"
			,Magic.punch[1], Magic.fireball[1], Magic.swordslash[1], Magic.cura[1]);
			
			printf("ação>>> ");
			scanf("%i", &select);
			fflush(stdin);
			sleep(1);
			system("cls");
			//player 2
			printf("%s: %i\n",p2.nome,p2.hp);
			printf("Mana points: %i\n", p2.mp);
			
			printf("[1]punch(Custo:%i) | [2]fireball(Custo:%i)\n[3]sword slash(Custo:%i) | [4]heal(Custo:%i)\n"
			,Magic.punch[1], Magic.fireball[1], Magic.swordslash[1], Magic.cura[1]);
			
			printf("ação>>> ");
			scanf("%i", &selectp2);
			fflush(stdin);
			
			//executando a ação
			//ação do player 1
			switch(select)
			{
				case 1:
					sleep(1);
					
					//chance de critico
					if(critrate <= climit)
					{
						printf("CRÍTICO!\n");
						Magic.punch[0] = Magic.punch[0] * 2;
					}
					
					if(Stats.mp < Magic.punch[1]) {
						printf("%s não tem mana o suficiente\n",Stats.nome);
						break;
					}
					
					printf("%s atacou com SOCO e causou %i de dano\n",Stats.nome, Magic.punch[0]);
					
					p2.hp = (p2.hp)-(Magic.punch[0]); // Dano que o inimigo toma
					Stats.mp = Stats.mp-Magic.punch[1]; // Custo de mana
					break;
					
				case 2:
					
					sleep(1);
					
					//pouca magia:
					if(Stats.mp < Magic.fireball[1])
					{
						printf("%s não tem mana o suficiente\n",Stats.nome);
						break;
					}
					
					//chance de critico
					if(critrate <= climit)
					{
						printf("CRÍTICO!\n");
						Magic.fireball[0] = Magic.fireball[0] * 2;
					}
					
					printf("%s atacou com BOLA DE FOGO e causou %i de dano\n",Stats.nome, Magic.fireball[0]);
					p2.hp = (p2.hp)-(Magic.fireball[0]); // Dano que o inimigo toma
					Stats.mp = (Stats.mp) - (Magic.fireball[1]); // Custo de mana
					break;
					
				case 3:
					sleep(1);
					
					//pouca magia:
					if(Stats.mp < Magic.swordslash[1])
					{
						printf("%s não tem mana o suficiente\n",Stats.nome);
						break;
					}
					
					//chance de critico
					if(critrate <= climit)
					{
						printf("CRÍTICO!\n");
						Magic.swordslash[0] = Magic.swordslash[0] * 2;
					}

					printf("%s atacou com ESPADADA e causou %i de dano\n",Stats.nome, Magic.swordslash[0]);
					
					p2.hp = (p2.hp)-(Magic.swordslash[0]); // Dano que o inimigo toma
					Stats.mp = (Stats.mp) - (Magic.swordslash[1]); // Custo de mana
					break;
				case 4:
					sleep(1);
					//pouca magia:
					if(Stats.mp < Magic.cura[1])
					{
						printf("%s não tem mana o suficiente\n",Stats.nome);
						break;
					}
					//condições de vida máxima
					if(Stats.hp == 30)
					{
						printf("%s já esta com a vida máxima\n",Stats.nome);
						break;
					}
					
					printf("%s curou %i de hp\n",Stats.nome, Magic.cura[0]);
					Stats.hp = Stats.hp + Magic.cura[0];
					Stats.mp = (Stats.mp) - (Magic.cura[1]);
					
					break;
					
				default:
					printf("comando não reconhecido\n");
					break;
			} //fechando a ação do p1
			
			sleep(1);
			//player 2
			switch(selectp2)
			{
				case 1: //PUNCH
					sleep(1);
					//chance de critico
					if(critrate <= climit)
					{
						printf("CRÍTICO!\n");
						Magic.punch[0] = Magic.punch[0] * 2;
					}
					if(p2.mp < Magic.punch[1])
					{
						printf("%s não tem mana o suficiente\n",p2.nome);
						break;
					}
					printf("%s atacou com SOCO e causou %i de dano\n",p2.nome, Magic.punch[0]);
					Stats.hp = (Stats.hp)-(Magic.punch[0]); // Dano que o inimigo toma
					p2.mp = p2.mp-Magic.punch[1]; // Custo de mana
					break;
					
				case 2: //FIREBALL
					sleep(1);
					
					//pouca magia:
					if(p2.mp < Magic.fireball[1])
					{
						printf("%s não tem mana o suficiente\n",p2.nome);
						break;
					}
					
					//chance de critico
					if(critrate <= climit)
					{
						printf("CRÍTICO!\n");
						Magic.fireball[0] = Magic.fireball[0] * 2;
					}
					printf("%s atacou com BOLA DE FOGO e causou %i de dano\n",p2.nome, Magic.fireball[0]);
					
					Stats.hp = (Stats.hp)-(Magic.fireball[0]); // Dano que o inimigo toma
					p2.mp = (p2.mp) - (Magic.fireball[1]); // Custo de mana
					break;
					
				case 3: //SWORD SLASH
					sleep(1);
					
					//pouca magia:
					if(p2.mp < Magic.swordslash[1])
					{
						printf("%s não tem mana o suficiente\n",p2.nome);
						break;
					}
					
					//chance de critico
					if(critrate <= climit)
					{
						printf("CRÍTICO!\n");
						Magic.swordslash[0] = Magic.swordslash[0] * 2;
					}

					printf("%s atacou com ESPADADA e causou %i de dano\n",p2.nome, Magic.swordslash[0]);
					Stats.hp = (Stats.hp)-(Magic.swordslash[0]); // Dano que o inimigo toma
					p2.mp = (p2.mp) - (Magic.swordslash[1]); // Custo de mana
					break;
				case 4: //CURA
					sleep(1);
					//pouca magia:
					if(p2.mp < Magic.cura[1])
					{
						printf("%s não tem mana o suficiente\n",p2.nome);
						break;
					}
					//condições de vida máxima
					if(p2.hp == 30)
					{
						printf("%s já esta com a vida máxima\n",p2.nome);
						break;
					}
					
					printf("%s curou %i de hp\n",p2.nome, Magic.cura[0]);
					p2.hp = p2.hp + Magic.cura[0];
					p2.mp = (p2.mp) - (Magic.cura[1]);
					break;
				default:
					printf("comando não reconhecido\n");
					break;
			} //fechando a seleção do p2
			sleep(1);
			
			//condição de vitória
			//vitoria do player 1
			if(p2.hp <= 0 && Stats.hp > 0)
			{
				printf("O VENCEDOR É %s!\n", Stats.nome);
				sleep(3);
				multiplayer = 0;
				partida = 0;
				menu = 1;
				system("cls");
				break;
			}
			
			//vitória do player2
			if(Stats.hp <= 0 && p2.hp > 0)
			{
				printf("O VENCEDOR É %s!\n", p2.nome);
				sleep(3);
				multiplayer = 0;
				partida = 0;
				menu = 1;
				system("cls");
				break;
			}
			
			//empate
			if(Stats.hp == 0 && p2.hp == 0)
			{
				printf("EMPATE!\n");
				sleep(3);
				multiplayer = 0;
				partida = 0;
				menu = 1;
				system("cls");
				break;
			}
			
			
			// condição de vida máxima
			if(Stats.hp > 30)
			{
				Stats.hp = 30;
			}
			
			if(p2.hp > 30)
			{
				p2.hp = 30;
			}
			
			system("cls"); //limpa a tela
			//stats de final de rodada
			Stats.mp = Stats.mp + 3;
			p2.mp = p2.mp + 3;
		} //fechando o loop do multiplayer
	} // fechando loop do game;
}
