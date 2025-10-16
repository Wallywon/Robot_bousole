
int maxPower2=49; //puissance maximale
float maxSpeed2=490;  //vitesse maximale
int minPower2=2; // puissance minimale avant arret du moteur
float minSpeed2=10;  //vitesse minimale avant arret du moteur
bool stopProgram=false; //variable permettant de stoper le programme

/********fonctions du robot mobile : ********/




//tache qui lance le moteur a une vitesse donnée
void launchMotorSpeed2(float speed){
	int sens = 1;
	float absspeed=abs(speed);

	if(speed<0){
		 sens=-1;
	}
	if(absspeed>maxSpeed2){
		setMotorSpeed(motorA,maxPower2*sens);
	}
	else if(absspeed<minSpeed2 && speed!=0){
		setMotorSpeed(motorA,minPower2*sens);
	}
	else {
		setMotorSpeed(motorA,speed*0.1);
	}
}

//Tache qui indique au moteur de suivre l'objectif
//Tache KeepHeadingPID()

task KeepHeadingPID2(){
	int position;
	int tab[10]={0,0,0,0,0,0,0,0,0,0};
	int i=0;
	int coef=0;

	while(1){

		position= getGyroDegrees(S1);
		if(abs(0-position)>4){
			tab[i%10]=0-position;
			i=i+1;
			coef=0;
			for(int j=0;j<10;j++){
				coef= coef+tab[j];
			}
			float vitesse=0.6*(-position)+coef*0.006+(-0.02)*(getMotorRPM(motorA)*6);
			launchMotorSpeed2(vitesse);
	}
	else{
		launchMotorSpeed2(0);

	  }

	}
}

//tache watchButton2
task watchButtons2(){
	while(1){
      if(getButtonPress(buttonEnter)){
      while(getButtonPress(buttonEnter)){}
      stopProgram = true;
      }
  }
}

task IHM2(){
		while(1){
			displayTextLine(1,"consigne : 0°, cap actuel: %d ",getGyroDegrees(S1));
			displayTextLine(3,"ROBOT MOBILE ");
			affiche_position(0,getGyroDegrees(S1));
			delay(100);
			eraseDisplay();
	}
}
/********fin des fonctions robot mobile : ********/
