### Définitions pour comprendre l'incompréhensible

* Trois projets :
	* virtual machine (VM)
	* assembleur (asm)
	* champions (chmp)

* `But` : creer une machine virtuelle dans laquelle des champions s'affronterons.
		* la partie est finie quand plus aucun processus n'est en vie
		* le gagnant de la partie est dernier joueur ayant declare etre en vie.

* La `VM`:
	* la machine virtuelle prendra les champions-asm en leur atribuant un numero
	* puis executera les instructions de ceux-ci dans les procesus jusqu'a la fin de la partie
	* Les processus s'executent sequentiellement et dans le meme espace memoire
	* ils peuvent donc s'ecrire les uns sur les autres se corrompre, etc...
	* la machine virtuelle lit les octets en BIG_ENDIAN(de gauche a droite)
	* chaque instruction s'execute uniquement a la fin de son cycle(et attends toute sa duree)
	* et dans l'ordre decroissant des numeros de processus

* VM : `composition des processus`:
	* `PC` Définition de PC :
		Registre special qui contient l'adresse (dans la memoire de la VM) de la
		prochaine instruction a decoder et executer.

	* `carry` Définition de carry:
		Un flag qui vaut 1 si l'opperation a reussie.

	* `registre` Définition de registre
		un register est une petite case memoire contenant une seule valeur
		Chaque processus a a sa disposition des registeurs propres
		ces registeurs sont au nombre de REG_NUMBER registers
		chaque registeur fait REG_SIZE octets.

* VM autre :
	* `Le numero du joueur`
		* Il est generer par la machine ou specifie au lancement et est
		* fourni aux joueurs via le registeur r1 de leur premier processus

	* Les `champions dans a VM`
		* Les champions sont charges en memoire de facon a espacer equitablement leur point d'entree

	* Les CYCLES : `verification`
		* Une verification correspond a CYCLE_TO_DIE cycles
		* A chaque verification la machine verifie que chaque processus a executer au moins un live depuis la derniere verification
		* S'il ne l'as pas fait il est juge comme mort(remis a 0?)

	* Les CYCLES : `decrementation` des CYCLE_TO_DIE
		* si durant la verification on se rends compte qu'il y a eu NBR_LIVE live
		* ou si on attent MAX_CHECKS vérifications,
		* un decremente CyCLE_TO_DIE de CYCLE_DELTA. (-50 suvant les param de base)
	* `Fin de la partie`
		* Quand il n'y a plus de processus en vie la partie est finie et le gagnant est le dernier joueur rapporte en vie(live)
	* `Affichage fin de partie`
		* afficher : "le joueur x(nom_champion) a gagne", où x est le numéro du joueur et nom_champion le nom de son champion. (Exemple : "le joueur 2(rainbowdash) a gagne")
	* Les executions
		* A chaque exécution valide de l’instruction live, la machine doit afficher :
		* "un processus dit que le joueur x(nom_champion) est en vie"
	* Taille de la VM
		* la memoire est circulaire et fait MEM_SIZE octets.

* macros non définies
	* MAX_ARGS_NUMBER		4
	* REG_CODE				1
	* DIR_CODE				2
	* IND_CODE				3
	* IND_SIZE				2
	* typedef char			t_arg_type;
	* T_REG					1
	* T_DIR					2
	* T_IND					4
	* T_LAB					8

* Les champions :
	* les champions seront recompile depuis un psedo-assembleur en  'bytecde',par notre asm
	* les champions ne pevent pas avoir plus de CHAMP_MAX_SIZE octets
