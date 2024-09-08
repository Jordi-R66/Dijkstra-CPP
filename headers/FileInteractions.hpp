#ifndef FILES_H
#define FILES_H

#include "commons.hpp"
#include "Utils.hpp"

namespace Fichiers {
	void LoadVerticesFromCSV(string VerticesFile, vector<Sommet>* vecSommets);
	void LoadLinksFromCSV(string LinksFile, vector<Lien>* vecLiens);
	Utils::Graph LoadGraphFromCSV(string VerticesFile, string LinksFile);
}

#endif