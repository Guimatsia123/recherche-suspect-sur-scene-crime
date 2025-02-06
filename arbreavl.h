/* Squelette pour classe générique ArbreAVL<T>.
 * Lab6 et Lab7 -- Arbres AVL
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * MARIUS GUIMATSIA AKALONG GUIM27309006
 * SENAYAH KOSSIWA SENK14299107
 */

#ifndef _ARBREAVL_H_
#define _ARBREAVL_H_

#include <cassert>
#include <iostream> 
#include <algorithm>
#include <set>
#include <iterator>
#include <bits/stdc++.h>
using namespace std;


// ------ Début bloc 1 inséré pour Lab7 ------
#include "pile.h"
// ------ Fin bloc 1 inséré pour Lab7 ------

template<class T>
class ArbreAVL {
public:
  ArbreAVL();
  ~ArbreAVL();

  // Lab6 / Tâche 2 - Fonctions de base
  bool vide() const;
  bool contient(const T&) const;
  void inserer(const T&);
  void vider();

  // Lab6 / Tâche 3
  void enlever(const T&);

  // Lab6 / Tâche 4
  ArbreAVL& operator=(const ArbreAVL&);
  ArbreAVL(const ArbreAVL&);

  // Fonctions pour certains tests ou diagnostique
  int compter() const;
  int hauteur() const;
  void afficher() const;

  // ------ Début bloc 2 inséré pour Lab7 ------

  // Annonce l'existence d'une classe Iterateur.
  // Nécessaire pour définir la classe Iterateur APRÈS la classe Noeud.
  class Iterateur;

  // Fonctions pour obtenir un itérateur (position dans l'arbre)
  Iterateur debut() const;
  Iterateur fin() const;
  Iterateur rechercher(const T&) const;
  Iterateur rechercherEgalOuSuivant(const T&) const;
  Iterateur rechercherEgalOuPrecedent(const T&) const;

  // Accès aux éléments de l'arbre via un intérateur.
  const T& operator[](const Iterateur&) const;

  // Retourne le i ième élément du parcours inordre de l'arbre.
  T& operator[](const Iterateur&);

  const T& operator[](int i) const;
  // Retourne un nouvel arbre AVL contenant les éléments inverses de l'arbre.
  // Ex.: si l'arbre contient 1, -2 et 3, le nouvel arbre doit contenir -1, 2 et -3.
  // On suppose que l'opérateur - est défini pour le type T.
  ArbreAVL<T> arbreInverse() const;  

  // ------ Fin bloc 2 inséré pour Lab7 ------

private:
  struct Noeud {
    Noeud(const T&);
    T contenu;
    int equilibre;
    Noeud *gauche, *droite;
    bool enleve;
  };
  Noeud* racine;

  // Fonctions internes
  bool inserer(Noeud*&, const T&);
  void rotationGaucheDroite(Noeud*&);
  void rotationDroiteGauche(Noeud*&);
  void vider(Noeud*&);

  // Lab6 / Tâche 4
  void copier(const Noeud*, Noeud*&) const;

  // Fonctions internes pour certains tests
  int hauteur(const Noeud*) const;
  int compter(const Noeud*) const;
  void inordre(Noeud* noeud, ArbreAVL<T>& arbre) const;
  void preparer_afficher(const Noeud* n, int profondeur, int& rang, T* elements,
   int* profondeurs) const;

  const T* trouver(const T& element, const Noeud* noeud) const;
  public:

  // Insere les elements de l'arbre dans un tableu  
  Noeud* inserer_elements(T*& elements, int debut, int fin) const;
  // Retourne un nouvel arbre AVL représentant la différence symétrique
  // entre l'arbre courant et l'arbre passé en paramètre.
  // La différence symétrique est l'ensemble des éléments qui sont
  // dans un des deux arbres, mais pas dans les deux.
  ArbreAVL<T> differenceSymetrique(const ArbreAVL<T>&) const;
  // Fait un parcourt inordre et mets les elements dans un tableau
  void parcourt_inordre(Noeud* noeud, T*& elements, int& index) const;

  // ------ Début bloc 3 inséré pour Lab7 ------
public:
  // Sera présenté à la semaine #7
  class Iterateur {
  public:
    Iterateur(const ArbreAVL& a);
    Iterateur(const Iterateur& a);
    Iterateur(const ArbreAVL& a, Noeud* c);


    operator bool() const;
    bool operator!() const;
    bool operator==(const Iterateur&) const;
    bool operator!=(const Iterateur&) const;

