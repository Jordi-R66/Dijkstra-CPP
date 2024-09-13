#ifndef FILES_H
#define FILES_H

#include "commons.hpp"
#include "Utils.hpp"

using namespace std;

namespace Dijkstra {
	namespace Fichiers {
		void LoadVerticesFromCSV(string VerticesFilename, vector<Utils::Sommet>* Vertices);
		vector<Utils::Lien> LoadLinksFromCSV(string LinksFile);
		Utils::Graph LoadGraphFromCSV(string VerticesFilename, string LinksFile);
	}
}

#endif