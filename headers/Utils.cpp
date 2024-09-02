#include "Utils.hpp"

#include <iostream>
// #include <iomanip>

using namespace std;

namespace Dijkstra {
	namespace Utils {
		Sommet::Sommet(int64_t id, string name, double x, double y, double z) : id(id), name(name), x(x), y(y), z(z) {
			this->canReach = {};
		}

		void Sommet::PrintString() {
			cout << "Sommet(id=" << id << ", name=" << name << ", x=" << to_string(x) << ", y=" << to_string(y) << ", z=" << to_string(z) << ")" << endl;
		}
	}
}
