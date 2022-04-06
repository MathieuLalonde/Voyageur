#!/bin/bash
generer="../solution2/generer"
cartes=`ls *-carte.txt`


echo "Liste des cartes : $cartes"

for carte in $cartes;
do
    echo "Génération de ${carte} ..."
    (
    set -x #echo on
    ${generer} $carte 1 1 > ${carte%-carte.txt}-missions-D0.txt
    ${generer} $carte 2 1 > ${carte%-carte.txt}-missions-D1.txt
    ${generer} $carte 10 1 > ${carte%-carte.txt}-missions-D2.txt
    ${generer} $carte 100 1  > ${carte%-carte.txt}-missions-D3.txt
    ${generer} $carte 500 1 > ${carte%-carte.txt}-missions-D4.txt
    ${generer} $carte 1000 1 > ${carte%-carte.txt}-missions-D5.txt
    ${generer} $carte 5000 1 > ${carte%-carte.txt}-missions-D6.txt

    ${generer} $carte 10 2 > ${carte%-carte.txt}-missions-F02.txt
    ${generer} $carte 10 3 > ${carte%-carte.txt}-missions-F03.txt
    ${generer} $carte 10 4 > ${carte%-carte.txt}-missions-F04.txt
    ${generer} $carte 10 5 > ${carte%-carte.txt}-missions-F04.txt
    ${generer} $carte 10 6 > ${carte%-carte.txt}-missions-F05.txt
    ${generer} $carte 10 7 > ${carte%-carte.txt}-missions-F07.txt
    ${generer} $carte 10 8 > ${carte%-carte.txt}-missions-F08.txt
    ${generer} $carte 10 9 > ${carte%-carte.txt}-missions-F09.txt
    ${generer} $carte 10 10 > ${carte%-carte.txt}-missions-F10.txt
    ${generer} $carte 10 11 > ${carte%-carte.txt}-missions-F11.txt
    ${generer} $carte 10 12 > ${carte%-carte.txt}-missions-F12.txt
    ${generer} $carte 10 13 > ${carte%-carte.txt}-missions-F13.txt
#    ${generer} $carte 10 14 > ${carte%-carte.txt}-missions-F14.txt
#    ${generer} $carte 10 15 > ${carte%-carte.txt}-missions-F15.txt
#    ${generer} $carte 10 16 > ${carte%-carte.txt}-missions-F16.txt
#    ${generer} $carte 10 17 > ${carte%-carte.txt}-missions-F17.txt
    )
done

#tar cvfj tp3-tests.tar.bz2 tests/{evaluer.sh,lisezmoi.txt} tests/valideur-* tests/{uqam,stejulie,montsthilaire,victoria,montreal}-*.{txt,solution}

#zip tp3-tests.zip tests/{evaluer.sh,lisezmoi.txt} tests/valideur-* tests/{uqam,stejulie,montsthilaire,victoria,montreal}-*.{txt,solution}
