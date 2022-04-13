/*  Classe contenant les elements necessaires pour la representation et
    sauvegarde des objets dans la file prioritaire.

    AUTEURS:
        David Genois GEND13119801
        Mathieu Lalonde LALM14127501
*/
#if !defined(__OBJETPQ_H__)
#define __OBJETPQ_H__

#include <iostream>

#include "lieu.h"
#include "objetpq.h"

class ObjetPQ {
   public:
    ObjetPQ();
    ObjetPQ(const Lieu* lieu, double distanceEstimee);
    ~ObjetPQ();

    bool operator>(const ObjetPQ& objet) const;
    bool operator<(const ObjetPQ& objet) const;
    bool operator==(const ObjetPQ& objet) const;

    double distanceEstimee;
    // double distanceCumul;
    const Lieu* lieu;

   private:
    // list<Lieu*> cheminJusquIci;
};

bool ObjetPQ::operator<(const ObjetPQ& o) const {
    return (this->distanceEstimee < o.distanceEstimee);
}

bool ObjetPQ::operator>(const ObjetPQ& o) const {
    return (this->distanceEstimee > o.distanceEstimee);
}

bool ObjetPQ::operator==(const ObjetPQ& o) const {
    return (this->distanceEstimee == o.distanceEstimee);
}

ObjetPQ::ObjetPQ() {
    this->distanceEstimee = numeric_limits<double>::infinity();
    // this->distanceCumul = 0;
    // this->lieu;
    ;
}

ObjetPQ::ObjetPQ(const Lieu* lieu, double distanceEstimee) {
    this->distanceEstimee = distanceEstimee;
    // this->distanceCumul = distanceCumul;
    this->lieu = lieu;
    ;
}

ObjetPQ::~ObjetPQ() {
}

#endif
