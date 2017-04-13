### Définitions pour comprendre l'incompréhensible

* Deux projets :
	* virtual machine (VM)
	* assembleur (asm)

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
		ces registeurs sont au nombre de REG_NUMBER (16) registers
		chaque registeur fait REG_SIZE (4) octets.

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
	* Taille de la VM
		* la memoire est circulaire et fait MEM_SIZE octets.

* Les champions :
	* les champions seront recompile depuis un psedo-assembleur en  'bytecde',par notre asm
	* les champions ne pevent pas avoir plus de CHAMP_MAX_SIZE octets

* Encodage :
	* Chaque instruction est encodée par :
	* Code de l'instruction (live == 0x01, ld == 0x02 ...)
	* L’octet de codage des paramètres (OCP), jusqu'a MAX_ARGS_NUMBER (4):
		* -------(Chaque parametre prends 2bits)
		* 01 SI Registre, Suivie d’un octet            (le numéro de registre)
		* 10 SI Direct,   Suivie de DIR_SIZE (4)octets (la valeur directement)
		* 11 Si Indirect, Suivie de IND_SIZE octets    (la valeur de l’indirection)
	
				Ex : sti r1, %:live, %1 == 0x0b | 0x68
									  (sti)	| (r1, %:line, %1) == (01, 10, 10, 00)