    const T& operator*() const;

    Iterateur& operator++();
    Iterateur operator++(int);
    Iterateur& operator=(const Iterateur&);



  private:
    const ArbreAVL& arbre_associe;
    Noeud* courant;
    Pile<Noeud*> chemin;

    friend class ArbreAVL;
  };
  // ------ Fin bloc 3 inséré pour Lab7 ------
};

//-----------------------------------------------------------------------------

template<class T>
ArbreAVL<T>::Noeud::Noeud(const T& c)
: contenu(c), equilibre(0), gauche(nullptr), droite(nullptr), enleve(false) {}

template<class T>
ArbreAVL<T>::ArbreAVL() : racine(nullptr) {}

template<class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre) : racine(nullptr) {
  copier(autre.racine, racine);
}

template<class T>
ArbreAVL<T>::~ArbreAVL() {
  vider(racine);
}

template<class T>
bool ArbreAVL<T>::contient(const T& element) const {
  if (racine == nullptr) return false;
  return trouver(element,racine);
}

template<class T>
const T* ArbreAVL<T>:: trouver(const T& element, const Noeud* noeud) const{
  if(noeud == nullptr) return nullptr;
  if(element < noeud->contenu) return trouver(element, noeud->gauche);
  if(noeud->contenu < element) return trouver(element, noeud->droite);

  if(noeud->enleve) return nullptr;

  return &(noeud->contenu);

}


template<class T>
void ArbreAVL<T>::inserer(const T& element) {
  inserer(racine, element);
}

template<class T>
bool ArbreAVL<T>::inserer(Noeud*& noeud, const T& element) {
  if (noeud == nullptr) {
    noeud = new Noeud(element);
    return true;
  }
  if (element < noeud->contenu) {
    if (inserer(noeud->gauche, element)) {
      noeud->equilibre++;
      if (noeud->equilibre == 0) return false;
      if (noeud->equilibre == 1) return true;
      assert(noeud->equilibre == 2);
      if (noeud->gauche->equilibre == -1) rotationDroiteGauche(noeud->gauche);
      rotationGaucheDroite(noeud);
    }
    return false;
  } else if (noeud->contenu < element) {
    // À compléter.
    if(inserer(noeud->droite, element)){
      noeud->equilibre--;
      if(noeud->equilibre == 0) return false;
      if(noeud->equilibre == -1) return true;
      assert(noeud->equilibre == -2 );
      if(noeud->droite->equilibre == 1)
        rotationGaucheDroite(noeud->droite);
      rotationDroiteGauche(noeud);
    }
    return false;
  }

  // element == noeud->contenu
  noeud->contenu = element;  // Mise à jour
  noeud->enleve = false;
  return false;
}

template<class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud*& racinesousarbre) {
  Noeud* temp = racinesousarbre->gauche;
  int ea = temp->equilibre;
  int eb = racinesousarbre->equilibre;
  int neb = -(ea > 0 ? ea : 0) - 1 + eb;
  int nea = ea + (neb < 0 ? neb : 0) - 1;

  temp->equilibre = nea;
  racinesousarbre->equilibre = neb;
  racinesousarbre->gauche = temp->droite;
  temp->droite = racinesousarbre;
  racinesousarbre = temp;
}

template<class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud*& racinesousarbre) {
  // À compléter.
  // Les démonstrateurs peuvent fournir la formule à mettre ici.
  Noeud* temp = racinesousarbre->droite;
  const int eb = temp->equilibre;
  const int ea = racinesousarbre->equilibre;
  const int nea = -(eb<0? eb : 0) + 1 + ea ;
  const int neb = (nea > 0 ? nea : 0) + 1 + eb;

  temp->equilibre =neb;
  racinesousarbre->equilibre = nea;
  racinesousarbre->droite = temp->gauche;
  temp->gauche = racinesousarbre;
  racinesousarbre = temp;
}

template<class T>
bool ArbreAVL<T>::vide() const {
  // À compléter : doit retourner vrai si et seulement si l'arbre est vide.
  return racine == nullptr;
}

template<class T>
void ArbreAVL<T>::vider() {
  vider(racine);
  racine = nullptr;
}

template<class T>
void ArbreAVL<T>::vider(Noeud*& noeud) {
  if(noeud == nullptr) return;
  vider(noeud->gauche);
  vider(noeud->droite);
  delete noeud;
}

