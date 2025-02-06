/* TP4 - Recherche de suspects
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 */

#include <sstream>
#include <vector>  // Vous ne *pouvez pas* utiliser vector dans vos
                   // fichiers. Il est utilisé seulement dans les tests ici.

#include "dateheure.h"

using namespace std;

int main() {
  cout << "Tests pour la classe DateHeure ..." << endl;

  stringstream ss(
      "0j_00h00m00s 0j_00h00m01s 0j_00h00m10s 0j_00h01m00s 0j_00h01m02s "
      "0j_00h01m05s 0j_00h02m00s 0j_00h02m03s 0j_00h02m06s 0j_00h03m00s "
      "0j_00h03m10s 0j_00h40m00s 0j_01h00m00s 0j_01h00m01s 0j_01h01m00s "
      "0j_01h02m00s 0j_02h00m00s 0j_02h10m00s 0j_02h12m01s 1j_00h00m00s "
      "1j_00h00m02s 1j_01h01m00s 2j_00h00m00s");

  vector<DateHeure> dates;
  // Recommandation : testez aussi ArbreAVL<DateHeure>
  // ArbreAVL<DateHeure> arbre;

  DateHeure d;
  while (ss >> d >> ws) {
    cout << d << endl;
    dates.push_back(d);
    // arbre.inserer(d);
  }

  // Test du comparateur
  for (size_t i = 0; i < dates.size(); i++)
    for (size_t j = 0; j < dates.size(); j++) {
      if (i < j) {
        if (!(dates[i] < dates[j]))
          cout << "Erreur : dates[" << i << "]<dates[" << j
               << "] : " << dates[i] << "<" << dates[j] << " retourne faux!\n";
      } else if (j < i) {
        if (!(dates[j] < dates[i]))
          cout << "Erreur : dates[" << j << "]<dates[" << i
               << "] : " << dates[j] << "<" << dates[i] << " retourne faux!\n";
      } else {  // i == j
        if (dates[j] < dates[i])
          cout << "Erreur : dates[" << j << "]<dates[" << i
               << "] : " << dates[j] << "<" << dates[i] << " retourne faux!\n";
      }
    }

  cout << " --- FIN ---" << endl;
  return EXIT_SUCCESS;
}
