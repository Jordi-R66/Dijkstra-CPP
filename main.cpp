#include "headers/commons.hpp"

#include "headers/Utils.hpp"
#include "headers/FileInteractions.hpp"

#include <math.h>

using namespace std;

using namespace Dijkstra;
using namespace Utils;
using namespace Fichiers;

vector<Sommet> SOMMETS_OG = {};
vector<Lien> LIENS_OG = {};

dict<int64_t, Sommet> CORRESPONDANCE;

Sommet SOMMET_NULL(-1, "null", HUGE_VAL, HUGE_VAL, HUGE_VAL);

void PreInit() {
	return;
}

double Poids(Sommet s1, Sommet s2) {
	double poids = sqrt(pow(s2.x - s1.x, 2) + pow(s2.y - s1.y, 2) + pow(s2.z - s1.z, 2));

	return poids;
}

int main() {
	string basename = "France";

	string sommets_file = basename + "_s.csv";
	string liens_file = basename + "_l.csv";

	LoadVerticesFromCSV(sommets_file, &SOMMETS_OG);
	size_t TotalVertices = SOMMETS_OG.size();

	for (size_t i=0; i<TotalVertices; i++) {
		SOMMETS_OG.at(i).PrintString();
	}

	return 0;
}
