#define STRTAILLE 40

typedef struct AVL
	{
		char motfr[STRTAILLE];
		char mot[STRTAILLE];
		char image[STRTAILLE];
		struct AVL* g;
		struct AVL* d;
	} AVL;

//Fonctions d'initialisation de l'AVL

void init(AVL* arbre,char franc[STRTAILLE],char mot[STRTAILLE],char img[STRTAILLE]);

//Fonctions d'insertion de l'AVL	
	
AVL* inserer(AVL* arbre,AVL* pos,char franc[STRTAILLE],char mot[STRTAILLE],char img[STRTAILLE]);
	
//Fonctions d'affichage de l'AVL	

void afficher(AVL* ar,char c);

 //Fonctions de calcul de hauteur d'un arbre
  
int hauteur(AVL* arbre);

//Fonction de mesure du déséquilibre
	
int desequi(AVL* arbre);

//Fonction de rangement d'un AVL

AVL* estAVL(AVL* arbre);

//Fonction de recherche d'un mot dans un AVL

AVL* recherche(AVL* arbre,char franc[STRTAILLE]);

//Fonction de remplissage du tableau	
	
int remptab(char tab[][STRTAILLE]);

//Fonction de séparation de la ligne récupérée en trois chaines	
	
void separtab(int lang, char tamp[6*STRTAILLE],char franc[STRTAILLE],char mot[STRTAILLE], char img[STRTAILLE]);

	
//Fonction de remplissage de l'AVL
	
AVL* rempAVL(AVL* arbre, int lang);

//Fonction de mesure du nombre de ligne

int nblines(void);
	
//Fonction de changement de langue

void changelang(AVL* arbre, int lang);	
	
