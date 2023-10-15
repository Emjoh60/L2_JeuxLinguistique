#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include "struc.h"
#define TEMPS 2000
#define FREQUENCE 96000

/*##########################################################################################################################################################
                                                        FONCTIONS DIVERSES
##########################################################################################################################################################*/

// Fonction d'ajustage d'une ligne entrée

void ajust(char chaine[STRTAILLE],char renvoie[STRTAILLE],int affichage)
    {
        int i=1,j=0;
/*Dans le cas où la chaine est ajustée pour être affichée on ne supprime pas la première case qui est un espace afin qu'elle s'affiche correctement*/
        if(affichage)
            {
                i=0;
            }

        while(chaine[i]!='\0')
            {

/*Gestion des majuscules par remplacemnt des lettres en majuscules par des en minuscule*/

                if((chaine[i]<91)&&(chaine[i]>64))
                    {
                        renvoie[j]=chaine[i]+32;
                    }

/*Gestion des accents par remplacement de ceux-ci par des lettres sans accents*/
                else if(chaine[i]==-61)
                    {
                        if((chaine[i+1]<=-92)&&(chaine[i+1]>=-96))
                            {
                                renvoie[j]='a';
                            }
                        else if((chaine[i+1]<=-85)&&(chaine[i+1]>=-88))
                            {
                                renvoie[j]='e';
                            }
                        else if((chaine[i+1]<=-81)&&(chaine[i+1]>=-84))
                            {
                                renvoie[j]='i';
                            }
                        else if(chaine[i+1]==-79)
                            {
                                renvoie[j]='n';
                            }
                        else if((chaine[i+1]<=-74)&&(chaine[i+1]>=-78))
                            {
                                renvoie[j]='o';
                            }  
                        else if((chaine[i+1]<=-68)&&(chaine[i+1]>=-71))
                            {
                                renvoie[j]='u';
                            }  
                        else if((chaine[i+1]==-67)||(chaine[i+1]>=-65))
                            {
                                renvoie[j]='y';
                            }
                        else
                            {
                                printf("Erreur\n");
                            } 
                        i++; /*On incrémente le compteur une première fois ici étant donné que les accents prennent deux cases du tableau*/
                    } 

/*Sinon on copie normalement chaque caractère*/
                else
                    {
                        renvoie[j]=chaine[i];
                    }
                i++; 
                j++;
            }
        renvoie[j]=chaine[i];
/*Si on est dans le cas de l'affichage on met la première lettre en majuscule pour enjoliver le rendu du texte*/
        if(affichage && !((renvoie[1]<91)&&(renvoie[1]>64)))
            {
                renvoie[1]=renvoie[1]-32;
            }
    }
    
// Fonction permettant de changer de joueur
int changplay(int play)
    {
        if(!play)
            {
                play=1;
            }
        else
            {
                play=0;
            }
        return play;
    }

// Fonction permettant d'afficher les chaînes de manière nette

void net(char tab[STRTAILLE])
    {
        int i;
        /*On remplit le reste de la chaine avec des espaces afin qu'elle soit affichée de manière nette*/
        for(i=strlen(tab);i<STRTAILLE-1;i++)
            {
                tab[i]=' ';
            }
        tab[i+1]='\0';
    }

// Fonction de tirage au sort 

int tirage(int nbmots)
    {
        int ret;
        srand(time(NULL));
        /* Comme il s'agit d'un tirage pour un tableau, on fait en sorte que la valeur ne soit jamais égale au nombre de mots donc on ne rajoute pas 1*/
        ret=rand()%(nbmots);
        return ret;
    }

// Fonction de test d'une position
int testposition(SDL_Event even,SDL_Rect rect)
    {
        if((even.motion.x>=rect.x)&&(even.motion.x<=(rect.x+rect.w)))
            {
                if((even.motion.y>=rect.y)&&(even.motion.y<=(rect.y+rect.h)))
                    {
                        return 1;
                    }
            }
        return 0;
    }    

/*##########################################################################################################################################################
                                            FONCTIONS DE CREATION DES TEXTURES ET DE MODIFICATION
##########################################################################################################################################################*/

// Fonction d'initialisation d'une texture du menu
SDL_Texture* inittextmenu(SDL_Renderer* renderer,SDL_Texture* tglob,char* cj1,char* cj2,char* cstop,char* lang,SDL_Rect j1,SDL_Rect j2,SDL_Rect stopb,SDL_Rect soundb,SDL_Rect langb)
    {
        SDL_Texture* tfond=NULL;

        SDL_SetRenderTarget(renderer,tglob);
        
        tfond= IMG_LoadTexture(renderer,"fond/fond.jpg");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MENU 1\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, NULL); 

        tfond= IMG_LoadTexture(renderer,cj1);
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MENU 2\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &j1); 


        tfond= IMG_LoadTexture(renderer,cj2);
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MENU 3\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &j2);


        tfond= IMG_LoadTexture(renderer,cstop);
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MENU 4\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &stopb); 


        tfond= IMG_LoadTexture(renderer,"fond/sound.png");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MENU 5\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &soundb); 

        tfond= IMG_LoadTexture(renderer,lang);
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MENU 6\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &langb); 

        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(tfond);
        SDL_SetRenderTarget(renderer,NULL);
        return tglob;
    }

//Fonction de création de l'écran du language

