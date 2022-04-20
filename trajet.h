/*  Classe contenant les elements necessaires pour la representation et
    sauvegarde des objets dans la file prioritaire.

    AUTEURS:
        David Genois GEND13119801
        Mathieu Lalonde LALM14127501
*/
#if !defined(__TRAJET_H__)
#define __TRAJET_H__

#include <iostream>
#include <set>

#include "lieu.h"
// TODO: inclure carte.h non? mais ca compile pas si on fait ca..

class Trajet {
   public:
    bool operator>(const Trajet& objet) const;
    bool operator<(const Trajet& objet) const;
    bool operator==(const Trajet& objet) const;

   private:
    const Lieu* depart;
    const Lieu* arrivee;
    double distanceEstimee;
    double distanceReele = -1;
    std::list<string> out_cheminNoeuds;
    std::list<string> out_cheminRoutes;

    friend class Carte;
};

#endif
