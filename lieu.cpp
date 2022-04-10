/*
   Classe Lieu/SegRoute
*/

#include "lieu.h"

using namespace std;

Lieu::SegRoute::SegRoute() {}

Lieu::SegRoute::SegRoute(const string nom, Lieu* depart, Lieu* arrivee) {
    this->nom = nom;
    this->arrivee = arrivee;
    this->longueur = depart->coor.distance((*arrivee).coor);

    cout << nom << ": " << longueur << " m" << endl;
}