#include "headers/commons.hpp"

#include "headers/Utils.hpp"
#include "headers/FileInteractions.hpp"

#include <math.h>

using namespace std;
using namespace Dijkstra;
using namespace Fichiers;

vector<Utils::Sommet> SOMMETS_OG = {};
vector<Utils::Lien> LIENS_OG = {};

dict<int64_t, Utils::Sommet> CORRESPONDANCE;

Utils::Sommet SOMMET_NULL(-1, "null", HUGE_VAL, HUGE_VAL, HUGE_VAL);

void PreInit() {
	return;
}

double Poids(Utils::Sommet s) {return 0.0;}

int main() {
	// Utils::Sommet s(0ULL, "Hullo", 0.0, 0.0, 0.0);

	SOMMET_NULL.PrintString();
	return 0;
}