SDL_Texture* initttextlang(SDL_Renderer* renderer,SDL_Texture* tglob,SDL_Rect rbri,SDL_Rect rger,SDL_Rect rita,SDL_Rect rspa,SDL_Rect rltexte)
    {
        SDL_Texture* tfond=NULL;

        SDL_SetRenderTarget(renderer,tglob);
        
        tfond= IMG_LoadTexture(renderer,"fond/fond.jpg");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture LANG 1\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, NULL); 

        tfond= IMG_LoadTexture(renderer,"fond/bri.png");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture LANG 2\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &rbri); 


        tfond= IMG_LoadTexture(renderer,"fond/ger.png");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture LANG 3\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &rger);


        tfond= IMG_LoadTexture(renderer,"fond/ita.png");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture LANG 4\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &rita); 


        tfond= IMG_LoadTexture(renderer,"fond/spa.png");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture LANG 5\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &rspa); 

        tfond= IMG_LoadTexture(renderer,"fond/ltexte.png");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture LANG 6\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &rltexte); 

        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(tfond);
        SDL_SetRenderTarget(renderer,NULL);
        return tglob;
    }

//Fonction de création de la texture principale du jeu

SDL_Texture* inittextmain(SDL_Renderer* renderer,SDL_Texture* tglob,char* image,SDL_Rect rimage,SDL_Rect rframe,SDL_Rect rtexte,SDL_Rect stopb,SDL_Rect soundb)
    {
        SDL_Texture* tfond=NULL;

        SDL_SetRenderTarget(renderer,tglob);
        
        tfond= IMG_LoadTexture(renderer,"fond/fondm.jpg");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MAIN 1\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, NULL); 

        tfond= IMG_LoadTexture(renderer,"fond/frame.png");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MAIN 2\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &rframe); 

        tfond= IMG_LoadTexture(renderer,image);
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MAIN 3\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &rimage); 


        tfond= IMG_LoadTexture(renderer,"fond/fondtxt.png");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MAIN 4\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &rtexte);


        tfond= IMG_LoadTexture(renderer,"fond/stop.png");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MAIN 5\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &stopb); 


        tfond= IMG_LoadTexture(renderer,"fond/sound.png");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture MAIN 6\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &soundb); 
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(tfond);
        SDL_SetRenderTarget(renderer,NULL);
        return tglob;
    }

//Fonction de création de la texture pour le mode à 2 joueurs

SDL_Texture* inittextj2(SDL_Renderer* renderer,SDL_Texture* text,char * conseil,SDL_Rect rtexte,SDL_Rect rconseil)
    {
        SDL_Texture* tfond=NULL;

        SDL_SetRenderTarget(renderer,text);
        
        tfond= IMG_LoadTexture(renderer,"fond/fond.jpg");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture J2 1\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, NULL); 

        tfond= IMG_LoadTexture(renderer,"fond/fondtxt.png");
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture J2 2\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &rtexte); 

        tfond= IMG_LoadTexture(renderer,conseil);
        if(tfond==NULL)
            {
                printf("Erreur lors de la création de la texture J2 3\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, tfond, NULL, &rconseil); 

        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(tfond);
        SDL_SetRenderTarget(renderer,NULL);
        return text;
    }

// Fonction de modification d'une texture

void modif(SDL_Renderer* renderer,SDL_Texture* tglob,char* image,SDL_Rect zone)
    {
        SDL_Texture * tzone;
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer,tglob);
        tzone=IMG_LoadTexture(renderer,image);
        SDL_RenderCopy(renderer, tzone, NULL,&zone); 
        SDL_SetRenderTarget(renderer,NULL);
        SDL_RenderCopy(renderer, tglob, NULL,NULL); 
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(tzone);
    }

/*##########################################################################################################################################################
                                                            FONCTIONS COMPLEMENTAIRES
##########################################################################################################################################################*/

// Fonction permettant l'affichage du score

void affscore(SDL_Renderer* renderer,SDL_Texture* textmain, SDL_Rect rect,int joueur, int score[2])
    {
        char chaine[STRTAILLE];
        /*Création de la police*/
        TTF_Font * font=NULL;
        font=TTF_OpenFont("fond/Timeless-Bold.ttf",50);
        if(font==NULL)
            {
                printf("Erreur lors du chargement de la police\n");
            }

        SDL_Color white={255,255,255};

        /*Initialisation de la chaine à afficher*/
        if(joueur==0)
            {
                sprintf(chaine,"Score Joueur 1 : %d",score[joueur]);
            }
        else
            {
                sprintf(chaine,"Score Joueur 2 : %d",score[joueur]);
            }
        net(chaine);

        /*Affichage du score sur le rendu*/
        SDL_Texture * txttexte;
        SDL_Surface * zonetxt=TTF_RenderText_Solid(font,chaine,white);
        if(zonetxt!=NULL)
            {
                SDL_SetRenderTarget(renderer,textmain);
                txttexte=SDL_CreateTextureFromSurface(renderer,zonetxt);
                SDL_RenderCopy(renderer, txttexte, NULL,&rect); 
                SDL_SetRenderTarget(renderer,NULL);
                SDL_RenderCopy(renderer, textmain, NULL,NULL); 
                SDL_RenderPresent(renderer);
                SDL_FreeSurface(zonetxt); 
                SDL_DestroyTexture(txttexte);
            }
        else
            {
                printf("Erreur lors de l'affichage du texte\n");
            }
    }

// Fonction permettant de mettre à jour l'affichage des tentatives

