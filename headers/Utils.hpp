#pragma once

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
			s_id_t id;
			string name;

			double x;
			double y;
			double z;

			vector<s_id_t> neighbours;

			Sommet(s_id_t id, string name, double x, double y, double z);
			void PrintString();

			bool operator==(const Sommet& other) const;
			bool operator!=(const Sommet& other) const;
		};

		struct Lien {
			s_id_t idA;
			s_id_t idB;

			TypeLien type;

			Lien(s_id_t A, s_id_t B, TypeLien T);
		};

		struct Graph {
			vector<Sommet> sommets;
			vector<Lien> liens;

			Graph(vector<Sommet> S, vector<Lien> L);
		};
	}
}
