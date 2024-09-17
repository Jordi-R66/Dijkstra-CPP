#ifndef UTILS_H
#define UTILS_H

#include "commons.hpp"

using namespace std;

namespace Dijkstra {
	namespace Utils {
		typedef enum {
			LIEN_UNI = 1,
			LIEN_BI = 2,
			ERR = 3
		} TypeLien;

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

			TypeLien type;

			Lien(int64_t A, int64_t B, TypeLien T);
		};

		struct Graph {
			vector<Sommet> sommets;
			vector<Lien> liens;

			Graph(vector<Sommet> S, vector<Lien> L);
		};
	}
}

#endif
