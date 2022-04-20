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
#include "carte.h"

class ObjetPQ {
   public:
    ObjetPQ();
    ObjetPQ(const Lieu* lieu, double fScore, double distanceEstimee, double distanceRestanteEstimee);
    ~ObjetPQ();

    bool operator>(const ObjetPQ& objet) const;
    bool operator<(const ObjetPQ& objet) const;
    bool operator==(const ObjetPQ& objet) const;


   private:
    double distanceRestanteEstimee;
    double distanceEstimee;
    const Lieu* lieu;
    double fScore;

    friend Carte;
};

bool ObjetPQ::operator<(const ObjetPQ& o) const {
    return (this->fScore < o.fScore);
}

bool ObjetPQ::operator>(const ObjetPQ& o) const {
    return (this->fScore > o.fScore);
}

bool ObjetPQ::operator==(const ObjetPQ& o) const {
    return (this->fScore == o.fScore);
}

ObjetPQ::ObjetPQ() {
    this->fScore = numeric_limits<double>::infinity();
    this->distanceEstimee = numeric_limits<double>::infinity();
    this->distanceRestanteEstimee = numeric_limits<double>::infinity();
}

ObjetPQ::ObjetPQ(const Lieu* lieu, double fScore, double distanceEstimee, double distanceRestanteEstimee) {
    this->distanceEstimee = distanceEstimee;
    this->distanceRestanteEstimee = distanceRestanteEstimee;
    this->lieu = lieu;
    this->fScore = fScore;
}

ObjetPQ::~ObjetPQ() {
}

#endif