void updattempt(SDL_Renderer* renderer,SDL_Texture* textmain,SDL_Rect ratt1,SDL_Rect ratt2,SDL_Rect ratt3,SDL_Rect ratt4,int attempt)
    {
        /*Si il n'y a pas eu d'essai on affiche toute les images*/
        if(attempt==4)
            {
                modif(renderer,textmain,"fond/firefly2.png",ratt1);
                modif(renderer,textmain,"fond/firefly1.png",ratt2);
                modif(renderer,textmain,"fond/firefly2.png",ratt3);
                modif(renderer,textmain,"fond/firefly1.png",ratt4);
            }
        /*Sinon on change l'image correspondante*/
        else if(attempt==3)
            {
                modif(renderer,textmain,"fond/firefly1o.png",ratt4);
            }
        else if(attempt==2)
            {
                modif(renderer,textmain,"fond/firefly2o.png",ratt3);
            }
        else if(attempt==1)
            {
                modif(renderer,textmain,"fond/firefly1o.png",ratt2);
            }
        else
            {
                modif(renderer,textmain,"fond/firefly2o.png",ratt1);
            }
    }

/*##########################################################################################################################################################
                                                        FONCTIONS D'AFFICHAGES ET DE GESTION
##########################################################################################################################################################*/

// Fonction d'affichage et de gestion du menu
/* On lui passe en paramètre toutes les textures du menu,les rectangles correspondants aux différentes 
zones de la texture ainsi que l'addresse des variables rendant compte de l'état du volume*/

int menu(SDL_Renderer* renderer,SDL_Texture* text0,SDL_Texture* text1,SDL_Texture* text2,SDL_Texture* text3,SDL_Texture* text4,SDL_Rect j1,SDL_Rect j2,SDL_Rect stopb,SDL_Rect soundb,SDL_Rect langb,int * musicstate,int * volume) 
    {
        /*On initialise trois variables, la première pour faire tourner le programme,la deuxième pour connaitre l'état de l'affichage et la troisième pour retourner le choix de l'utilisateur*/
        int run=1,stat=0,retour;

        /*On affiche la texture du menu*/
        SDL_RenderCopy(renderer, text0, NULL,NULL); 
        SDL_RenderPresent(renderer);

        SDL_Event events; 

        while(run)
            {
                while(SDL_PollEvent(&events))
                    {
                        switch(events.type)
                            {
                                case SDL_MOUSEMOTION : 
                                /*Dans chacun des cas si la souris passe sur un bouton et que ce bouton n'est pas déjà mis en avant 
                                on change l'affichage et on change la variable d'état afin d'indiquer que ce bouton est déjà mis en avant*/
                                    if(stat!=1&&testposition(events,j1))
                                        {
                                            SDL_RenderClear(renderer);
                                            SDL_RenderCopy(renderer, text1, NULL,NULL); 
                                            SDL_RenderPresent(renderer);
                                            stat=1;
                                        }
                                    else if(stat!=2&&testposition(events,j2))
                                        {
                                            SDL_RenderClear(renderer);
                                            SDL_RenderCopy(renderer, text2, NULL,NULL); 
                                            SDL_RenderPresent(renderer);
                                            stat=2;
                                        }
                                    else if(stat!=3&&testposition(events,stopb))
                                        {
                                            SDL_RenderClear(renderer);
                                            SDL_RenderCopy(renderer, text3, NULL,NULL); 
                                            SDL_RenderPresent(renderer);       
                                            stat=3;                                
                                        }
                                    else if(stat!=4&&testposition(events,langb))
                                        {
                                            SDL_RenderClear(renderer);
                                            SDL_RenderCopy(renderer, text4, NULL,NULL); 
                                            SDL_RenderPresent(renderer);       
                                            stat=4;                                
                                        }
                                    /*Dans le cas où aucune des zones n'est survollée par la souris 
                                    et que l'écran n'est pas dans son état initial on le réinitialise*/
                                    else if(stat!=0&&!(testposition(events,j1))&&!(testposition(events,j2))&&!(testposition(events,stopb))&&!(testposition(events,langb)))
                                        {
                                            SDL_RenderClear(renderer);
                                            SDL_RenderCopy(renderer, text0, NULL,NULL); 
                                            SDL_RenderPresent(renderer);
                                            stat=0;
                                        }
                                break;
                                case SDL_MOUSEBUTTONDOWN : 
                                /*Dans les cas où l'utilisateur clique sur un bouton, on retourne une valeur correspondant aux différents cas.
                                Si le bouton arrêt est cliqué la valeur est de 0, pour les modes 1 joueur et 2 joueurs, il s'agit de respectivement 1 et 2
                                enfin si l'utilisateur veut changer de langue on renvoie 3*/
                                    if(testposition(events,stopb))
                                        {
                                            retour=0;
                                            run=0;
                                        }
                                    else if(testposition(events,j1))
                                        {
                                            retour=1;
                                            run=0;
                                        }
                                    else if(testposition(events,j2))
                                        {
                                            retour=2;
                                            run=0;
                                        }
                                    else if(testposition(events,langb))
                                        {
                                            retour=3;
                                            run=0;
                                        }
                                    else if(testposition(events,soundb))
                                        {
                                            /*Dans le cas où le bouton est celui du son, on désactive la musique si elle est active sinon on la réactive*/
                                            if(*musicstate)
                                                {
                                                    Mix_ResumeMusic();
                                                    *musicstate=0;
                                                }
                                            else
                                                {
                                                    Mix_PauseMusic();
                                                    *musicstate=1;
                                                }
                                        }
                                break; 
                                case SDL_KEYDOWN : 
                                    /*La seule utilisation du clavier dans le menu est pour baisser le volume en utilisant les flèches du clavier,
                                    on modifie le contenu de la variable volume selon le bouton enclenché et on applique ces modifications après*/
                                    if (events.key.keysym.scancode==SDL_SCANCODE_UP && *volume < MIX_MAX_VOLUME)
                                        {
                                            (*volume)++;
                                            Mix_VolumeMusic(*volume);
                                        }  
                                    else if (events.key.keysym.scancode==SDL_SCANCODE_DOWN && *volume >0)
                                        {
                                            (*volume)--;
                                            Mix_VolumeMusic(*volume);
                                        }
                                break;
                            }
                    }        

            }
        return retour;
    }

