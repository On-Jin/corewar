# corewar

VM : Machine Virtuelle

La VM dispose de 4096 cases memoires dans lesquels le bytecode des champions vont y etre ecris.
Le bytecode des champions est généré grace a l'asm qui traduit l'assembleur des .s en .cor.
Le bytecode est un ensemble d'instruction, suivis de ses parametres, qui defini donc les champions.
Ces meme instructions vont etre interpreté par les processus.

Les chmapions peuvent donc adopter differentes strategie :

(Ce n'est que 3 simples exemples)

-Sniper :
	*Ecrire de la memoire tres tres loins, afin de toucher les bytecodes source des autres champions
-Train :
	* Multiplier ses processus jusqu'a pouvoir ecrire les bytescodes permettant d'ecrire plus loins dans la memoire les meme bytecodes. C'est un train
-Tortue :
	*Multiplier ses processus pour creer des mur autour de ses bytecodes sources. Cela permet d'arreter les trains, car le mur doit s'ecrire plus souvent pour ecraser continuellement les bytescodes du train. Cela peut aussi permettre de faire travailler des processus qui ce serait perdu dans l'ecrasement des bytecodes.

/*
Video
FlutterShy
Helltrain
Turtle
*/
