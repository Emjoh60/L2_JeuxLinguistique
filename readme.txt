MANUEL D'UTILISATION

I.DESCRIPTION DU PROJET
	Le projet "Translate" vise à créer un jeux permettant au joueur de tester son niveau de langue en anglais, allemand, espagnol ou italien. Le but du jeux est de trouver la traduction d'un mot à partir d'une image qui s'affiche dans le jeux. Il y a deux modes de jeux, le premier est un mode à un joueur dans lequel une image aléatoire est affichée et le joueur doit trouver la traduction de ce qui se trouve sur l'image, la deuxième version est une version à deux joueurs dans laquelle un joueur doit entrer un mot en français que l'autre joueur devra deviner grâce à l'image s'affichant sur l'écran. Le mot devra se trouver dans la base de donnée, c'est pourquoi certains mots ne seront pas disponibles.

II.PREREQUIS
	Afin de pouvoir tester ce programme, il est nécessaire de disposer d'un compilateur et d'avoir d'installer les librairies SDL2, SDL2_images, SDL2_ttf et SDL2_Mixer.

III.INSTALLATION
	Afin d'installer ce programme, il est nécessaire de s'assurer que tous les éléments suivants sont dans un même dossier, il s'agit des fichiers jeux.c, struc.c et struc.h, le makefile, le fichier jeux.csv ainsi que les dossier fond, musique et images. Le dossier images étant d'un volume important, il est nécessaire de le télécharger séparément du reste du programme et de l'insérer ensuite dans le même dossier que le makefile. Le liens permettant de télécharger le dossier images est le suivant : https://www.dropbox.com/s/xn6keiildo7aj56/images.zip?dl=0 Il ne reste plus qu'à exécuter la commande make sur le terminal après s'être assuré que toutes ces conditions sont remplies et que l'on se situe dans le même dossier que le makefile.
   
IV.LANCEMENT
	Pour lancer le jeux, il suffit d'exécuter la commande ./jeux dans le terminal, lorsque l'on se situe dans le dossier d'installations.
	
V.GUIDE D'UTILISATION
	Lorsque le joueur lance le jeu, il arrivera sur un menu, il aura le choix d'effectuer plusieurs actions. Il lui sera possible de choisir dans quel mode de jeu il souhaite jouer, auquel cas il	devra cliquer avec la souris sur le bouton correspondant puis le jeu lui demandera de choisir une langue avant de pouvoir jouer. Il pourra également cliquer sur trois autres bouton en haut à gauche de l'écran servant respectivement de gauche à droite à : changer la langue du jeu, couper le son ou le réactiver si il a déjà été coupé et enfin quitter le jeu. A propos du son, il est possible pour le joueur de modifier le son du jeu dans le menu ou en pleine partie en appuyant sur les touches UP et DOWN du pavé numérique.
	
	Après avoir sélectionné un mode de jeux, le joueur arrivera dans l'espace de jeu, cet espace diffère légèrement d'un mode à l'autre ainsi nous les présenterons séparément.
	
	V.1 MODE UN JOUEUR
		Dans le cas du mode à un joueur, le joueur arrivera sur un écran où s'affichera une image, sur cet écran s'affichera le score total du joueur au cours de toute les parties ainsi que le nombre de tentatives qu'il lui reste, le nombre de luciole sera l'indicateur du nombre de tentatives. Il pourra quitter cet écran à tout moment en cliquant sur le bouton quitter en haut à gauche de l'écran ce qui le ramènera sur le menu. Enfin, il lui sera possible d'écrire du texte, la saisie de texte suit un procédé qui peut paraitre non intuitif c'est pour cela que nous allons l'expliquer en détail. TOut d'abord, le joueur saisi un mot, rien ne s'affiche, pour afficher le mot il doit presser la touche ENTREE, le mot s'affichera. A ce moment là le joueur peut soit supprimer le mot qu'il a entré en pressant la touche RETOUR ARRIERE, soit valider ce mot en pressant la touche ENTREE. Si le mot correspond bien à ce qui se trouve sur l'écran, une nouvelle image apparaitra sinon il perdra une tentative et devra réessayer jusqu'à ce qu'il trouve ou qu'il ait atteint le nombre maximum de tentatives.
	
	V.2 MODE A DEUX JOUEURS
		Dans le cas du mode à deux joueurs, le joueur arrivera d'abord sur un écran lui demandant d'entrer un mot, le principe de saisit de texte est le même que celui expliqué précédement, le joueur doit donc saisir un mot jusqu'à ce que ce mot corresponde à un mot se trouvant dans la banque de données sinon le programme attendra qu'il saisisse quelque chose dans le cas où le joueur se ravise et ne souhaite pas jouer, il lui faudra entrer un mot afin d'accéder à l'interface de jeu et pouvoir quitter. Un mot pouvant être entré afin de quitter le mode saisie de texte peut être "lion". Après que le joueur ait choisi un mot, le programme se comportera comme pour le mode à un joueur.