template<class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const {
  if (source == noeud) return;

  noeud = new Noeud(source->contenu);
  noeud->enleve = source->enleve;
  noeud->equilibre = source->equilibre;

  if (source->gauche != nullptr)
    copier(source->gauche, noeud->gauche);
  if (source->droite != nullptr)
    copier(source->droite, noeud->droite);
}

template<class T>
int ArbreAVL<T>::hauteur() const {
  return hauteur(racine);
}

template<class T>
int ArbreAVL<T>::compter() const {
  return compter(racine);
}

template<class T>
int ArbreAVL<T>::hauteur(const Noeud* n) const {
  if (n == nullptr) return -1;
  return 1 + std::max(hauteur(n->gauche), hauteur(n->droite));
}

template<class T>
int ArbreAVL<T>::compter(const Noeud* n) const {
  if (n == nullptr) return 0;
  return compter(n->gauche) + compter(n->droite) + !n->enleve;
}

template<class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
  if (this == &autre) return *this;
  vider();
  copier(autre.racine, racine);
  return *this;
}

// ------ Optionnel Lab 6 -----
template<class T>
void ArbreAVL<T>::enlever(const T& element) {
  Noeud* current = racine;

  while(current != nullptr){
    if (element == current->contenu){
      current->enleve = true;
      return;
    } else if (current->contenu < element) {
      current = current->droite;
    } else {
    //if (element < current->contenu)
      current = current->gauche;
    }
  }
}

//-----------------------------

// Code fourni pour afficher l'arbre.
// L'opérateur ostream& << const T&  doit être défini.
#include <iostream>
template<class T>
void ArbreAVL<T>::afficher() const {
  std::cout << "Contenu de l'arbre AVL (";
  int n = compter();
  std::cout << n << " noeuds) :\n";

  T* elements = new T[n];
  int* profondeurs = new int[n];
  n = 0;
  preparer_afficher(racine, 0, n, elements, profondeurs);
  for (int p = 0;; p++) {
    bool derniereprofondeur = true;
    for (int i = 0; i < n; i++) {
      if (profondeurs[i] == p) {
        std::cout << elements[i];
        derniereprofondeur = false;
      }
      std::cout << '\t';
    }
    std::cout << '\n';
    if (derniereprofondeur) break;
  }

  delete[] elements;
  delete[] profondeurs;
  std::cout << "--------------" << std::endl;
}

template<class T>
void ArbreAVL<T>::preparer_afficher(const Noeud* n, int profondeur, int& rang,
  T* elements, int* profondeurs) const {
  if (n == nullptr) return;
  preparer_afficher(n->gauche, profondeur + 1, rang, elements, profondeurs);
  elements[rang] = n->contenu;
  profondeurs[rang] = profondeur;
  rang++;
  preparer_afficher(n->droite, profondeur + 1, rang, elements, profondeurs);
}

// ------ Début bloc 4 inséré pour Lab7 ------
template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const {
  Iterateur iter(*this);
  // À compléter.
  if(racine != nullptr){
    Noeud* currentCandidate = racine;
    while(currentCandidate->gauche != nullptr){
      iter.chemin.empiler(currentCandidate);
      currentCandidate = currentCandidate->gauche;

    }
    iter.courant = currentCandidate;
  }
  return iter;
}

template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const {
  return Iterateur(*this);
}

template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T& e) const {
  Iterateur iter(*this);
  // À compléter.
  Noeud* currentCandidate = racine;
  Pile<Noeud*> chemin;

  while(currentCandidate != nullptr){
    if (e < currentCandidate->contenu){
      chemin.empiler(currentCandidate);
      currentCandidate = currentCandidate ->gauche;

    }else if(currentCandidate->contenu < e){
      currentCandidate = currentCandidate->droite;
    }
    else{
      break;
    }

  }


  if(currentCandidate != nullptr){
    iter.courant = currentCandidate;
    iter.chemin = chemin;
  }

  return iter;
}
template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(
  const T& e) const {

  Noeud* n = racine, *dernier = nullptr;
  while(n){
    if(e < n->contenu){
      dernier = n;
      n = n->gauche;
    }else if(n->contenu < e){
      n = n->droite;
    }else{
      return rechercher(e);
    }

  }
  if(dernier != nullptr)
    return rechercher(dernier->contenu);


  return Iterateur(*this);
}

