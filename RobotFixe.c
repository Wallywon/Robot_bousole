#include "SourceFile002.c"
#include "Affichage.c"
int maxPower=81; //puissance maximale
float maxSpeed=810;  //vitesse maximale
int minPower=2; // puissance minimale avant arret du moteur
float minSpeed=10;  //vitesse minimale avant arret du moteur
int objectif;

TSemaphore mutexObjectif;
/********fonction robot fixe : ********/


void launchMotorSpeed(float speed){
int sens = 1; //variable pour connaitre le sens du moteur souhaitée
float absspeed=abs(speed); //valeur absolue de la vitesse souhaitée

if(speed<0){ //vérification du sens du moteur souhaité
	 sens=-1;
}
if(absspeed>maxSpeed){ //si vitesse souhaitée est supérieur à la vitesse max
	setMotorSpeed(motorA,maxPower*sens); //mettre le moteur à la vitesse max
}
else if(absspeed<minSpeed && speed!=0){//si vitesse souhaitée est inférieur à la vitesse min et ne demande pas l'arret du moteur (vitesse =0)
	setMotorSpeed(motorA,minPower*sens); // mettre le moteur à la vitesse min
}
else {
	setMotorSpeed(motorA,speed*0.1); //si vitesse compris entre vitesse max et vitesse min, mettre le moteur à cette vitesse - 0.1 étant le coefficiant calculé lors de l'étude des caractéristiques du moteur
}
}

task KeepHeadingPID(){

	int position;
	int obj ;
	//initialisation du tableau des 10 dernières valeur de l'objectif-la position afin de calculer l'intégrale dans le calcul proposé en consigne
	int tab[10]={0,0,0,0,0,0,0,0,0,0};
	int nb_tour=0; //variable calculant le nombre de tour dans la boucle while
	int integral=0;

	while(1){
		//récupération de la position actuelle
		position=getMotorEncoder(motorA);
		//récupération avec sémaphore de l'objectif (afin de ne pas avoir de conflit avec WatchButton()
		semaphoreLock(mutexObjectif);
		obj= objectif;
		semaphoreUnlock(mutexObjectif);

		//si l'objectif et la position ne sont pas strictement identique
		if(abs(obj-position)>0){
			//nous ajoutons l'écart entre l'objectif et la position dans un tableau - utilisation d'un modulo 10 pour rester dans le tableau
			tab[nb_tour%10]=abs(obj-position);
			nb_tour=nb_tour+1;
			//réinitialisation du coefficiant
			integral=0;

			//calcul de l'intégrale
			for(int j=0;j<10;j++){
				integral= integral+tab[j];
			}

			//calcul de la vitesse a donner au moteur en utilisant le calcul PID de la consigne
			float vitesse=0.6*(obj-position)+integral*0.006+(-0.02)*(getMotorRPM(motorA)*6);
			launchMotorSpeed(vitesse);

		}
		else{
			//Si le moteur a atteind son objectif, arreter le moteur
			launchMotorSpeed(0);
	  }
	}
}

//tache qui surveille les boutons et modifie l'objectif en conséquence
task watchButtons(){

		while(1){
		//Si le bouton gauche est appuyé, modification de l'objectif de -10°
		if(getButtonPress(buttonLeft) == 1){
		semaphoreLock(mutexObjectif); //utilisation sémaphore pour éviter conflit avec tache keepHeading()
		objectif =objectif-10;
		semaphoreUnlock(mutexObjectif);
		while(getButtonPress(buttonLeft)){} // Permet d'attedre qu'on relache le bouton

	}
	//Meme chose pour bouton droit
	else if(getButtonPress(buttonRight) == 1){
			semaphoreLock(mutexObjectif);
			objectif =objectif+10;
			semaphoreUnlock(mutexObjectif);
		while(getButtonPress(buttonRight)){}
	}

	//Meme chose pour bouton droit
	else if(getButtonPress(buttonUp) == 1){
			semaphoreLock(mutexObjectif);
		objectif =objectif+90;
			semaphoreUnlock(mutexObjectif);
		while(getButtonPress(buttonUp)){}
	}
	//Meme chose pour bouton bas
	else if( getButtonPress(buttonDown) == 1){
			semaphoreLock(mutexObjectif);
		objectif =objectif-90;
			semaphoreUnlock(mutexObjectif);
		while(getButtonPress(buttonDown)){}
	}

}
}

//affiche continuellement à l'écran la position du moteur et l'objectif en °
	task IHM(){
		while(1){
		displayTextLine(1,"position : %d - objectif : %d",getMotorEncoder(motorA),objectif);
		displayTextLine(0,"ROBOT FIXE",getMotorEncoder(motorA),objectif);

		affiche_position(objectif,getMotorEncoder(motorA));
		delay(100);
		eraseDisplay();
		}
}

/********fin fonctions robot fixe: ********/
