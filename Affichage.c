int centerX=80;
int centerY=50;
int radius=50;
void drawRay(int angleDeg) {
    int endX = centerX + radius * cosDegrees(angleDeg);
    int endY = centerY - radius * sinDegrees(angleDeg);  // -sin pour corriger laxe Y inversé

    drawLine(centerX, centerY, endX, endY);
}

void affiche_position(int position, int objectif){
	drawEllipse(30,0,130,100);
  drawRay(position-90); //-90 pour que le °0 soit considéré en haut et pas à droite
	drawRay(objectif-90);
}
void affichage_menu_principal(){

	displayStringAt(30,75,"Robot ");
	displayStringAt(30,65,"Fixe");
	drawLine(5,60,70,120);
	drawLine(70,120,70,0);
	drawLine(70,0,5,60);
	displayStringAt(95,75,"Robot ");
	displayStringAt(95,65,"Mobile");
	drawLine(80,0,80,120);
	drawLine(150,60,80,120);
	drawLine(150,60,80,0);


}
void affichage_menu_init(){
	displayStringAt(20,75,"360 ");
	displayStringAt(20,65,"Gauche");
	drawLine(5,60,60,120);
	drawLine(60,120,60,0);
	drawLine(60,0,5,60);
	drawRect(65,0,105,120);
	displayStringAt(70,75,"Let's");
	displayStringAt(80,60,"Go");
	displayStringAt(120,75,"360 ");
	displayStringAt(120,65,"Droit");
	drawLine(110,0,110,120);
	drawLine(177,60,110,120);
	drawLine(177,60,110,0);

}
