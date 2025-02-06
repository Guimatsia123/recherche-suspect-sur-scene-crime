/* TP4 - Recherche de suspects
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * MARIUS GUIMATSIA AKALONG GUIM27309006
 * SENAYAH KOSSIWA SENK14299107
 */
#include "dateheure.h"
#include <assert.h>
#include <cstdio>
#include <iomanip>

DateHeure::DateHeure(): jour(0), heure(0), minute(0), seconde(0) {} 

bool DateHeure::operator<(const DateHeure& d) const {
  // À compléter : comparer *this (l'objet courant) avec d.
  if(jour != d.jour) return jour < d.jour;
  if(heure != d.heure) return heure < d.heure;
  if(minute != d.minute) return minute < d.minute;
  if(seconde != d.seconde) return seconde < d.seconde;
  return false;
}

bool DateHeure::operator==(const DateHeure& d) const{
  return jour == d.jour && heure == d.heure 
  && minute == d.minute && seconde == d.seconde;
}

bool DateHeure::operator<=(const DateHeure& d) const {
  // À compléter : comparer *this (l'objet courant) avec d.
  return *this < d || *this == d;
}

 int  DateHeure::convertirSeconde() const{
  return jour*24*360 + heure*360 + minute*60 + seconde;
 }

std::ostream& operator<<(std::ostream& os, const DateHeure& d) {
  int jours, heures, minutes, secondes;
  // À compléter : transférer la date d dans les champs.
  jours = d.jour;
  heures = d.heure;
  minutes = d.minute;
  secondes = d.seconde;
  char chaine[40];
  sprintf(chaine, "%dj_%02dh%02dm%02ds", jours, heures, minutes, secondes);
  os << chaine;
  return os;
}

std::istream& operator>>(std::istream& is, DateHeure& d) {
  int jours, heures, minutes, secondes;
  char j, m, h, s, underscore;
  is >> jours >> j >> underscore
     >> heures >> h >> minutes >> m >> secondes >> s;

  assert(j == 'j');
  assert(underscore == '_');
  assert(h == 'h' && m == 'm' && s == 's');

  // À compléter : utiliser les variable jours,heures,minutes,secondes pour
  // modifier l'objet d.
  d.jour = jours;
  d.heure = heures;
  d.minute = minutes;
  d.seconde = secondes;

  return is;
}

std::ostream& operator<<(std::ostream& os, const Intervalle& i) {
  os << i.debut << i.fin;
  return os;
}

std::istream& operator>>(std::istream& is, Intervalle& i) {
  char crochetgauche, crochetdroit, virgule;
  is >> crochetgauche >> i.debut >> virgule >> i.fin >> crochetdroit;
  assert(crochetgauche == '[' && virgule == ',' && crochetdroit == ']');
  return is;
}
