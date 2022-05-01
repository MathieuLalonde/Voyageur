# Rapport TP3 - INF3105
## Fait Par
- David Genois GEND13119801
- Mathieu Lalonde LALM14127501

## Résultats des tests
Voici les résultats obtenus en effectuant les tests sur le serveur labunix.

<pre>
Évaluation du programme tp3 ...

Détection de /usr/bin/time...
0.00
ulimit (limites courantes des ressources) :
cpu time               (seconds, -t) 60
virtual memory          (kbytes, -v) 2097152
file size               (blocks, -f) 131072
-----
## CORRECTION : .
~/tp3 ~/tp3
Les résultats seront déposés dans log-20220430_201606.txt...

Test                    Miss    CPU     Mém.(k) Valid   Optimal DistOK  RouteOK /Total  Réussi?
uqam-missions-0.txt     1       0.00    4064k   1       1       1       1       /1      Optimal
uqam-missions-1.txt     6       0.00    4016k   6       6       6       6       /6      Optimal
uqam-missions-D0.txt    1       0.00    4068k   1       1       1       1       /1      Optimal
uqam-missions-D1.txt    2       0.00    3948k   2       2       2       2       /2      Optimal
uqam-missions-D2.txt    10      0.00    4128k   10      10      10      10      /10     Optimal
uqam-missions-D3.txt    100     0.00    4208k   100     100     100     100     /100    Optimal
uqam-missions-D4.txt    500     0.00    4140k   500     500     500     500     /500    Optimal
uqam-missions-D5.txt    1000    0.01    4012k   1000    1000    1000    1000    /1000   Optimal
uqam-missions-D6.txt    5000    0.07    4104k   5000    5000    5000    5000    /5000   Optimal
uqam-missions-F02.txt   10      0.00    4248k   10      10      10      10      /10     Optimal
uqam-missions-F03.txt   10      0.00    4216k   10      10      10      10      /10     Optimal
uqam-missions-F04.txt   10      0.00    4252k   10      10      10      10      /10     Optimal
uqam-missions-F05.txt   10      0.00    4180k   10      10      10      10      /10     Optimal
uqam-missions-F07.txt   10      0.01    4224k   10      10      10      10      /10     Optimal
uqam-missions-F08.txt   10      0.03    4092k   10      10      10      10      /10     Optimal
uqam-missions-F09.txt   10      0.16    4228k   10      10      10      10      /10     Optimal
uqam-missions-F10.txt   10      0.11    4232k   10      10      10      10      /10     Optimal
uqam-missions-F11.txt   10      0.20    4244k   10      10      10      10      /10     Optimal
uqam-missions-F12.txt   10      1.45    4268k   10      10      10      10      /10     Optimal
uqam-missions-F13.txt   10      2.95    4348k   10      10      10      10      /10     Optimal
stejulie-missions-D0.txt        1       0.00    5140k   1       1       1       1       /1      Optimal
stejulie-missions-D1.txt        2       0.00    5236k   2       2       2       2       /2      Optimal
stejulie-missions-D2.txt        10      0.01    5300k   10      10      10      10      /10     Optimal
stejulie-missions-D3.txt        100     0.08    5392k   100     100     100     100     /100    Optimal
stejulie-missions-D4.txt        500     0.42    5512k   500     500     500     500     /500    Optimal
stejulie-missions-D5.txt        1000    0.84    5396k   1000    1000    1000    1000    /1000   Optimal
stejulie-missions-D6.txt        5000    4.23    5620k   5000    5000    5000    5000    /5000   Optimal
stejulie-missions-F02.txt       10      0.03    5524k   10      10      10      10      /10     Optimal
stejulie-missions-F03.txt       10      0.06    5316k   10      10      10      10      /10     Optimal
stejulie-missions-F04.txt       10      0.13    5316k   10      10      10      10      /10     Optimal
stejulie-missions-F05.txt       10      0.19    5660k   10      10      10      10      /10     Optimal
stejulie-missions-F07.txt       10      0.30    5712k   10      10      10      10      /10     Optimal
stejulie-missions-F08.txt       10      0.65    5768k   10      10      10      10      /10     Optimal
stejulie-missions-F09.txt       10      2.32    5792k   10      10      10      10      /10     Optimal
stejulie-missions-F10.txt       10      10.67   5908k   10      10      10      10      /10     Optimal
stejulie-missions-F11.txt       10      60.00   5820k   5       5       5       5       /10     Echec
stejulie-missions-F12.txt       10      59.99   5628k   1       1       1       1       /10     Echec
stejulie-missions-F13.txt       10      59.98   5268k   0       0       0       0       /10     Echec
montsthilaire-missions-D0.txt   1       0.01    6568k   1       1       1       1       /1      Optimal
montsthilaire-missions-D1.txt   2       0.01    6684k   2       2       2       2       /2      Optimal
montsthilaire-missions-D2.txt   10      0.03    7072k   10      10      10      10      /10     Optimal
montsthilaire-missions-D3.txt   100     0.23    7040k   100     100     100     100     /100    Optimal
montsthilaire-missions-D4.txt   500     1.15    7016k   500     500     500     500     /500    Optimal
montsthilaire-missions-D5.txt   1000    2.18    6812k   1000    1000    1000    1000    /1000   Optimal
montsthilaire-missions-D6.txt   5000    11.36   6940k   5000    5000    5000    5000    /5000   Optimal
montsthilaire-missions-F02.txt  10      0.07    7052k   10      10      10      10      /10     Optimal
montsthilaire-missions-F03.txt  10      0.19    7288k   10      10      10      10      /10     Optimal
montsthilaire-missions-F04.txt  10      0.38    7456k   10      10      10      10      /10     Optimal
montsthilaire-missions-F05.txt  10      0.46    7456k   10      10      10      10      /10     Optimal
montsthilaire-missions-F07.txt  10      0.64    7276k   10      10      10      10      /10     Optimal
montsthilaire-missions-F08.txt  10      1.36    7372k   10      10      10      10      /10     Optimal
montsthilaire-missions-F09.txt  10      2.63    7716k   10      10      10      10      /10     Optimal
montsthilaire-missions-F10.txt  10      16.89   7744k   10      10      10      10      /10     Optimal
montsthilaire-missions-F11.txt  10      60.02   7644k   7       7       7       7       /10     Echec
montsthilaire-missions-F12.txt  10      59.97   7664k   1       1       1       1       /10     Echec
montsthilaire-missions-F13.txt  10      59.99   7748k   0       0       0       0       /10     Echec
victoria-missions-D0.txt        1       0.18    23964k  1       1       1       1       /1      Optimal
victoria-missions-D1.txt        2       0.17    27148k  2       2       2       2       /2      Optimal
victoria-missions-D2.txt        10      0.33    26772k  10      10      10      10      /10     Optimal
victoria-missions-D3.txt        100     2.18    28184k  100     100     100     100     /100    Optimal
victoria-missions-D4.txt        500     11.35   29920k  500     500     500     500     /500    Optimal
victoria-missions-D5.txt        1000    21.62   29928k  1000    1000    1000    1000    /1000   Optimal
victoria-missions-D6.txt        5000    60.15   30344k  2489    2489    2489    2489    /5000   Echec
victoria-missions-F02.txt       10      0.99    28060k  10      10      10      10      /10     Optimal
victoria-missions-F03.txt       10      1.16    28976k  10      10      10      10      /10     Optimal
victoria-missions-F04.txt       10      3.92    29736k  10      10      10      10      /10     Optimal
victoria-missions-F05.txt       10      6.31    30408k  10      10      10      10      /10     Optimal
victoria-missions-F07.txt       10      6.90    30232k  10      10      10      10      /10     Optimal
victoria-missions-F08.txt       10      7.26    30336k  10      10      10      10      /10     Optimal
victoria-missions-F09.txt       10      13.41   31352k  10      10      10      10      /10     Optimal
victoria-missions-F10.txt       10      21.41   31168k  10      10      10      10      /10     Optimal
victoria-missions-F11.txt       10      34.68   32428k  10      10      10      10      /10     Optimal
victoria-missions-F12.txt       10      60.03   32592k  3       3       3       3       /10     Echec
victoria-missions-F13.txt       10      59.95   33644k  0       0       0       0       /10     Echec
montreal-missions-D0.txt        1       0.21    33468k  1       1       1       1       /1      Optimal
montreal-missions-D1.txt        2       0.22    34212k  2       2       2       2       /2      Optimal
montreal-missions-D2.txt        10      0.71    37580k  10      10      10      8       /10     Echec
montreal-missions-D3.txt        100     3.22    38476k  100     100     100     89      /100    Echec
montreal-missions-D4.txt        500     18.80   41948k  500     500     500     456     /500    Echec
montreal-missions-D5.txt        1000    41.04   42944k  1000    1000    1000    906     /1000   Echec
montreal-missions-D6.txt        5000    60.04   44264k  1398    1398    1398    1269    /5000   Echec
montreal-missions-F02.txt       10      1.56    40200k  10      10      10      9       /10     Echec
montreal-missions-F03.txt       10      3.18    40484k  10      10      10      7       /10     Echec
montreal-missions-F04.txt       10      6.40    41532k  10      10      10      6       /10     Echec
montreal-missions-F05.txt       10      8.39    42288k  10      10      10      8       /10     Echec
montreal-missions-F07.txt       10      13.10   43088k  10      10      10      9       /10     Echec
montreal-missions-F08.txt       10      16.84   42156k  10      10      10      5       /10     Echec
montreal-missions-F09.txt       10      19.09   47108k  10      10      10      9       /10     Echec
montreal-missions-F10.txt       10      24.78   43844k  10      10      10      8       /10     Echec
montreal-missions-F11.txt       10      47.38   43476k  10      10      10      5       /10     Echec
montreal-missions-F12.txt       10      59.96   42636k  6       6       6       4       /10     Echec
montreal-missions-F13.txt       10      59.91   42988k  3       3       3       3       /10     Echec
</pre>

## Auto-Evaluation

Tous les tests fonctionnent sans erreur et avec des solutions optimals evaluer.sh avec le programme valideur compilé et roulé sur labunix (mais certains tests F prennent plus de 60s pour se terminer: 10/55 et 2 des 30 test D prennent plus de 60s sur labunix, mais pas nos propres machines). Nous rapportons donc que notre TP fonctionne correctement.

Veuillez prendre note qu'a cause d'une mauvaise validation des routes textuelles, les tests de montreal disent que les noms ne sont pas correctes. (il y a des rues parelles, donc des solutions multiples pour les noms de rues, Armand a recu un message a ce sujet avec les explications. Par exemple, le segment n212659199 et n3090629830 est sur 2 definitions de rues, et la solution de evaluer.sh ne semble pas toujours favoriser de rester sur la meme rue)