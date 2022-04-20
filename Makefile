# Makefile pour TP3

OUTPUT_ZIP_NAME = GEND13119801_LALM14127501.zip
OUTPUT_PDF_NAME = rapport_GEND13119801_LALM14127501.pdf

OPTIONS = -Wall

#Option -g pour avoir les infos de débogage
#OPTIONS = -g -O0 -Wall

#Option -O2 pour le code optimisé
OPTIONS = -O2 -Wall

# Syntaxe : cible : dépendance1 dépendance2 ...
# Ensuite, la ou les ligne(s) débutant par une tabulation (\t) donne les commandes pour construire une cible

all : tp3

tp3: tp3.o carte.o coordonnee.o lieu.o trajet.o
	g++ $(OPTIONS) -o tp3 tp3.o carte.o coordonnee.o lieu.o

tp3.o: tp3.cpp carte.h coordonnee.h
	g++ $(OPTIONS) -c -o tp3.o tp3.cpp

carte.o: carte.h carte.cpp coordonnee.h
	g++ $(OPTIONS) -c -o carte.o carte.cpp

coordonnee.o: coordonnee.h coordonnee.cpp
	g++ $(OPTIONS) -c -o coordonnee.o coordonnee.cpp

lieu.o: lieu.h lieu.cpp
	g++ $(OPTIONS) -c -o lieu.o lieu.cpp

trajet.o: trajet.h trajet.cpp
	g++ $(OPTIONS) -c -o trajet.o trajet.cpp

clean :
	rm -f *.o
	rm -f tp3
	rm -f *~
	rm -f *.resultat

clean-tests:
	rm -f *.txt
	rm -f *.resultat
	rm -f *.validation
	rm -f Mapnik/*

zip:
	make clean
	rm -f ${OUTPUT_ZIP_NAME}
	zip -r ${OUTPUT_ZIP_NAME} ${OUTPUT_PDF_NAME} *.h *.cpp Makefile

test:
	make clean
	make
	tests/evaluer.sh