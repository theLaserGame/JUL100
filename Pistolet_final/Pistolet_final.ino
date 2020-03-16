      // ECRAN LCD 
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // initialise les commandes avec les n° de broches
int temps=1; // durée d'une partie 1min
int tmins=0;
int tsecond=0;
int currentTime;
int previousTime=0;

     //LASER
const int Laser=8;

     //BOUTON
const int bouton=9;
int val=0;



void setup()    
{pinMode(Laser,OUTPUT);
pinMode(bouton,INPUT);
Serial.begin(9600);
lcd.begin(20, 4); // initialiser le nombre de colonnes et de lignes
lcd.setCursor(0, 0); //le curseur se positionne à la première ligne et colonne
lcd.print("   LASER GAME");
lcd.setCursor(0, 1); //le curseur se positionne à la deuxième ligne et première colonne
lcd.print("Partie d'1 min");
lcd.setCursor(0, 3); //le curseur se positionne à la troisième ligne et première colonne
lcd.print("   BONNE CHANCE !");


}
    
void loop() {   // minuteur qui s'affiche sur l'écran

lcd.setCursor(0, 0); //le curseur se positionne à la première ligne et colonne
lcd.print("   LASER GAME");
lcd.setCursor(0, 1); //le curseur se positionne à la deuxième ligne et première colonne
lcd.print("Partie d'1 min");
lcd.setCursor(0, 3); //le curseur se positionne à la troisième ligne et première colonne
lcd.print("   BONNE CHANCE !");
val = digitalRead(bouton); // état du bouton 
temps=temps*60; 
while(temps>0){
  currentTime = millis(); // on recupere le temps depuis lequel le pistolet est allume
  if (currentTime-previousTime>1000){ // toutes les secondes, cette boucle if s'effectue
    previousTime=currentTime;
    temps=temps-1;  // on enlève une seconde au temps restant
    tsecond=temps%60;   // tsecond est le reste de la division euclidienne de temps par 60
    tmins=(temps-tsecond)/60;
    affichageMins();
    affichageSeconds();
  }
  val = digitalRead(bouton);
    while (val==LOW){//tant qu'on appuie sur le bouton, le laser s'allume mais en salves de 1 seconde
      digitalWrite(Laser,HIGH);
      delay(600);
      digitalWrite(Laser,LOW);
      delay(400);
      break;
}
   if((tmins==0) && (tsecond==0)){   // si le temps est écoulé on efface ce qui est écrit sur l'écran 
      lcd.clear();
   }
   
   }
   finPartie(); // On utilise la fonction permettant d'afficher la fin de la partie

}










    // FONCTIONS ECRAN LCD 

void finPartie () {
lcd.setCursor(0, 0); 
lcd.print("    LASER GAME");
lcd.setCursor(0, 1); 
lcd.print("TIME'S OUT !!");
lcd.setCursor(0, 2); 
lcd.print("Fin de la partie !");
}



void affichageMins(){
  lcd.setCursor(0, 2);//le curseur se positionne à la deuxième ligne 
  lcd.print("Il reste:"); 
  lcd.setCursor(10, 2);// affichage des minutes
  lcd.print(tmins);
  lcd.print("m");
}



void affichageSeconds(){
  if (tsecond>=10){//si les secondes sont sup à 10 l'affichage se fait normalement il n'y a pas de problème

  lcd.print(tsecond);
  lcd.print("s");
  }
  else{  lcd.setCursor(12, 2); //dans le cas contraire, il faut d'abord afficher 00 puis remplacer le 0 de droite par les secondes 
  lcd.print("00");
  lcd.setCursor(13, 2); 
  lcd.print(tsecond);
  lcd.print("s");
  }
}


// Note : cette fonction n'a pas pu etre utilisee dans le loop final. elle marche lorsque l'ecran est branche seul, mais avec le laser les delay bloquent le fonctionnement
// correct du pistolet
void chrono(){temps=temps*60;   // on converti le temps en secondes
while (temps>0) {   // tant qu'il reste du temps
  temps=temps-1;  // on enlève une seconde toutes les secondes
  tsecond=temps%60;   // tsecond est le reste de la division euclidienne de temps par 60
  tmins=(temps-tsecond)/60;
  delay(1000);
  affichageMins();
  affichageSeconds();
  if((tmins==0) && (tsecond==0)){   // si le temps est écoulé on efface ce qui est écrit sur l'écran 
    lcd.clear();
  }
}
 //on affiche le message de fin de partie
finPartie();}

  
