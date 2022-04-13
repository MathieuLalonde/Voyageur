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
}

bool Lieu::operator<(const Lieu& lieu) const {
    return (this->nom < lieu.nom);
}

bool Lieu::operator>(const Lieu& lieu) const {
    return (this->nom > lieu.nom);
}

bool Lieu::operator==(const Lieu& lieu) const {
    return (this->nom == lieu.nom);
}

Lieu::Lieu() {
}

Lieu::Lieu(string nom, Coordonnee coor) {
    this->nom = nom;
    this->coor = coor;
    ;
}

// Lieu::~Lieu() {
// }