template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(
  const T& e) const {
  // À compléter.
  Noeud* n = racine, *dernier = nullptr;
  while(n){
    if(e < n->contenu){
      n = n->gauche;
    }else if(n->contenu < e){
      dernier = n;
      n = n->droite;
    }else{
      return rechercher(e);
    }

  }
  if(dernier != nullptr)
    return rechercher(dernier->contenu);


  return Iterateur(*this);
}

template<class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const {
  assert(&iterateur.arbre_associe == this);
  assert(iterateur.courant);
  return iterateur.courant->contenu;
}

template<class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur) {
  assert(&iterateur.arbre_associe == this);
  assert(iterateur.courant);
  return iterateur.courant->contenu;
}

template<class T>
const T& ArbreAVL<T>::operator[](int i) const{
  int rang = 0;
  ArbreAVL<T>::Iterateur it = debut() ;

  if(i == 0) return it.courant->contenu;
  do{
    ++rang;
    ++it;

  }while(it && i != rang);

  return it.courant->contenu;

}

template<class T>
 ArbreAVL<T> ArbreAVL<T>::arbreInverse() const{
 ArbreAVL<T> arbre;
 int taille = compter();
 T *elements = new T[taille];
 int index = 0;
 parcourt_inordre(racine,elements, index);
 arbre.racine = inserer_elements(elements, 0, taille-1);
 delete[] elements;//free memory
 return arbre;
}



template<class T>
void ArbreAVL<T>::parcourt_inordre(Noeud* noeud, T*& elements, int& index) const{
  if(noeud){
    parcourt_inordre(noeud->gauche, elements, index);
    elements[index++] = noeud->contenu;
    parcourt_inordre(noeud->droite, elements, index);
  }

}

template<class T>
  typename ArbreAVL<T>::Noeud* ArbreAVL<T>::inserer_elements(T*& elements, int debut, int fin) const {
  if(fin < debut ) return nullptr;
  
  int milieu = (debut + fin)/2;

  Noeud* nouveauNoeud =  new Noeud(-elements[milieu]);
  nouveauNoeud->droite = inserer_elements(elements, debut, milieu - 1);
  nouveauNoeud->gauche = inserer_elements(elements, milieu + 1, fin);

  return nouveauNoeud;
}




template<class T>
 ArbreAVL<T> ArbreAVL<T>::differenceSymetrique(const ArbreAVL<T>& arbre) const{
  ArbreAVL<T> nouvelArbre;
  
  for(ArbreAVL<T>::Iterateur i2 = debut();i2;++i2){
    if(!arbre.contient(*i2))
      nouvelArbre.inserer(*i2);
  }
  for(ArbreAVL<T>::Iterateur i1 = arbre.debut();i1;++i1){
    if(!contient(*i1))
      nouvelArbre.inserer(*i1);
  }

 return nouvelArbre;
}



//-----------------------
template<class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL& a)
: arbre_associe(a), courant(nullptr) {}

template<class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur& a)
: arbre_associe(a.arbre_associe) {
  courant = a.courant;
  chemin = a.chemin;
}

// Pré-incrément
template<class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++() {
  // À compléter.ou
  if(*this == arbre_associe.fin())
    return *this;

  if(courant->droite != nullptr){
    Noeud* currentCandidate = courant->droite;
    while(currentCandidate->gauche != nullptr){
      chemin.empiler(currentCandidate);
      currentCandidate = currentCandidate->gauche;


    }
    courant = currentCandidate;

  }else if(!chemin.vide()){
    courant = chemin.depiler();

  }else{
    courant = nullptr;
  }
  return *this;
}

// Post-incrément
template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int) {
  Iterateur copie(*this);
  operator++();
  return copie;
}

template<class T>
ArbreAVL<T>::Iterateur::operator bool() const {
  return courant != nullptr;
}

template<class T>
bool ArbreAVL<T>::Iterateur::operator!() const {
  return courant == nullptr;
}

template<class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur& o) const {
  assert(&arbre_associe == &o.arbre_associe);
  return courant == o.courant;
}

template<class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const {
  assert(&arbre_associe == &o.arbre_associe);
  return courant != o.courant;
}

template<class T>
const T& ArbreAVL<T>::Iterateur::operator*() const {
  assert(courant != nullptr);
  return courant->contenu;
}

template<class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator=(
  const Iterateur& autre) {
  assert(&arbre_associe == &autre.arbre_associe);
  courant = autre.courant;
  chemin = autre.chemin;
  return *this;
}
// ------ Fin bloc 4 inséré pour Lab7 ------

#endif
