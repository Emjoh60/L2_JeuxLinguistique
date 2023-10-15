#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "struc.h"

// Fonction permettant de compter le nombre de mot dans le fichier

int nblines(void)
	{
		int cpt=0;
		char tamp[6*STRTAILLE];
		FILE* fichier=NULL;
		fichier=fopen("jeux.csv","r");
		if(fichier==NULL)
			{
				printf("Impossible d'ouvrir le fichier \n");
				cpt=-1;
			}
		else
			{
				while(fgets(tamp,6*STRTAILLE,fichier))
					{
						cpt++;
					}
			}
		printf("NB LIGNES : %d\n",cpt);
		return cpt;
	}

//Fonctions d'initialisation de l'AVL

void init(AVL* arbre,char franc[STRTAILLE],char mot[STRTAILLE],char img[STRTAILLE])
	{
		strcpy(arbre->motfr,franc);
		strcpy(arbre->mot,mot);
		strcpy(arbre->image,img);
		arbre->g=NULL;
		arbre->d=NULL;
	}	

//Fonctions d'insertion de l'AVL	
	
AVL* inserer(AVL* arbre,AVL* pos,char franc[STRTAILLE],char mot[STRTAILLE],char img[STRTAILLE])
	{
		if(arbre==NULL)
			{
				/*Si on se trouve sur une feuille le pointeur est null et on peut insérer le nouvel élément*/
				init(pos,franc,mot,img);
				return pos;
			}
		else if(strcmp(arbre->motfr,franc)!=0)
			{
				/*Si le mot à insérer est différent de celui de l'abre courant*/
				if(strcmp(arbre->motfr,franc)>0)
					{
						/*Si il est avant le mot de l'arbre courant dans l'ordre lexicographique, on le range à gauche*/
						arbre->g=inserer(arbre->g,pos,franc,mot,img);
						return arbre;
					}
				else
					{
						/*Si il est après le mot de l'arbre courant dans l'ordre lexicographique, on le range à droite*/
						arbre->d=inserer(arbre->d,pos,franc,mot,img);
						return arbre;
					}
				/*Sinon il s'agit d'un mot déjà entré et on quitte le programme*/
			}
		else
			{
				return arbre;
			}
	}
	
//Fonctions d'affichage de l'AVL	

void afficher(AVL* ar,char c)
  {
    if(ar!=NULL)
    	{
			if (c=='c'){printf("Centre\n");}
        	printf("%s\n",ar->motfr);
        	if (c=='c'){printf("Gauche\n");}
			afficher(ar->g,'g');
        	if (c=='c'){printf("Droite\n");}
			afficher(ar->d,'d');
      	}   
  }

 //Fonctions de calcul de hauteur d'un arbre
  
int hauteur(AVL* arbre)
	{
		if(arbre==NULL)
			{
				return -1;
			}
		else
			{
				if(hauteur(arbre->g)>=hauteur(arbre->d))
					{
						return 1+hauteur(arbre->g);
					}
				else
					{
						return 1+hauteur(arbre->d);
					}
			}
	}
	
//Fonction de mesure du déséquilibre
	
int desequi(AVL* arbre)
	{
		if(arbre==NULL)
			{
				return 0;
			}
		else
			{
				if((hauteur(arbre->g)-hauteur(arbre->d)<=1)&&(hauteur(arbre->g)-hauteur(arbre->d)>=-1))
					{ 
						/*Si la différence des hauteurs est comprise entre 1 et -1, l'arbre est équilibré*/
						return 0;
					}
				else if(hauteur(arbre->g)-hauteur(arbre->d)<-1)
					{
						/*Si la différence des hauteurs est inférieur à -1, le sous arbre droit a une hauteur nettement supérieur au sous arbre gauche*/
						return -1;
					}
				else 
					{
						/*Si la différence des hauteurs est supérieur à 1, le sous arbre gauche a une hauteur nettement supérieur au sous arbre droit*/
						return 1;
					}
			}
	}

//Fonction de rangement d'un AVL

AVL* estAVL(AVL* arbre)	
	{
		if(arbre==NULL)
			{
				/*Si l'arbre est null alors il est inutile de le trier, on le renvoit*/
				return arbre;
			}
		else
			{				
				arbre->g=estAVL(arbre->g);
				arbre->d=estAVL(arbre->d);
				/*On parcourt et range les sous arbres gauches et droits avant de traiter le noeud courant*/
				if(desequi(arbre)==0)
					{
						/*Si il n'y a pas de déséquilibre alors il s'agit d'un AVL*/
						return arbre;
					}
				else if(desequi(arbre)==-1)
					{
						/*Si le déséquilibre est négatif on effectue une rotation gauche*/
						AVL* sd=arbre->d;
						if(hauteur(sd->g)-hauteur(sd->d)==1)
							{
								AVL* sdg=sd->g;
								sd->g=sdg->d;
								sdg->d=sd;
								arbre->d=sdg->g;
								sdg->g=arbre;
								arbre=sdg;
								return estAVL(arbre);
							}
						else
							{
								arbre->d=sd->g;
								sd->g=arbre;
								arbre= sd;
								return estAVL(arbre);
							}
						
					}
				else if(desequi(arbre)==1)
					{
						/*Si le déséquilibre est positif on effectue une rotation droite*/
						AVL* sg=arbre->g;
						if(hauteur(sg->g)-hauteur(sg->d)==-1)
							{
								AVL* sgd=sg->d;
								sg->d=sgd->g;
								sgd->g=sg;
								arbre->g=sgd->d;
								sgd->d=arbre;
								arbre=sgd;
								return estAVL(arbre);
								
							}
						else
							{
								arbre->g=sg->d;
								sg->d=arbre;
								arbre= sg;
								return estAVL(arbre);
							}
						
					}
			}
	}