//Fonction de sélection de la langue de jeu
/*On passe en paramètre le rendu, la texture pour choisir la langue et les différentes zones cliquables*/

int afflang(SDL_Renderer* renderer,SDL_Texture* textl,SDL_Rect rbri,SDL_Rect rger,SDL_Rect rita,SDL_Rect rspa) 
    {
        /*On initialise deux variables, une pour faire tourner la boucle et une autre pour retourner le choix de la langue*/ 
        int run=1,stat=0;

        /*On affiche l'écran pour choisir */
        SDL_RenderCopy(renderer, textl, NULL,NULL); 
        SDL_RenderPresent(renderer);

        SDL_Event events; 

        while(run)
            {
                while(SDL_PollEvent(&events))
                    {
                        switch(events.type)
                            {
                                case SDL_MOUSEBUTTONDOWN : 
                                /*Quand l'utilisateur clique sur un bouton, on change la variable d'état 
                                la variable permettant de faire tourner la boucle prend 0 pour la stopper*/
                                    if(testposition(events,rbri))
                                        {
                                            stat=1;
                                            run=0;
                                        }
                                    else if(testposition(events,rger))
                                        {
                                            stat=2;
                                            run=0;
                                        }
                                    else if(testposition(events,rita))
                                        {
                                            stat=3;
                                            run=0;
                                        }
                                    else if(testposition(events,rspa))
                                        {
                                            stat=4;
                                            run=0;
                                        }
                                break; 
                                  
                                
                            }
                    }        

            }
        return stat;
    }

//Fonction choix d'un mot
/*On passe en paramètre le rendu, la texture pour choisir la langue,les différentes zones cliquables et notre structure de donnée
on renvoie le noeud correspondant au mot choisi*/

AVL* choose(SDL_Renderer* renderer,SDL_Texture* textchoix1,SDL_Texture* textchoix2,SDL_Rect rtexte,AVL * arbre) 
    {
        /*On initialise deux variables entières, une pour faire tourner la boucle et une pour activer la saisie*/ 
        int run=1,saisie=1;

        /*On déclare un pointeur vers un noeud de l'arbre qui sera retourné en cas de succès de la recherche*/
        AVL*search;

        /*On initialise trois chaines une pour récupérer le texte entré, elle sera initialisé avec un espace,
        une visant à être affichée, elle sera formatée de telle sorte et une visant à être comparée, elle sera formatée aussi*/
        char texte[STRTAILLE];
        char affiche[STRTAILLE];
        char renvoie[STRTAILLE];
        strcpy(texte," ");

        Sint32 cursor;
        Sint32 selection_len;

        /*Création de la police*/
        TTF_Font * font=NULL;
        font=TTF_OpenFont("fond/Timeless.ttf",25);
        if(font==NULL)
            {
                printf("Erreur lors du chargement de la police\n");
            }

        SDL_Color white={255,255,255};

        /*Création des textures et des surfaces pour afficher le texte*/
        SDL_Surface * zonetxt;
        SDL_Texture * txttexte;

        txttexte=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,rtexte.w,rtexte.h);

        /*Affichage de la texture principale*/
        SDL_RenderCopy(renderer, textchoix1, NULL,NULL); 
        SDL_RenderPresent(renderer);

        SDL_Event events; 
        SDL_StartTextInput();

        while(run)
            {
                while(SDL_PollEvent(&events))
                    {
                        switch(events.type)
                            {
                                case SDL_KEYDOWN :
                                    if(events.key.keysym.scancode==SDL_SCANCODE_RETURN && saisie)
                                        {
                                        /*Quand le bouton entrée est pressé et que le jeux est en mode saisie alors on formate la chaine "affiche"
                                        afin qu'elle corresponde à l'affichage, on passe donc 1 comme paramètre à la fonction ajust*/
                                            ajust(texte,affiche,1);
                                            net(affiche);
                                            zonetxt=TTF_RenderText_Solid(font,affiche,white);
                                        /*Après avoir chargé la surface dans la texture on l'affiche sur l'écran, ainsi on affiche le texte entré par l'utilisateur
                                        dans la zone de texte et on passe hors du mode saisie, maintenant le joueur doit valider ou supprimer son entrée*/
                                            if(zonetxt!=NULL)
                                                {
                                                    SDL_SetRenderTarget(renderer,textchoix1);
                                                    txttexte=SDL_CreateTextureFromSurface(renderer,zonetxt);
                                                    SDL_RenderCopy(renderer, txttexte, NULL,&rtexte); 
                                                    SDL_SetRenderTarget(renderer,NULL);
                                                    SDL_RenderCopy(renderer, textchoix1, NULL,NULL); 
                                                    SDL_RenderPresent(renderer);
                                                    saisie=0;
                                                }
                                            else
                                                {
                                                    printf("Erreur lors de l'affichage du texte\n");
                                                }
                                            
                                        } 
                                    else if(events.key.keysym.scancode==SDL_SCANCODE_RETURN && !(saisie))
                                        {
                                        /*Quand le bouton entrée est pressé et que le jeux n'est pas en mode saisie alors on formate la chaine "renvoie"
                                        afin qu'elle corresponde à celle se trouvant dans l'AVL, on passe donc 0 comme paramètre à la fonction ajust*/
                                            ajust(texte,renvoie,0);

                                        /*On effectue ensuite la recherche de l'élément dans l'AVL*/
                                            search=recherche(arbre,renvoie);

                                        /*Si l'élément est trouvé, on stoppe la boucle, "run" passe donc à 0 et on réinitialise l'affichage 
                                        afin d'éviter d'avoir le texte toujours afficher pour la prochaine entrée*/
                                            if(search!=NULL)
                                                {
                                                    run=0;
                                                    modif(renderer,textchoix1,"fond/fondtxt.png",rtexte);
                                                }
                                        /*Sinon on affiche le message d'erreur et on réinitialise l'affichage et le texte et on réactive le mode saisie*/
                                            else
                                                {
                                                    SDL_RenderCopy(renderer, textchoix2, NULL,NULL); 
                                                    SDL_RenderPresent(renderer); 
                                                    SDL_Delay(TEMPS);
                                                    modif(renderer,textchoix1,"fond/fondtxt.png",rtexte);
                                                    strcpy(texte," ");
                                                    saisie=1; 
                                                }
                                        }
                                    /*Si le bouton correspond au retour arrière, on réinitialise l'affiche, la chaine tampon et on réactive la saisie*/
                                    else if(events.key.keysym.scancode==SDL_SCANCODE_BACKSPACE && !(saisie))
                                        {
                                            strcpy(texte," ");
                                            modif(renderer,textchoix1,"fond/fondtxt.png",rtexte);
                                            saisie=1;
                                        }   
                                break;
                                case SDL_TEXTINPUT :
                                /*Si le mode de saisie est activé alors on concatène les différentes entrées avec la chaine tampon*/
                                    if(saisie)
                                        {
                                            strcat(texte, events.text.text);
                                        }       
                                break;                                                                
                            }
                    }        
            }
        /*On libère la surface et la textures tampon utilisées*/
        SDL_FreeSurface(zonetxt);
        SDL_DestroyTexture(txttexte);   
        SDL_StopTextInput(); 
        TTF_CloseFont(font);
        return search;
    }
