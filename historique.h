/* TP4 - Recherche de suspects
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * MARIUS GUIMATSIA AKALONG GUIM27309006
 * SENAYAH KOSSIWA SENK14299107
 */

#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <string>

#include "arbremap.h"
#include "dateheure.h"

using namespace std;


struct Trace {
    DateHeure date;
    mutable string lieu;
    bool operator<(const Trace& other) const {
        if (date == other.date)
            return lieu < other.lieu;
        return date < other.date;
    }
    bool operator==(const Trace& other) const {
        return date == other.date;
    }
    mutable bool enleve = false;

    
};
/** Un objet de type Historique :
    - contient des traces et offre une (représentation, partie privée);
    - offre une interface publique pour ajouter des traces et exécuter des requêtes.
 */
class Historique {
 public:
  // Ajouter une trace
  void trace(DateHeure dh, const string& lieu, const string& nomPersonne);

  // Les 4 types de requête
  ArbreAVL<string> localiser(const Intervalle&,
                             const string& nomPersonne) const;
  ArbreAVL<string> presences(const Intervalle&, const string& nomLieu) const;
  ArbreAVL<string> frequentations(const Intervalle&,
                                  const string& nomPersonne) const;
  int duree_rencontres(const Intervalle&, const string& nomPersonne1,
                       const string& nomPersonne2) const;

 private:
  // À Compléter.
   ArbreMap<string, ArbreAVL<Trace>> traces; // personne -> (date -> lieu)
};

#endif
