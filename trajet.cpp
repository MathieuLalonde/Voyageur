#include "trajet.h"

bool Trajet::operator<(const Trajet& o) const {
    return (this->distanceEstimee < o.distanceEstimee);
}

bool Trajet::operator>(const Trajet& o) const {
    return (this->distanceEstimee > o.distanceEstimee);
}

bool Trajet::operator==(const Trajet& o) const {
    return (this->distanceEstimee == o.distanceEstimee);
}