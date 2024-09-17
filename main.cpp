#include "headers/commons.hpp"

#include "headers/Utils.hpp"
#include "headers/FileInteractions.hpp"

#include <algorithm>
#include <cmath>

using namespace std;

using namespace Dijkstra;
using namespace Utils;
using namespace Fichiers;

const double PosInf = +INFINITY;

vector<Sommet> SOMMETS_OG = {};
vector<Lien> LIENS_OG = {};

dict<int64_t, Sommet*> CORRESPONDANCE;

Sommet SOMMET_NULL((s_id_t)-1, "null", PosInf, PosInf, PosInf);

void PreInit(string basename) {

	string sommets_file = basename + "_s.tsv";
	string liens_file = basename + "_l.tsv";

	LoadVerticesFromCSV(sommets_file, &SOMMETS_OG);
	LoadLinksFromCSV(liens_file, &LIENS_OG);

	size_t TotalVertices = SOMMETS_OG.size();
	size_t TotalLinks = LIENS_OG.size();

	for (size_t i=0; i < TotalVertices; i++) {
		Sommet* s = &SOMMETS_OG.at(i);

		pair<s_id_t, Sommet*> to_insert = {s->id, s};

		CORRESPONDANCE.insert(to_insert);
	}

	for (size_t i=0; i < TotalLinks; i++) {
		Lien l = LIENS_OG.at(i);

		if (l.type != ERR) {

			s_id_t idA = l.idA;
			s_id_t idB = l.idB;

			if (CORRESPONDANCE.contains(idA) && CORRESPONDANCE.contains(idB)) {

				Sommet* sA = CORRESPONDANCE.at(idA);
				Sommet* sB = CORRESPONDANCE.at(idB);

				bool inA = count(sA->neighbours.begin(), sA->neighbours.end(), idB) == 0 ? false: true;
				bool inB = count(sB->neighbours.begin(), sB->neighbours.end(), idA) == 0 ? false: true;

				if (!inA) {
					sA->neighbours.push_back(idB);
				}

				if ((!inB) && (l.type == LIEN_BI)) {
					sB->neighbours.push_back(idA);
				}
			}
		}
	}

	return;
}

double Poids(Sommet s1, Sommet s2) {
	double poids = sqrt(pow(s2.x - s1.x, 2) + pow(s2.y - s1.y, 2) + pow(s2.z - s1.z, 2));

	return poids;
}

vector<Sommet*> Voisins(Sommet s, vector<Sommet*> SOMMETS, vector<Lien>* LIENS) {
	size_t n_liens = LIENS->size();

	vector<Sommet*> voisins;

	for (size_t i=0; i < n_liens; i++) {
		Lien l = LIENS->at(i);

		if ((s.id == l.idA) && (l.type != ERR)) {
			Sommet* s2 = CORRESPONDANCE.at(l.idB);
			bool contains = count(SOMMETS.begin(), SOMMETS.end(), *s2) == 0 ? false: true;

			if (contains) {
				voisins.push_back(s2);
			}

		} else if ((l.type == LIEN_BI) && (s.id == l.idB)) {
			Sommet* s2 = CORRESPONDANCE.at(l.idA);
			bool contains = count(SOMMETS.begin(), SOMMETS.end(), *s2) == 0 ? false: true;

			if (contains) {
				voisins.push_back(s2);
			}
		}
	}

	return voisins;
}

dict<Sommet*, double> Initialisation(vector<Sommet*> SOMMETS, Sommet* s_dep_ptr) {
	Sommet s_dep = *s_dep_ptr;

	dict<Sommet*, double> d = {};

	for (size_t i=0; i < SOMMETS.size(); i++) {
		Sommet* s = SOMMETS.at(i);

		if (*s != s_dep) {
			d[s] = PosInf;
		} else {
			d[s] = (double)0.0;
		}
	}

	return d;
}

int main() {
	string basename = "France";

	s_id_t idA, idB;

	PreInit(basename);

	return 0;
}
