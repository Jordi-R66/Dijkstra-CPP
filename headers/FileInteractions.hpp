#ifndef FILES_H
#define FILES_H

#include "commons.hpp"
#include "Utils.hpp"

namespace Dijkstra {
	namespace Fichiers {
		vector<Utils::Sommet> ImporterSommets(string filename);
	}
}

#endif