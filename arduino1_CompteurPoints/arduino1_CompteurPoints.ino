/**
 * The MIT License
 * Copyright (c) 2017 Florence Dervaux
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * Projet My Machine
 * arduino n°1: Compteur de Points
 */

//PARAMETRAGE BOUTONS
#define BOUTON_PLUS_DROITE    18    //Pin utilisée par le bouton
#define BOUTON_MOINS_DROITE   19
#define BOUTON_PLUS_GAUCHE    20
#define BOUTON_MOINS_GAUCHE   21
#define BOUTON_RESET          3
#define DELAI_REBONDS         1000

//PARAMETRAGE AFFICHEURS 7 SEGMENTS
#define NOMBRE_AFFICHEURS     4
#define DELAI_RAFRAICHIR      4

//PARAMETRAGE 74LS47
#define NBR_ENTREE_LS         4

//VARAIBLES UTILISÉES PAR LES 74LS47
int EntreeLS[NOMBRE_AFFICHEURS][NBR_ENTREE_LS] = {{22, 23, 24, 25},  // pin utilisées par les 74ls47
                                                  {26, 27, 28, 29},
                                                  {30, 31, 32, 33},
                                                  {34, 35, 36, 37}};

  
//VARIABLES UTILISÉE POUR LES AFFICHEURS
int Anodes[NOMBRE_AFFICHEURS] = {38, 39, 40, 41};
int Nombres[NOMBRE_AFFICHEURS] = {1, 3, 6, 8}; //Nombres à afficher sur chaque afficheur
byte Afficheur = 0; //Numéro du dernier afficheur rafraichi
unsigned long DernierRafraichissement = 0; //Utilisé avec millis()


void setup() {  
  int i = 0;
  int j = 0;
  // Anodes configurés en sortie
  for (i = 0; i < NOMBRE_AFFICHEURS; i++)
  {
    pinMode(Anodes[i], OUTPUT);
  }

  // Entrées 74LS47 configurées en sortie
  for (i = 0; i < NOMBRE_AFFICHEURS; i++)
  {
    for (j = 0; i < NBR_ENTREE_LS; i++)
    {
      pinMode(EntreeLS[i][j], OUTPUT);
    }
  }
}

void loop() {
  RafraichirAffichage();
}


void RafraichirAffichage()
{
  int i = 0;
  if ((millis() - DernierRafraichissement) > DELAI_RAFRAICHIR / NOMBRE_AFFICHEURS)
  {
    for (i = 0; i < NOMBRE_AFFICHEURS; i++)
    {
      digitalWrite(Anodes[i], LOW);
    }
    digitalWrite(Anodes[Afficheur], HIGH);

    for (i = 0; i < NBR_ENTREE_LS; i++)
    {
      digitalWrite(EntreeLS[Afficheur][i], bitRead(Nombres[Afficheur], i));
    }
    Afficheur = (Afficheur + 1) % NOMBRE_AFFICHEURS;
    DernierRafraichissement = millis();
  }
}





