#include "FileInteractions.hpp"

using namespace std;

using namespace Dijkstra;
using namespace Fichiers;
using namespace Utils;

Utils::Graph LoadGraphFromCSV(string VerticesFile, string SidesFile) {
	vector<Sommet> sommets;
	vector<Lien> liens;


}

void LoadVerticesFromCSV(string VerticesFile, vector<Sommet>* vecSommets) {
	ifstream myfile;

	string raw_data;

	myfile.open(VerticesFile);
	myfile >> raw_data;

	myfile.close();

	size_t data_len = raw_data.length();

	const char sep = '\t';

	vector<string> lines;
	string line;

	for (size_t i=0; i < data_len; i++) {
		char c = raw_data[i];

		if (c != '\n') {
			line += c;
		} else {
			lines.push_back(line);
			line.clear();
		}
	}

	lines.erase(lines.begin() + 0);
	raw_data.clear();

	size_t vecSize = lines.size();

	for (size_t i=0; i<vecSize; i++) {
		char c;
		string tokens[5];

		string line = lines.at(i);
		size_t line_size = line.length();

		uint8_t n_sep = 0;

		for (size_t j=0; j<line_size; j++) {
			c = line[j];
			if (c != sep) {
				tokens[n_sep] += c;
			} else {
				n_sep++;
			}
		}

		int64_t id;
		string name;
		double x, y, z;

		id = stoll(tokens[1]);

		for (int8_t j=0; j < tokens[1].size(); j++) {
			name[j] = tokens[1][j];
		}

		x = stod(tokens[2]);
		y = stod(tokens[3]);
		z = stod(tokens[4]);

		vecSommets->push_back(Sommet(id, name, x, y, z));
	}
}