//Fonction d'affichage du mode de jeux
//On passe en paramètre le rendu, la texture, les zones cliquables correspondant à des rectangles, le noeud contenant les éléments à deviner ainsi que les paramètres de la musique et les paramètres du score

int affmain(SDL_Renderer* renderer,SDL_Texture* textmain,SDL_Rect rtexte,SDL_Rect rconseil,SDL_Rect rscore,SDL_Rect stopb,SDL_Rect soundb,SDL_Rect ratt1,SDL_Rect ratt2,SDL_Rect ratt3,SDL_Rect ratt4,AVL * arbre,int * musicstate,int * volume,int player,int score[2]) 
    {
        /*On initialise 5 variables, la première servant à faire tourner le jeu, la deuxième sera le retour de la fonction dans le programme principal
        il nous permettra de savoir si on doit relancer ou pas le programme, la troisième variable permettra de savoir si on est en mode saisie ou pas
        la quatrième permet de savoir si le bouton stop est en affichage alternatif ou pas et enfin la dernière variable est un compteur*/

        int run=1,stat=1,saisie=1,stopmotion=0,attempt=4;

        /*On initialise trois chaines une pour récupérer le texte entré, elle sera initialisé avec un espace,
        une visant à être affichée, elle sera formatée de telle sorte et une visant à être comparée, elle sera formatée aussi*/
        char affiche[STRTAILLE];
        char texte[STRTAILLE];
        char renvoie[STRTAILLE];
        strcpy(texte," ");

        Sint32 cursor;
        Sint32 selection_len;

        /*Création de la police*/
        TTF_Font * font=NULL;
        font=TTF_OpenFont("fond/Timeless.ttf",25);
        if(font==NULL)
            {
                printf("Erreur lors du chargement de la police\n");
            }

        SDL_Color white={255,255,255};

        /*Création des textures locales variants trop pour être chargées au début*/
        SDL_Texture * txttexte;
        SDL_Texture * txtscore;
        txttexte=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,rtexte.w,rtexte.h);
        txtscore=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,rscore.w,rscore.h);
        
        /*Affichage de la texture principale ainsi que des fenêtres de conseiller, de score et de tentatives*/
        SDL_RenderCopy(renderer, textmain, NULL,NULL); 
        SDL_RenderPresent(renderer);

        modif(renderer,textmain,"fond/conseilb.png",rconseil);

        affscore(renderer,textmain,rscore,player,score);
        updattempt(renderer,textmain,ratt1,ratt2,ratt3,ratt4,attempt);

        SDL_Event events; 
        SDL_StartTextInput();

        /*Lancement du jeux tant que l'on n'a pas cliqué sur le bouton exit ou atteint le nombre maximum de tentatives*/
        while(run && attempt)
            {
                while(SDL_PollEvent(&events))
                    {
                        switch(events.type)
                            {
                                /*Dans le cas où la souris passe sur le bouton exit et selon l'état du bouton on change l'affichage de celui-ci*/
                                case SDL_MOUSEMOTION : 
                                    if(!stopmotion && testposition(events,stopb))
                                        {
                                            modif(renderer,textmain,"fond/stopo.png",stopb);
                                            stopmotion=1;
                                        }
                                    else if(stopmotion && !testposition(events,stopb))
                                        {
                                            modif(renderer,textmain,"fond/stop.png",stopb);
                                            stopmotion=0;
                                        }
                                break;
                                case SDL_MOUSEBUTTONDOWN :
                                /*Quand l'utilisateur clique sur le bouton stop, on change la variable d'état 
                                la variable permettant de faire tourner la boucle prend 0 pour la stopper et
                                la variable de retour passe à 0 pour ne pas relancer le jeux*/ 
                                    if(testposition(events,stopb))
                                        {
                                            run=0;
                                            stat=0;
                                        }
                                /*Quand on appuie sur le bouton de son, on met en pause la musique si elle est joué
                                sinon on la relance si elle est en pause */
                                    else if(testposition(events,soundb))
                                        {
                                            if(*musicstate)
                                                {
                                                    Mix_ResumeMusic();
                                                    *musicstate=0;
                                                }
                                            else
                                                {
                                                    Mix_PauseMusic();
                                                    *musicstate=1;
                                                }
                                        }
                                break;
                                case SDL_KEYDOWN :
                                
                                    if(events.key.keysym.scancode==SDL_SCANCODE_RETURN && saisie)
                                        {
                                            /*Quand le bouton entrée est pressé et que le jeux est en mode saisie alors on formate la chaine "affiche"
                                        afin qu'elle corresponde à l'affichage, on passe donc 1 comme paramètre à la fonction ajust*/
                                            ajust(texte,affiche,1);
                                            net(affiche);
                                            /*Après avoir chargé la surface dans la texture on l'affiche sur l'écran, ainsi on affiche le texte entré par l'utilisateur
                                        dans la zone de texte et on passe hors du mode saisie, maintenant le joueur doit valider ou supprimer son entrée*/
                                            SDL_Surface * zonetxt=TTF_RenderText_Solid(font,affiche,white);
                                            if(zonetxt!=NULL)
                                                {
                                                    SDL_SetRenderTarget(renderer,textmain);
                                                    txttexte=SDL_CreateTextureFromSurface(renderer,zonetxt);
                                                    SDL_RenderCopy(renderer, txttexte, NULL,&rtexte); 
                                                    SDL_SetRenderTarget(renderer,NULL);
                                                    SDL_RenderCopy(renderer, textmain, NULL,NULL); 
                                                    SDL_RenderPresent(renderer);
                                                    saisie=0;
                                                    SDL_FreeSurface(zonetxt); 
                                                }
                                            else
                                                {
                                                    printf("Erreur lors de l'affichage du texte\n");
                                                }
                                            /*A activer en mode test : printf("Réponse: %s\n",arbre->mot);*/
                                        } 
                                    else if(events.key.keysym.scancode==SDL_SCANCODE_BACKSPACE && !(saisie))
                                        {
                                            /*Si le bouton correspond au retour arrière, on réinitialise l'affiche, la chaine tampon et on réactive la saisie*/
                                            strcpy(texte," ");
                                            modif(renderer,textmain,"fond/fondtxt.png",rtexte);
                                            saisie=1;
                                        }
                                    else if(events.key.keysym.scancode==SDL_SCANCODE_RETURN && !(saisie))
                                        {
                                             /*Quand le bouton entrée est pressé et que le jeux n'est pas en mode saisie alors on formate la chaine "renvoie"
                                        afin qu'elle corresponde à celle que que l'utilisateur doit deviner, on passe donc 0 comme paramètre à la fonction ajust*/
                                            ajust(texte,renvoie,0);
                                            /*Si les chaines sont identiques, on change l'image du conseiller pour indiquer au joueur qu'il a gagné, 
                                            on ajoute des points et on passe "run" à 0 pour sortir de la boucle*/
                                            if(strcmp(renvoie,arbre->mot)==0)
                                                {
                                                    modif(renderer,textmain,"fond/conseilv.png",rconseil);
                                                    SDL_Delay(TEMPS/2);
                                                    run=0;
                                                    score[player]=score[player]+attempt;
                                                }
                                            /*Sinon on affiche le message d'erreur et on réinitialise l'affichage et le texte et on réactive le mode saisie*/
                                            else   
                                                {
                                                    modif(renderer,textmain,"fond/conseild.png",rconseil);
                                                    SDL_Delay(TEMPS);
                                                    strcpy(texte," ");
                                                    saisie=1;
                                                    attempt--;
                                                    updattempt(renderer,textmain,ratt1,ratt2,ratt3,ratt4,attempt);
                                                    modif(renderer,textmain,"fond/fondtxt.png",rtexte);
                                                    modif(renderer,textmain,"fond/conseilb.png",rconseil);
                                                    
                                                }
                                        } 
                                    /*Dans le cas où le bouton est celui du son, on désactive la musique si elle est active sinon on la réactive*/
                                    else if (events.key.keysym.scancode==SDL_SCANCODE_UP && *volume < MIX_MAX_VOLUME)
                                        {
                                            (*volume)++;
                                            Mix_VolumeMusic(*volume);
                                        }  
                                    else if (events.key.keysym.scancode==SDL_SCANCODE_DOWN && *volume > 0)
                                        {
                                            (*volume)--;
                                            Mix_VolumeMusic(*volume);
                                        }
                                break;
                                case SDL_TEXTINPUT :
                                    if(saisie)
                                        {
                                            strcat(texte, events.text.text);
                                        }
                                    
                                break;                                                                
                            }
                    }        
            }
        
        SDL_DestroyTexture(txttexte);     
        SDL_DestroyTexture(txtscore); 
        SDL_StopTextInput();  
        TTF_CloseFont(font);
        return stat;
    }

