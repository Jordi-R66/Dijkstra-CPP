#pragma once

#include "commons.hpp"
#include "Utils.hpp"

using namespace std;

namespace Dijkstra {
	namespace Fichiers {
		void LoadVerticesFromCSV(string VerticesFilename, vector<Utils::Sommet>& Vertices);
		void LoadLinksFromCSV(string LinksFilename, vector<Utils::Lien>& Links);
		//void LoadGraphFromCSV(string VerticesFilename, string LinksFilename, Utils::Graph* WorkGraph);
	}
}
