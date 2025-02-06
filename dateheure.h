/* TP4 - Recherche de suspects
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * MARIUS GUIMATSIA AKALONG GUIM27309006
 * SENAYAH KOSSIWA SENK14299107
 */
#ifndef DATEHEURE_H
#define DATEHEURE_H
#include <iostream>

class DateHeure {
 public:
  DateHeure();

  bool operator<(const DateHeure& date) const;
  bool operator<=(const DateHeure& date) const;
  bool operator==(const DateHeure& d) const;
  int convertirSeconde() const;

 private:
  // À compléter.
  int jour;
  int heure;
  int minute;
  int seconde;

  friend std::ostream& operator<<(std::ostream&, const DateHeure& date);
  friend std::istream& operator>>(std::istream&, DateHeure& date);
};

struct Intervalle {
  DateHeure debut, fin;
  bool estValide(const DateHeure& date) const{
     return (debut <= date) && (date < fin);
  }

  friend std::istream& operator>>(std::istream& is, Intervalle& itervale);
  friend std::ostream& operator<<(std::ostream& os, const Intervalle& itervale);
};

#endif

