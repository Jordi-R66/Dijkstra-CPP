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

double Poids(Utils::Sommet s1, Utils::Sommet s2) {
	double poids = sqrt(pow(s2.x - s1.x, 2) + pow(s2.y - s1.y, 2) + pow(s2.z - s1.z, 2));

	return poids;
}


int main() {
	// Utils::Sommet s(0ULL, "Hullo", 0.0, 0.0, 0.0);

	SOMMET_NULL.PrintString();
	return 0;
}
