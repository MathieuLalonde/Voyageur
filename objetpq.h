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
    ObjetPQ(const Lieu* lieu, double distanceEstimee, double distanceRestanteEstimee);
    ~ObjetPQ();

    bool operator>(const ObjetPQ& objet) const;
    bool operator<(const ObjetPQ& objet) const;
    bool operator==(const ObjetPQ& objet) const;

    double distanceRestanteEstimee;
    double distanceEstimee;
    const Lieu* lieu;

   private:
};

bool ObjetPQ::operator<(const ObjetPQ& o) const {
    return (this->distanceRestanteEstimee < o.distanceRestanteEstimee);
}

bool ObjetPQ::operator>(const ObjetPQ& o) const {
    return (this->distanceRestanteEstimee > o.distanceRestanteEstimee);
}

bool ObjetPQ::operator==(const ObjetPQ& o) const {
    return (this->distanceRestanteEstimee == o.distanceRestanteEstimee);
}

ObjetPQ::ObjetPQ() {
    this->distanceEstimee = numeric_limits<double>::infinity();
    ;
    this->distanceRestanteEstimee = numeric_limits<double>::infinity();
    ;
}

ObjetPQ::ObjetPQ(const Lieu* lieu, double distanceEstimee, double distanceRestanteEstimee) {
    this->distanceEstimee = distanceEstimee;
    this->distanceRestanteEstimee = distanceRestanteEstimee;
    this->lieu = lieu;
    ;
}

ObjetPQ::~ObjetPQ() {
}

#endif
