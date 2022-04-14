# inf3105-tp3

# Note:

- Stocker les inputs
    - Map lieu:obj
        - coordonee
        - liste segments
            - nom
            - point d'arrivee
            - distance

- Algo graphe pour les distances
    - Pour les 14 lieux d'une mission:
        - A* distance vers tous les autres lieux de la mission
            - est-ce possible de prioriser de rester sur le même chemin?
        - Sauvegarder les trajets
    - Recup algo TP2 pour trouver le trajet optimal parmis ceux-là.


# TODO:
- Optimisation pour 1 (3pt) & 2+ (1pt bonus)
- Rapports (output de evaluer.sh) + docstring + clean up code/commentaire
- Validation sur labunix avant remise