//Fonction de recherche d'un mot dans un AVL

AVL* recherche(AVL* arbre,char franc[STRTAILLE])
	{
		if(arbre==NULL)
			{
				return NULL;
			}
		else if(strcmp(franc,arbre->motfr)==0)
			{
				return arbre;
			}
		else
			{
				if(strcmp(arbre->motfr,franc)>0)
					{
						return recherche(arbre->g,franc);
					}
				else
					{
						return recherche(arbre->d,franc);
					}
			}
	}

//Fonction de remplissage du tableau	
	
int remptab(char tab[][STRTAILLE])
	{
		FILE* fich=NULL;
		/*On déclare un tableau tamp récupérant la ligne traitée*/
		char tamp[6*STRTAILLE];
		char motf[STRTAILLE];
		/*On utilisera deux variables, i pour parcourir la chaine, idmot pour parcourir le tableau de chaine*/
		int i,idmot;
		
		fich=fopen("jeux.csv","r");
		if(fich!=NULL)
			{
				idmot=0;
				/*On effectue cette opération tant que l'on peut extraire des chaines*/
				while(fgets(tamp,6*STRTAILLE,fich))
					{
						i=0;
						/*On effectue copie dans "tab" le contenu de la chaine "tamp" tant que l'on n'a pas atteint le charactère ','*/
						while(tamp[i]!=',')
							{
								tab[idmot][i]=tamp[i];
								i++;
							}
						tab[idmot][i]='\0';
						idmot++;
					}
				fclose(fich);
				return 1;
			}
		return 0;
		
	}

//Fonction de séparation de la ligne récupérée en trois chaines	
	
void separtab(int lang, char tamp[6*STRTAILLE],char franc[STRTAILLE],char mot[STRTAILLE], char img[STRTAILLE])
	{
		int i,j,lastj, indxmot;
		i=0;
				//Récupération du mot en français
				j=0;
				while(tamp[i]!=',')
					{
						franc[j]=tamp[i];
						i++;
						j++;
					}
				franc[j]='\0';
				i++;
				
				//Récupération du mot dans la langue choisie
				j=0;
				indxmot=1;
				while(indxmot<5)
					{
						if(tamp[i]==',')
							{
								indxmot++;
								j=0;
							}
						else if(indxmot==lang)
							{
								mot[j]=tamp[i];
								j++;
								lastj=j;
							}
						i++;	
					}
				mot[lastj]='\0';
				
				
				//Récupération du liens vers l'image
				j=0;
				while(tamp[i]!='\0')
					{
						img[j]=tamp[i];
						i++;
						j++;
					}
				img[j-2]='\0';
	
	}
	
//Fonction de remplissage de l'AVL
	
AVL* rempAVL(AVL* arbre, int lang)
	{
		/*On initialise "tree" avec la racine de notre arbre*/
		AVL* tree=arbre;
		FILE* fich=NULL;
		char tamp[6*STRTAILLE];
		char franc[STRTAILLE];
		char mot[STRTAILLE];
		char img[STRTAILLE];
		int n=0;
		fich=fopen("jeux.csv","r");
		if(fich!=NULL)
			{
				while(fgets(tamp,6*STRTAILLE,fich))
					{
						
						separtab(lang,tamp,franc,mot,img);
						if(n==0)
							{
								/*Lorsque l'on a un arbre vide,on l'initialise*/
								init(tree,franc,mot,img);
							}
						else
							{
								/*Lorsque l'on souhaite insérer un élément dans un nouveau noeud, on passe la variable n 
								indiquant l'adresse où doit s'effectuer l'opération*/
								tree=inserer(tree,arbre+n,franc,mot,img);
								tree=estAVL(tree);
							}
						/*Puis on incrémente le compteur*/
						n++;
					}
				fclose(fich);
				/*On retourne la variable "tree" indiquant la racine de l'arbre suite aux rotations*/
				return tree;
			}
		return tree;			
	}

//Fonction de changement de langue

void changelang(AVL* arbre, int lang)
	{
		AVL * node;
		FILE* fich=NULL;
		char tamp[6*STRTAILLE];
		char franc[STRTAILLE];
		char mot[STRTAILLE];
		char img[STRTAILLE];
		fich=fopen("jeux.csv","r");
		if(fich!=NULL)
			{
				/*Pour chaque lignes, on récupère les informations 
				et on remplace le mot contenu dans chaque noeud par son équivalent dans une autre langue*/
				while(fgets(tamp,6*STRTAILLE,fich))
					{
						separtab(lang,tamp,franc,mot,img);
						node=recherche(arbre,franc);
						strcpy(node->mot,mot);
					}
				fclose(fich);
			}			
	}


	
	
