#include "Utils.hpp"

using namespace std;

namespace Dijkstra {
	namespace Utils {
		Sommet::Sommet(int64_t id, string name, double x, double y, double z) : id(id), name(name), x(x), y(y), z(z) {
			this->canReach = {};
		}

		void Sommet::PrintString() {
			cout << "Sommet(id=" << id << ", name=" << name << ", x=" << to_string(x) << ", y=" << to_string(y) << ", z=" << to_string(z) << ")" << endl;
		}

		Lien::Lien(int64_t A, int64_t B, TypeLien T) : idA(A), idB(B), type(T) {
			return;
		}

		Graph::Graph(vector<Utils::Sommet> S, vector<Utils::Lien> L) : sommets(S), liens(L) {
			return;
		}
	}
}
