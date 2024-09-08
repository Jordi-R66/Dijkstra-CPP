#ifndef UTILS_H
#define UTILS_H

#include "commons.hpp"

using namespace std;

namespace Dijkstra {
	namespace Utils {

		struct Sommet {
			int64_t id;
			string name;

			double x;
			double y;
			double z;

			vector<int64_t> canReach;

			Sommet(int64_t id, string name, double x, double y, double z);
			void PrintString();
		};

		struct Lien {
			int64_t idA;
			int64_t idB;

			Lien(int64_t A, int64_t B);
		};

		struct Graph {
			vector<Sommet> sommets;
			vector<Lien> liens;

			Graph(vector<Sommet> S, vector<Lien> L);
		};
	}
}

#endif
