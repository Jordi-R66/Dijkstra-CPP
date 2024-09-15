#include "FileInteractions.hpp"

using namespace std;
using namespace Dijkstra;

Utils::Graph LoadGraphFromCSV(string VerticesFilename, string SidesFilename) {
	vector<Dijkstra::Utils::Sommet> sommets;
	vector<Dijkstra::Utils::Lien> liens;

	return Dijkstra::Utils::Graph(sommets, liens);
}

/*vector<Dijkstra::Utils::Sommet> Fichiers::LoadVerticesFromCSV(string VerticesFilename) {
	vector<Dijkstra::Utils::Sommet> vecSommets = {};
	ifstream myfile;

	string raw_data;

	myfile.open(VerticesFilename);
	myfile >> raw_data;

	myfile.close();

	size_t data_len = raw_data.length();

	const char sep = '\t';

	vector<string> lines;
	string line;

	size_t entries = 0;

	for (size_t i=0; i < data_len; i++) {
		char c = raw_data[i];

		if (c != '\n') {
			line += c;
		} else {
			entries++;
			lines.push_back(line);
			line.clear();
		}
	}

	lines.erase(lines.cbegin());
	cout << "Là" << endl;
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

		vecSommets.push_back(Dijkstra::Utils::Sommet(id, name, x, y, z));
	}

	return vecSommets;
}*/

void Fichiers::LoadVerticesFromCSV(string VerticesFilename, vector<Dijkstra::Utils::Sommet>* Vertices) {
	//vector<Dijkstra::Utils::Sommet> vecSommets = {};

	FILE* fp = fopen(VerticesFilename.c_str(), 'r');

	//myfile.open(VerticesFilename, ios::in);

	string current_line;
	//size_t data_len = raw_data.length();

	const char sep = '\t';

	size_t n_entries = 0;

	char c;

	while (c != EOF) {
		c = getc(fp);

		if (c == '\n') {
			n_entries++;
		}
	}

	cout << n_entries << endl;
	fclose(fp);
}
