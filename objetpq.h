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

class ObjetPQ {
   public:
    ObjetPQ();
    ObjetPQ(const Lieu* lieu, double distanceEstimee);
    ~ObjetPQ();

    bool operator>(const ObjetPQ& objet) const;
    bool operator<(const ObjetPQ& objet) const;
    bool operator==(const ObjetPQ& objet) const;

    double distanceEstimee;
    const Lieu* lieu;

   private:
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
    ;
}

ObjetPQ::ObjetPQ(const Lieu* lieu, double distanceEstimee) {
    this->distanceEstimee = distanceEstimee;
    this->lieu = lieu;
    ;
}

ObjetPQ::~ObjetPQ() {
}

#endif
