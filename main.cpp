#include "headers/commons.hpp"

#include "headers/Utils.hpp"
#include "headers/FileInteractions.hpp"

#include <algorithm>
#include <chrono>
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
			bool contains = count(SOMMETS.begin(), SOMMETS.end(), s2) == 0 ? false: true;

			if (contains) {
				voisins.push_back(s2);
			}

		} else if ((l.type == LIEN_BI) && (s.id == l.idB)) {
			Sommet* s2 = CORRESPONDANCE.at(l.idA);
			bool contains = count(SOMMETS.begin(), SOMMETS.end(), s2) == 0 ? false: true;

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

Sommet* Trouve_min(vector<Sommet*> SOMMETS, dict<Sommet*, double> d) {
	double mini = PosInf;
	Sommet* sommet = &SOMMET_NULL;

	for (size_t i=0; i<SOMMETS.size(); i++) {
		Sommet* s = SOMMETS.at(i);
		if (d[s] < mini) {
			mini = d[s];
			sommet = s;
		}
	}

	return sommet;
}

tuple<dict<Sommet*, double>, dict<Sommet*, Sommet*>> maj_distances(Sommet* s1, Sommet* s2, dict<Sommet*, double> d, dict<Sommet*, Sommet*> predecesseur) {
	if (d[s2] > (d[s1] + Poids(*s1, *s2))) {
		d[s2] = d[s1] + Poids(*s1, *s2);
		predecesseur[s2] = s1;
	}

	return make_tuple(d, predecesseur);
}

tuple<dict<Sommet*, double>, dict<Sommet*, Sommet*>> Algo(vector<Lien>* LIENS, vector<Sommet*> SOMMETS, Sommet s_dep) {
	dict<Sommet*, double> d = Initialisation(SOMMETS, &s_dep);
	dict<Sommet*, Sommet*> predecesseur = {};

	vector<Sommet*> SOMMETS_WORK = {};
	for (size_t i=0; i < SOMMETS.size(); i++) {
		Sommet* s = SOMMETS.at(i);
		SOMMETS_WORK.push_back(s);
	}

	tuple<dict<Sommet*, double>, dict<Sommet*, Sommet*>> Tuple_dP;

	while (SOMMETS_WORK.size() > 0) {
		Sommet* s1 = Trouve_min(SOMMETS_WORK, d);

		bool contains_s1 = (count(SOMMETS_WORK.begin(), SOMMETS_WORK.end(), s1) > 0);
		size_t s1_index = (size_t)NULL;

		if (s1 == &SOMMET_NULL) {
			break;
		}
		if (contains_s1) {
			for (size_t i=0; i < SOMMETS_WORK.size(); i++) {
				if (SOMMETS_WORK.at(i) == s1) {
					s1_index = i;
					break;
				}
			}

			SOMMETS_WORK.erase(SOMMETS_WORK.begin()+s1_index);
		}

		vector<Sommet*> voisins = Voisins(*s1, SOMMETS_WORK, LIENS);

		for (size_t i=0; i < voisins.size(); i++) {
			Sommet* s2 = voisins.at(i);
			Tuple_dP = maj_distances(s1, s2, d, predecesseur);
			d = get<0>(Tuple_dP);
			predecesseur = get<1>(Tuple_dP);
		}
	}

	return make_tuple(d, predecesseur);
}

tuple<vector<s_id_t>, double> trouver_chemin(Sommet s_dep, Sommet s_fin, dict<s_id_t, s_id_t> predecesseurs_id, dict<Sommet*, double> d) {
	s_id_t s_id = s_fin.id;
	s_id_t dep_id = s_dep.id;

	vector<s_id_t> A = {};

	while (s_id != dep_id) {
		A.push_back(s_id);
		s_id = predecesseurs_id[s_id];
	}

	A.push_back(dep_id);
	ranges::reverse(A);

	return make_tuple(A, d[CORRESPONDANCE[s_fin.id]]);
}

int main() {
	string basename = "";

	s_id_t idA, idB;

	//PreInit(basename);

	printf("Name of your files : ");
	cin >> basename;

	if (basename.size() > 0) {
		PreInit(basename);

		vector<Sommet*> SOMMETS = {};
		string dep_name, fin_name;

		printf("Starting point : ");
		cin >> dep_name;
		printf("End point : ");
		cin >> fin_name;

		if ((dep_name.size() > 0) && (fin_name.size() > 0) && (dep_name != fin_name)) {
			for (size_t i=0; i<SOMMETS_OG.size(); i++) {
				Sommet* s_ptr = &SOMMETS_OG.at(i);
				Sommet s = *s_ptr;

				SOMMETS.push_back(s_ptr);

				if (s.name == dep_name) {
					idA = s.id;
				} else if (s.name == fin_name) {
					idB = s.id;
				}
			}

			Sommet s_dep = *CORRESPONDANCE[idA];
			Sommet s_fin = *CORRESPONDANCE[idB];

			auto start = chrono::high_resolution_clock::now();

			tuple<dict<Sommet*, double>, dict<Sommet*, Sommet*>> AlgoOutput = Algo(&LIENS_OG, SOMMETS, s_dep);

			auto finish = chrono::high_resolution_clock::now();

			int64_t generation_time = chrono::duration_cast<chrono::nanoseconds>(finish-start).count();

			dict<Sommet*, double> d = get<0>(AlgoOutput);
			dict<Sommet*, Sommet*> predecesseurs = get<1>(AlgoOutput);

			/*// Utile pour le debug

			for (auto kvp = d.begin(); kvp != d.end(); kvp++) {
				Sommet s = *kvp->first;
				printf("\"%s\" : %lf\n", s.name.c_str(), kvp->second);
			}*/

			dict<s_id_t, s_id_t> predecesseurs_id = {};

			for (auto kvp = predecesseurs.begin(); kvp != predecesseurs.end(); ++kvp) {
				Sommet* k = kvp->first;
				Sommet* v = kvp->second;
				predecesseurs_id[k->id] = v->id;
			}

			tuple<vector<s_id_t>, double> TupleChemin = trouver_chemin(s_dep, s_fin, predecesseurs_id, d);
			vector<s_id_t> Chemin = get<0>(TupleChemin);
			double DistanceChemin = get<1>(TupleChemin);

			string output = "";

			if (DistanceChemin != PosInf) {
				for (size_t i=0; i<Chemin.size(); i++) {
					string s_name = CORRESPONDANCE[Chemin.at(i)]->name;

					output += s_name;

					if (i != (Chemin.size()-1)) {
						output += " -> ";
					}
				}

				printf("Path to go from %s to %s (%lf) :\n%s\nPath found in %lf seconds!\n", dep_name.c_str(), fin_name.c_str(), DistanceChemin, output.c_str(), (double)(generation_time)/1e9);
			} else {
				printf("Error : There is no path between those two points\n");
			}
		}
	}

	return 0;
}