/*##########################################################################################################################################################
                                                            CODE PRINCIPAL
##########################################################################################################################################################*/

int main(int argc, char *argv[])
    {
        /*On déclare 9 variables permettant de gérer les paramètres du jeu, la première et la deuxième correspondent à la taille de l'écran
        la variable "nbmots" va contenir le nombre de mots ce qui correspond au nombre de noeud, "menustate" sera le retour du menu, "lang" correspond à la langue choisie
        "game" permettra de joueur en continue tant que le joueur le veux, "player" permet de savoir quel joueur joue, "musicstate" et "volume" permettent de gérer l'audio*/
        int winw, winh,nbmots,menustate,lang,game,player,musicstate,volume;
        /*On initialise les scores à 0, l'indice 0 sera pour le joueur 1 et 1 pour le joueur 2*/
        int score[2];
        score[0]=score[1]=0;
        /*On affecte aussi à "nbmots" le nombre de lignes*/
        nbmots=nblines();

        /*On créé notre AVL de n noeuds où n est le nombre de mots à charger, on l'appel "root" car il s'agit du pointeur vers la zone mémoire, 
        on déclare aussi deux variables, la racine de l'arbre "tree" qui peut être modifiée à cause des rotations 
        et une variable "search" correspondant au mot à trouver*/
        AVL* root=(AVL*)malloc(nbmots*sizeof(AVL));
		AVL* search,*tree;
        /*On déclare également le tableau des mots français pour le tirage au sort*/
		char tabf[nbmots][STRTAILLE];

        /*"menustate" et "lang" prennent des valeurs indiquants qu'ils viennent d'être initialisé cela nous permettra de les comparer ultérieurement*/
        menustate=-1;
        lang=-1;

        /*On déclare toute les textures fixes, celle qui ne nécessite pas de gros changement*/
        SDL_Window* window=NULL;
        SDL_Renderer* renderer=NULL;
        SDL_Texture *textaccueil=NULL;
        SDL_Texture *textmenu0=NULL;
        SDL_Texture *textmenu1=NULL;
        SDL_Texture *textmenu2=NULL;
        SDL_Texture *textmenu3=NULL;
        SDL_Texture *textmenu4=NULL;
        SDL_Texture *textlang=NULL;
        SDL_Texture *textmain=NULL;
        SDL_Texture *choosej2_0=NULL;
        SDL_Texture *choosej2_1=NULL;

        if(SDL_Init(SDL_INIT_VIDEO)!=0)
            {
                printf("Erreur lors de l'initialisation\n");
                return EXIT_FAILURE;
            }

        if(TTF_Init()!=0)
            {
                printf("Erreur lors de l'initialisation de la TTF\n");
                SDL_DestroyWindow(window);
                SDL_Quit();
                return EXIT_FAILURE;
            }

        window=SDL_CreateWindow("Translate",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,0,0,SDL_WINDOW_FULLSCREEN_DESKTOP);
        if(window==NULL)
            {
                printf("Erreur lors de la création de fenêtre\n");
                SDL_Quit();
                return EXIT_FAILURE;
            }
        SDL_GetWindowSize(window,&winw,&winh);
        
        /*Après avoir récupérer la taille de l'écran, on initialise les différents rectangles en fonction de notre écran*/
        SDL_Rect j1={winw*0.0,winh*0.9,winw*0.5,winh*0.1};
		SDL_Rect j2={winw*0.5,winh*0.9,winw*0.5,winh*0.1};
        SDL_Rect stopb={winw*0.9,winh*0.025,winw*0.1,winh*0.1};
		SDL_Rect soundb={winw*0.85,winh*0.05,winw*0.05,winh*0.05};
        SDL_Rect langb={winw*0.79,winh*0.05,winw*0.055,winh*0.055};
        SDL_Rect rtexte={winw*0.0,winh*0.9,winw*1,winh*0.1};
        SDL_Rect rbri={winw*0.20,winh*0.20,winw*0.20,winh*0.20};
        SDL_Rect rger={winw*0.60,winh*0.20,winw*0.20,winh*0.20};
        SDL_Rect rita={winw*0.20,winh*0.60,winw*0.20,winh*0.20};
        SDL_Rect rspa={winw*0.60,winh*0.60,winw*0.20,winh*0.20};
        SDL_Rect image={winw*0.20,winh*0.20,winw*0.60,winh*0.60};
        SDL_Rect rframe={winw*0.19,winh*0.19,winw*0.62,winh*0.62};
        SDL_Rect rconseil={winw*0.05,winh*0.537,winw*0.4,winh*0.4};
        SDL_Rect rconseilm={winw*0.01,winh*0.5,winw*0.4,winh*0.4};
        SDL_Rect rscore={winw*0.0,winh*0.0,winw*0.5,winh*0.2};
        SDL_Rect ratt1={winw*0.85,winh*0.7,winw*0.1,winh*0.1};
        SDL_Rect ratt2={winw*0.90,winh*0.6,winw*0.1,winh*0.1};
        SDL_Rect ratt3={winw*0.85,winh*0.5,winw*0.1,winh*0.1};
        SDL_Rect ratt4={winw*0.90,winh*0.4,winw*0.1,winh*0.1};

        renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if(renderer==NULL)
            {
                printf("Erreur lors de la création du rendu\n");
                SDL_DestroyWindow(window);
                SDL_Quit();
                return EXIT_FAILURE;
            }

        /*On affiche un écran d'accueil le temps de charger toutes les textures*/
        textaccueil=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,winw,winh);
        textaccueil= IMG_LoadTexture(renderer,"fond/accueil.jpg");
        if(textaccueil==NULL)
            {
                printf("Erreur lors de la création de la texture d'accueil\n");
                return 0;
            } 
        SDL_RenderCopy(renderer, textaccueil, NULL, NULL); 
        SDL_RenderPresent(renderer);
        SDL_Delay(TEMPS/2);

        /*Chargement de l'ensemble des textures qui varient peu ou pas après leur création*/
        textmenu0=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,winw,winh);
        textmenu0=inittextmenu(renderer,textmenu0,"fond/j1.png","fond/j2.png","fond/stop.png","fond/langb.png",j1,j2,stopb,soundb,langb);
        textmenu1=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,winw,winh);
        textmenu1=inittextmenu(renderer,textmenu1,"fond/j1o.png","fond/j2.png","fond/stop.png","fond/langb.png",j1,j2,stopb,soundb,langb);
        textmenu2=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,winw,winh);
        textmenu2=inittextmenu(renderer,textmenu2,"fond/j1.png","fond/j2o.png","fond/stop.png","fond/langb.png",j1,j2,stopb,soundb,langb);
        textmenu3=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,winw,winh);    
        textmenu3=inittextmenu(renderer,textmenu3,"fond/j1.png","fond/j2.png","fond/stopo.png","fond/langb.png",j1,j2,stopb,soundb,langb);
        textmenu4=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,winw,winh);    
        textmenu4=inittextmenu(renderer,textmenu4,"fond/j1.png","fond/j2.png","fond/stop.png","fond/langbo.png",j1,j2,stopb,soundb,langb);
        textlang=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,winw,winh);
        textlang=initttextlang(renderer,textlang,rbri,rger,rita,rspa,rtexte);
        choosej2_0=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,winw,winh);
        choosej2_0=inittextj2(renderer,choosej2_0,"fond/conseilj2.png",rtexte,rconseil);
        choosej2_1=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,winw,winh);
        choosej2_1=inittextj2(renderer,choosej2_1,"fond/conseilj2o.png",rtexte,rconseil);
        textmain=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,winw,winh);

        /*Création de l'audio*/
        if(Mix_OpenAudio(FREQUENCE,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)<0)
            {
                printf("Erreur lors de l'initialisation du son\n");
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return EXIT_FAILURE;
            }
        Mix_Music* music=Mix_LoadMUS("musique/main.mp3");
        Mix_PlayMusic(music,-1);
        musicstate=1;
        volume=MIX_MAX_VOLUME;
        
        /*Destruction de la texture d'accueil qui devient inutile*/
        SDL_DestroyTexture(textaccueil);

        while(menustate)
            {
                /*On récupère l'état du menu et on estime que le joueur qui vient de sélectionner les informations est le premier joueur*/
                menustate=menu(renderer,textmenu0,textmenu1,textmenu2,textmenu3,textmenu4,j1,j2,stopb,soundb,langb,&musicstate,&volume);
                player=0;

                /*Si le joueur a cliqué sur le bouton j1 ou j2 alors on lance le jeu*/
                if(menustate==1||menustate==2)
                    {
                        game=1;
                        if(lang==-1)
                            {
                                /*Si le joueur n'a pas choisi de langue on rempli l'AVL*/
                                lang=afflang(renderer,textlang,rbri,rger,rita,rspa);
                                printf("LANGUE :%d\n",lang);
                                remptab(tabf);
                                tree=rempAVL(root,lang);
                            }
                        while(game)
                            {
                                if(menustate==1)
                                    {
                                        /*Dans le mode à un joueur, on tire au sort une valeur qui sera un indice du tableau de mot français,
                                        on récupère donc le contenu du tableau, le mot français et on le recherche dans l'arbre
                                        pour récupérer le noeud puis on initialise la texture de jeu selon l'image du noeud*/
                                        int x=tirage(nbmots);
                                        search=recherche(tree,tabf[x]);
                                        textmain=inittextmain(renderer,textmain,search->image,image,rframe,rtexte,stopb,soundb);
                                        game=affmain(renderer,textmain,rtexte,rconseilm,rscore,stopb,soundb,ratt1,ratt2,ratt3,ratt4,search,&musicstate,&volume,player,score);
                                    }
                                else if(menustate==2)
                                    {
                                        /*Dans le mode à deux joueurs, on demande un mot au joueur, on compare son entrée au contenu de l'AVL
                                        jusqu'a ce qu'il entre un mot correct, on récupére le noeud puis on initialise la texture de jeu selon l'image du noeud
                                        enfin on interverti les rôles*/
                                        search=choose(renderer,choosej2_0,choosej2_1,rtexte,tree);
                                        textmain=inittextmain(renderer,textmain,search->image,image,rframe,rtexte,stopb,soundb);
                                        game=affmain(renderer,textmain,rtexte,rconseilm,rscore,stopb,soundb,ratt1,ratt2,ratt3,ratt4,search,&musicstate,&volume,player,score);
                                        player=changplay(player);
                                    }  
                            }
                    }
                /*Si le joueur a cliqué sur le bouton de changement de langue*/
                else if(menustate==3)
                    {
                        if(lang==-1)
                            {
                                /*Si le joueur n'a pas choisi de langue mais clique sur le bouton changement de langue, on rempli l'AVL*/
                                lang=afflang(renderer,textlang,rbri,rger,rita,rspa);
                                printf("LANGUE :%d\n",lang);
                                remptab(tabf);
                                tree=rempAVL(root,lang);
                            }
                        else
                            {
                                /*Sinon on remplace les mots de l'AVL par leur équivalent dans une autre langue*/
                                lang=afflang(renderer,textlang,rbri,rger,rita,rspa);
                                printf("%d\n",lang);
                                changelang(tree,lang);
                            }
                    }
                
            }
        
        /*Destruction de toutes les textures et libération de l'espace mémoire alloué*/
        SDL_DestroyTexture(textmenu0);
        SDL_DestroyTexture(textmenu1);
        SDL_DestroyTexture(textmenu2);
        SDL_DestroyTexture(textmenu3);
        SDL_DestroyTexture(textmenu4);
        SDL_DestroyTexture(textlang);
        SDL_DestroyTexture(textmain);
        SDL_DestroyTexture(choosej2_0);
        SDL_DestroyTexture(choosej2_1);
        SDL_DestroyRenderer(renderer);
        TTF_Quit();
        SDL_DestroyWindow(window);
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        free(root);
        return EXIT_SUCCESS;
    }


    