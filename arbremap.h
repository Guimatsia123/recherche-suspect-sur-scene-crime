/* Squelette pour classe générique ArbreMap<K, V>.
 * Lab8 -- Dictionnaires et Arbres binaires de recherche
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * MARIUS GUIMATSIA AKALONG GUIM27309006
 * SENAYAH KOSSIWA SENK14299107
 */

#ifndef _ARBREMAP_H_
#define _ARBREMAP_H_

#include "arbreavl.h"

template<class K, class V>
class ArbreMap {
public:

  bool contient(const K&) const;

  void enlever(const K&);
  void vider();
  bool vide() const;

  const V& operator[](const K&) const;
  V& operator[](const K&);


private:
  // À compléter : voir la Section 8.11 (Arbres associatifs (Mapping Trees)) des notes de cours.
  struct Entree {
    Entree(const K& c) : cle(c), valeur() {}
    K cle;
    V valeur;
    bool operator < (const Entree& e) const { return cle < e.cle; }
  };

  ArbreAVL<Entree> entrees;

  // partie 2
public:
  class Iterateur {
  public:
    Iterateur(const ArbreMap& a) : iter(a.entrees.debut()) {}
    Iterateur(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {}
    operator bool() const;
    bool operator!() const;

    Iterateur& operator++();
    Iterateur operator++(int);

    const K& cle() const;
    const V& valeur() const; // constant ou non ?

  private:
    typename ArbreAVL<Entree>::Iterateur iter;
  };

  Iterateur debut() const;
  Iterateur fin() const;
  Iterateur rechercher(const K& cle) const;
  Iterateur rechercherEgalOuSuivant(const K& cle) const;
  Iterateur rechercherEgalOuPrecedent(const K& cle) const;
  const V& operator[](const ArbreMap<K, V>::Iterateur& iter) const;
  V& operator[](const ArbreMap<K, V>::Iterateur& iter);


};


template<class K, class V>
ArbreMap<K, V>::Iterateur::operator bool() const{
  return iter;
}

template<class K, class V>
bool ArbreMap<K, V>::Iterateur::operator!() const{
  return !iter;
}

template<class K, class V>
typename ArbreMap<K, V>::Iterateur& ArbreMap<K, V>::Iterateur::operator++() {
  ++iter;
  return *this;
}

//post-increment
template<class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::Iterateur::operator++(int) {
  ArbreMap<K, V>::Iterateur copie(iter);
  ++iter;
  return copie;
}


template<class K, class V>
void ArbreMap<K, V>::vider() {
  entrees.vider();
}

template<class K, class V>
bool ArbreMap<K, V>::vide() const {
  return entrees.vide();
}

template<class K, class V>
void ArbreMap<K, V>::enlever(const K& c) {
  entrees.enlever(Entree(c));
}

template<class K, class V>
bool ArbreMap<K, V>::contient(const K& c) const {
  return entrees.contient(Entree(c));
}

template<class K, class V>
const V& ArbreMap<K, V>::operator[](const K& c) const {
  typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(c);
  return entrees[iter].valeur;

}

template<class K, class V>
V& ArbreMap<K, V>::operator[](const K& c) {

  typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(c);

  if(!iter) {
// Choix d’implémentation : si l’élément n’existe pas, on le crée
    entrees.inserer(Entree(c));
    iter = entrees.rechercher(c);
// Choix alternatif : création explicite (Ex: TreeMap.put() en Java).
  }
  return entrees[iter].valeur;

}


template<class K, class V>
const V& ArbreMap<K, V>::operator[](const ArbreMap<K, V>::Iterateur& iter) const{
  return entrees[iter.iter].valeur;
}

template<class K, class V>
V& ArbreMap<K, V>::operator[](const ArbreMap<K, V>::Iterateur& iter){
  return entrees[iter.iter].valeur;
}

template<class K, class V>
const K& ArbreMap<K, V>::Iterateur::cle()const{
  return (*iter).cle;
}

template<class K, class V>
const V& ArbreMap<K, V>::Iterateur::valeur()const{
  return (*iter).valeur;
}

template<class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::debut()const{
  return ArbreMap<K, V>::Iterateur(*this);
}

template<class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::fin()const{
  return ArbreMap<K, V>::Iterateur(entrees.fin());
}

template<class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::rechercher(const K& cle)const{
  return ArbreMap<K, V>::Iterateur(entrees.rechercher(cle));
}

template<class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::rechercherEgalOuSuivant(const K& cle)const{
  return ArbreMap<K, V>::Iterateur(entrees.rechercherEgalOuSuivant(cle));
}

template<class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::rechercherEgalOuPrecedent(const K& cle)const{
  return ArbreMap<K, V>::Iterateur(entrees.rechercherEgalOuPrecedent(cle));
}

#endif


