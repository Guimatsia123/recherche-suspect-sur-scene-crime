/*
  Valideur pour INF3105 / 2020A / TP2
*/

#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

string enleverEspaces(const string& chaine) {
  string resultat = chaine;
  int j = 0;
  for (size_t i = 0; i < chaine.size(); i++) {
    if (chaine[i] != ' ' && chaine[i] != '\t') resultat[j++] = chaine[i];
  }
  resultat[j++] = 0;
  return resultat;
}

int main(int argc, const char* argv[]) {
  string nomfichier_test, nomfichier_resultat1, nomfichier_resultat2;
  bool silence = false;
  bool corrige = false;

  for (int i = 1, j = 0; i < argc; i++) {
    if (strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "-quiet") == 0 || strcmp(argv[i], "-silence") == 0)
      silence = true;
    else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-corrige") == 0)
      corrige = true;
    else
      switch (j++) {
        case 0:
          nomfichier_test = argv[i];
          break;
        case 1:
          nomfichier_resultat1 = argv[i];
          break;
        case 2:
          nomfichier_resultat2 = argv[i];
          break;
      }
  }
  if (nomfichier_resultat2 == "") {
    cerr << "Valideur pour INF3105/2024E/TP4\n";
    cerr << "Syntaxe : valideur text.txt solution.resultat votre.resultat"
         << endl;
    return 1;
  }

  ifstream ifs_test(nomfichier_test.c_str());
  ifstream ifs_solution(nomfichier_resultat1.c_str());
  ifstream ifs_resultat(nomfichier_resultat2.c_str());

  if (ifs_test.fail()) {
    cerr << "Erreur ouverture " << nomfichier_test << endl;
    return 1;
  }
  if (ifs_solution.fail()) {
    cerr << "Erreur ouverture " << nomfichier_resultat1 << endl;
    return 1;
  }
  if (ifs_resultat.fail()) {
    cerr << "Erreur ouverture " << nomfichier_resultat2 << endl;
    return 1;
  }

  map<string, int> nbtests;
  map<string, int> nbreussi;

  int ligne = 0;
  while (ifs_test) {
    ligne++;
    string lignetest, lignesolution, ligneresultat = "(X)";

    getline(ifs_test, lignetest);
    getline(ifs_solution, lignesolution);
    getline(ifs_resultat, ligneresultat);

    stringstream ss(lignetest);
    string commande;
    ss >> commande;

    if (commande.empty()) break;

    if (enleverEspaces(lignesolution) == enleverEspaces(ligneresultat))
      nbreussi[commande]++;
    else if (!silence) {
      cerr << "Ligne #" << ligne << " (" << commande << ") : ÉCHEC\n"
           << " V1:" << lignesolution << "\n"
           << " V2:" << ligneresultat << endl;
    }

    nbtests[commande]++;
  }

  cout << nbreussi["trace"];
  if (!corrige) cout << '/' << nbtests["trace"];
  cout << '\t' << nbreussi["localiser"];
  if (!corrige) cout << '/' << nbtests["localiser"];
  cout << '\t' << nbreussi["presences"];
  if (!corrige) cout << '/' << nbtests["presences"];
  cout << '\t' << nbreussi["frequentations"];
  if (!corrige) cout << '/' << nbtests["frequentations"];
  cout << '\t' << nbreussi["duree_rencontres"];
  if (!corrige) cout << '/' << nbtests["duree_rencontres"];
  cout << endl;

  return 0;
}
