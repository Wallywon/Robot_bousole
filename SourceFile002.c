
#include "RobotFixe.c"
#include "RobotMobile.c"

//Code Complet :




/*initialisation*/
void initialize(int robot_type) {

	affichage_menu_init();

	if(robot_type==0){
		displayTextLine(0, "Initilisation du robot fixe");
		}
	else if(robot_type==1){
	displayTextLine(0, "Initilisation du robot mobile");
	}

	while (getButtonPress(buttonEnter)!=1) {
		if(getButtonPress(buttonLeft) == 1){
		setMotorSpeed(motorA,-20);
		delay(1800); //attente de 1800 car besoin de 1.800 secondes pour faire 360° a puissance 20%
		setMotorSpeed(motorA,0);
		while(getButtonPress(buttonLeft)){} // Permet d'attendre qu'on relache le bouton
		}
		if(getButtonPress(buttonRight) == 1){
			setMotorSpeed(motorA,20);
			delay(1800);//attente de 1800 car besoin de 1.800 secondes pour faire 360° a puissance 20%
			setMotorSpeed(motorA,0);
			while(getButtonPress(buttonLeft)){} // Permet d'attendre qu'on relache le bouton
		}
	}
	resetMotorEncoder(motorA);
	resetGyro(S1);
	while (getButtonPress(buttonEnter)==1){}
	eraseDisplay();

}


/*Main et menu princial */

task main(){
	semaphoreInitialize(mutexObjectif); //initilisation du sémaphore

	//a tout moment on peut arreter le programme avec le bouton Sensor
	while(getTouchValue(S2)!=1){

		// Si on appuie sur le bouton entrer, alors on relance le menu principal (SAUF quand on est dans une initialisation)
		if(getButtonPress(buttonEnter)==1){
		//arrivée sur le menu principal, arret du moteur et de toutes les taches, efface ce qui est afficher a l ecran pui affiche le menu
			launchMotorSpeed(0);

			stopTask(KeepHeadingPID);
			stopTask(watchButtons);
			stopTask(IHM);

			stopTask(KeepHeadingPID2);
			stopTask(watchButtons2);
			stopTask(IHM2);

			eraseDisplay();
			affichage_menu_principal();

			//tant que l'on appuie pas sur bouton droit, gauche ou le Sensor, alors on attend
			while(getButtonPress(buttonLeft)==0 && getButtonPress(buttonRight)==0 && getTouchValue(S2)==0){}
			//si on appuie sur boutton gauche, après l'avoir relaché, on efface ce qu'il y a a l ecran, lance la fonction d'initilisation PUIS les taches du robot fixe
			if(getButtonPress(buttonLeft)==1){
				while(getButtonPress(buttonLeft)==1){}
				eraseDisplay();
			  initialize(0);
				startTask(KeepHeadingPID);
				startTask(watchButtons);
				startTask(IHM);

			}
			//si on appuie sur boutton droit, après l'avoir relaché, on efface ce qu'il y a a l ecran, lance la fonction d intitialisation puis les taches du robot fixe
			if(getButtonPress(buttonRight)==1 ){
				while(getButtonPress(buttonRight)==1){}
			  eraseDisplay();
			  initialize(1);
				startTask(KeepHeadingPID2);
				startTask(watchButtons2);
				startTask(IHM2);

			}
		}

	}
}
