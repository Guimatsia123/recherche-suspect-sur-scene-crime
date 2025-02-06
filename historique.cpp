/* TP4 - Recherche de suspects
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * MARIUS GUIMATSIA AKALONG GUIM27309006
 * SENAYAH KOSSIWA SENK14299107
 */

#include "historique.h"

void Historique::trace(DateHeure dh, const string& nomLieu,
 const string& nomPersonne) {
  Trace trace;
  trace.date = dh;
  trace.lieu = nomLieu;
  bool existe = false;
  if(traces.contient(nomPersonne)){
   for(ArbreAVL<Trace>::Iterateur it = traces[nomPersonne].debut(); it ; ++it){
    if((*it).date == dh){
      (*it).lieu = nomLieu;
      existe = true;
    }
  }
}
if(!existe)
  traces[nomPersonne].inserer(trace);
}

// Si une personne est localiser a une date d1 a un endroit PK jusqu"a sa prochaine 
// localisation d2, il est considerer comme etant au meme endroit.
//  ainsi durant l'intervalle [d1, d2[ il est considere etre au PK
ArbreAVL<string> Historique::localiser(const Intervalle& intervalle, const string& nomPersonne) const {
  ArbreAVL<string> lieux;

  if (traces.contient(nomPersonne)) {
    for (ArbreAVL<Trace>::Iterateur it = traces[nomPersonne].debut(); it ; ++it) {
      if((*it).lieu != "?" ){
        ArbreAVL<Trace>::Iterateur suivant = it;
        ++suivant;
        bool borne_inferieure= ((*it).date <= intervalle.debut 
          && (suivant == traces[nomPersonne].fin() || intervalle.debut < (*suivant).date));
        bool borne_superieure = ((*it).date < intervalle.fin 
          && (suivant == traces[nomPersonne].fin() || intervalle.fin < (*suivant).date));
        bool milieu_intervalle = (intervalle.debut <= (*it).date && (*it).date < intervalle.fin);
        bool localisation_pontuelle = (intervalle.debut == intervalle.fin 
          && ((*it).date <= intervalle.debut && (suivant == traces[nomPersonne].fin() 
            || intervalle.debut < (*suivant).date)));

        if (borne_inferieure || borne_superieure || milieu_intervalle || localisation_pontuelle ) {
          lieux.inserer((*it).lieu);
        }
      }
    }
  }

  return lieux;
}

// Pour avoir la liste des personnes presentes a un endroit, 
// on itere sur l'arbre map on recupere le nom de chaque personne 
// ainsi si une personne est localiser au meme lieu dans un intervalle
// de temps on l'insere dans la liste des personne presente dans ce lieu.
ArbreAVL<string> Historique::presences(const Intervalle& intervalle,
 const string& nomLieu) const {
  ArbreAVL<string> personnes;
  for( ArbreMap<string, ArbreAVL<Trace>>::Iterateur listeTraces = traces.debut(); 
    listeTraces != traces.fin(); ++listeTraces){
    ArbreAVL<string> lieux = localiser(intervalle,listeTraces.cle());
  if(lieux.contient(nomLieu)){
    personnes.inserer(listeTraces.cle());
  }
}
return personnes;
}

// Pour avoir les frequentations, on recupere les trace de la personne
// pour chaque trace on recupere la liste de personne presente dans un lieu au meme intervalle
// ainsi on itere sur l'arbre map si un personne est contenu dans celle liste on l'ajoute comme
// personne ayant frequente la personne passe en param.
ArbreAVL<string> Historique::frequentations(const Intervalle& intervalle,
  const string& nomPersonne) const {
  ArbreAVL<string> listeFrequentations;
  if(traces.contient(nomPersonne)){
    for(ArbreAVL<Trace>::Iterateur courant = traces[nomPersonne].debut(); courant ; courant++){
      ArbreAVL<string> listeContacts = presences(intervalle, (*courant).lieu);

      ArbreAVL<Trace>::Iterateur suivant = courant;
      ++suivant;

      struct Intervalle newIntervalle = intervalle;
      if(intervalle.debut < (*courant).date) newIntervalle.debut = (*courant).date;
      if(!(suivant == traces[nomPersonne].fin()) && (*suivant).date < intervalle.fin ) 
        newIntervalle.fin = (*suivant).date;

      if((*courant).lieu != "?" && listeContacts.contient(nomPersonne)){
        string lieu = (*courant).lieu;
        for( ArbreMap<string, ArbreAVL<Trace>>::Iterateur personne = traces.debut(); personne; ++personne){
          if(nomPersonne != personne.cle() && localiser(newIntervalle,personne.cle()).contient(lieu)){
            listeFrequentations.inserer(personne.cle());
          }
        }
      }
    }
  } 
  return listeFrequentations;
}


int Historique::duree_rencontres(const Intervalle& intervalle,
 const string& nomPersonne1,
 const string& nomPersonne2) const {
  int duree = 0;
  if(traces.contient(nomPersonne1) && traces.contient(nomPersonne2)){
    for(ArbreAVL<Trace>::Iterateur traceP1 = traces[nomPersonne1].debut(); traceP1 ; traceP1++){
      for(ArbreAVL<Trace>::Iterateur traceP2 = traces[nomPersonne2].debut(); traceP2; traceP2++){
        if((*traceP1).lieu == (*traceP2).lieu && intervalle.estValide((*traceP2).date)){
          duree += abs(((*traceP1).date.convertirSeconde() - (*traceP2).date.convertirSeconde()));
        }
      }
    }
  }  
  return duree;
}

