#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
const int RX=10;
const int TX=11;
SoftwareSerial BlueT(RX,TX);
#define PIXEL_PIN 6 // On définit le pin où est connecté la patte DATA du bandeau
#define PIXEL_COUNT 24 // On définit le nombre de LED compris sur le Ruban de LED soit 150 pour le ruban de 5m50
//const int ldr = 0;

//int val;
String joueur="";
String color="";
int temps; 
int r; 
int v;
int b;
const int ldr1 = 0;
const int ldr2 = 1;
const int ldr3 = 2;
const int ldr4 = 3;
const int ldr5 = 4;
const int ldr6 = 5;

int val1;
int val2;
int val3;
int val4;
int val5;
int val6;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
 
//Ici, le 150 correspond au nombre de led
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, 6, NEO_GRB + NEO_KHZ800);
 
void setup() {
  Serial.begin(9600);
  BlueT.begin(9600);
  strip.begin();
  strip.show(); 
  
  // Initialise toute les led à 'off'
  /* Définition des couleurs */
//int RED[3] = {255, 0, 0}; // Couleur Rouge
//int GREEN[3] = {0, 255, 0}; // Couleur Verte
//int CYAN[3] = {0, 255, 255}; // Couleur Cyan
//int YELLOW[3] = {255, 125, 0}; // Couleur Jaune
//int ORANGE[3] = {255, 40, 0}; // Couleur Orange
//int PURPLE[3] = {255, 0 , 255}; // Couleur Violette
//int PINK[3] = {255, 0, 100}; // Couleur Rose
//int BLUE[3] = {0, 0, 255}; // Couleur Bleu
//int WHITE[3] = {255, 255, 255}; // Couleur Blanche
}
 
void loop() {
// La première valeur correspond au temps, la seconde  à l'intensité du rouge, la troisième au vert, et la quatrième au bleu
 
  val1=analogRead(ldr1);
  val2=analogRead(ldr2);
  val3=analogRead(ldr3);
  val4=analogRead(ldr4);
  val5=analogRead(ldr5);
  val6=analogRead(ldr6);

  colorAttribution();// le ruban s'allume de la bonne couleur
  
 if (val1>600||val2>600 || val3 >600 || val4>600 || val5>600 || val6>600) {// si le laser touche la ldr
  BlueT.print("touche"); 
  Serial.println(joueur);
  if (joueur=="rouge") {
    all(10, 255, 0, 0);//ruban allumé
    delay(800);
    all(10, 0, 0, 0);
  }
  if (joueur=="jaune") {
    all(10, 255, 125, 0);
    delay(800);
    all(10, 0, 0, 0);
  }
  if (joueur=="bleu") {
    all(10, 0, 0, 255);
    delay(800);
    all(10, 0, 0, 0);
  }
  
  if (joueur=="vert") {
    all(10, 0, 255, 0);
    delay(800);
    all(10, 0, 0, 0);
  }
    
}


}




void colorAttribution() {//allume le ruban selon la couleur rentrée
 
    color=lireBT();
    Serial.println(color);
    if (color=="rouge" ) {
      all(10, 255, 0, 0);//ruban allumé
      delay(2000);
      all(10, 0, 0, 0);
      joueur = color;//joueur prend la valeur de color et color se réinitialise à ""
      color = "";
    }
    if (color=="jaune") {
      all(10, 255, 125, 0);
      delay(2000);
      all(10, 0, 0, 0);
      joueur = color;
      color = "";
    }
    if (color=="bleu") {
      all(10, 0, 0, 255);
      delay(2000);
      all(10, 0, 0, 0);
      joueur = color;
      color = "";
    }
    
    if (color=="vert") {
      all(10, 0, 255, 0);
      delay(2000);
      all(10, 0, 0, 0);
      joueur = color;
      color = "";
    }
    
    if (color=="retourini") {
      all(10, 0, 0, 0);//ruban allumé
      joueur = color;
      color = "";
    }

}


//void sinon(){// affiche ERROR quand la couleur n'existe pas
//  if (color!="") { 
//    Serial.println("ERROR") ;Serial.println ("saisissez une autre couleur");
//    color = "";
//    }
//   }

   
void all(int temps, int r, int v, int b)//allume le ruban de manière continue
{
   for(int i = 0 ; i < 24 ; i++)
  {
     strip.setPixelColor(i, r, v, b);
  }
  strip.show();
  delay(temps); 
}


String lireBT(){
  int n;
  char cBT;
  String rBT="";
  String rBT2="";
  if (BlueT.available()){
    if ((char)BlueT.read()=='X'){
      while (true){ 
        cBT = (char)BlueT.read();
        if (cBT=='X') {
          break;
         }
        rBT+=cBT;
        }
      }
    Serial.println(rBT);
    return rBT;
  }
  
  }
