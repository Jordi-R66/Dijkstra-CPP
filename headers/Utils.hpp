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
			id_t id;
			string name;

			double x;
			double y;
			double z;

			vector<id_t> neighbours;

			Sommet(id_t id, string name, double x, double y, double z);
			void PrintString();

			bool operator==(const Sommet& other) const;
			bool operator!=(const Sommet& other) const;
		};

		struct Lien {
			id_t idA;
			id_t idB;

			TypeLien type;

			Lien(id_t A, id_t B, TypeLien T);
		};

		struct Graph {
			vector<Sommet> sommets;
			vector<Lien> liens;

			Graph(vector<Sommet> S, vector<Lien> L);
		};
	}
}

#endif
