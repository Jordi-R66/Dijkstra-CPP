#ifndef FILES_H
#define FILES_H

#include "commons.hpp"
#include "Utils.hpp"

using namespace std;

namespace Dijkstra {
	namespace Fichiers {
		vector<Utils::Sommet> LoadVerticesFromCSV(string VerticesFile);
		vector<Utils::Lien> LoadLinksFromCSV(string LinksFile);
		Utils::Graph LoadGraphFromCSV(string VerticesFile, string LinksFile);
	}
}

#endif