/* TP4 - Recherche de suspects
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 */

#include <cassert>
#include <fstream>
#include <iostream>

#include "historique.h"

using namespace std;

void tp4(istream& entree) {
  Historique historique;
  string nomPersonne, nomLieu, nomPersonne2;
  DateHeure dh;
  Intervalle intervalle;
  while (entree) {
    string cmd;
    char pv = 0;
    entree >> cmd;
    if (!entree) break;

    if (cmd == "trace") {
      entree >> dh >> nomLieu >> nomPersonne >> pv;
      historique.trace(dh, nomLieu, nomPersonne);
      cout << "OK" << endl;
    } else if (cmd == "localiser") {
      entree >> intervalle >> nomPersonne >> pv;
      const ArbreAVL<string> lieux = historique.localiser(intervalle, nomPersonne);
      for (ArbreAVL<string>::Iterateur iter = lieux.debut(); iter; ++iter)
        cout << *iter << " ";
      cout << endl;
    } else if (cmd == "presences") {
      entree >> intervalle >> nomLieu >> pv;
      const ArbreAVL<string> personnes = historique.presences(intervalle, nomLieu);
      for (ArbreAVL<string>::Iterateur iter = personnes.debut(); iter; ++iter)
        cout << *iter << " ";
      cout << endl;
    } else if (cmd == "frequentations") {
      entree >> intervalle >> nomPersonne >> pv;
      const ArbreAVL<string> personnes = historique.frequentations(intervalle, nomPersonne);
      for (ArbreAVL<string>::Iterateur iter = personnes.debut(); iter; ++iter)
        cout << *iter << " ";
      cout << endl;
    } else if (cmd == "duree_rencontres") {
      entree >> intervalle >> nomPersonne >> nomPersonne2 >> pv;
      const int dr = historique.duree_rencontres(intervalle, nomPersonne, nomPersonne2);
      cout << dr << endl;
    }

    assert(pv == ';');
  }
}

int main(int argc, const char* argv[]) {
  if (argc > 1) {
    ifstream entree(argv[1]);
    if (entree.fail()) {
      cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << endl;
      return EXIT_FAILURE;
    } else
      tp4(entree);
  } else
    tp4(cin);

  return EXIT_SUCCESS;
}
