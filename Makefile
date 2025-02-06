# INF3105 - Structures de données et algorithmes
# UQAM / Département d'informatique
#
# Fichier Makefile pour le TP4.
# Pour compiler en mode release, il suffit de taper la commande make.
# Pour compiler en mode debug, il suffit de taper la commande make DEBUG=1.

OPTIONS = -Wall -Wextra -std=c++17 $(if $(DEBUG),-ggdb -O0,-O3 -DNDEBUG)

all: tp4 testdate

testdate: testdate.o dateheure.o arbreavl.h arbremap.h
	g++ ${OPTIONS} $^ -o $@

tp4: tp4.o historique.o dateheure.o arbreavl.h arbremap.h
	g++ ${OPTIONS} $^ -o $@

%.o: %.cpp
	g++ ${OPTIONS} -o $@ -c $<

clean:
	rm -rf tp4 testdate *~ *.o
