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
	size_t data_len = raw_data.length();

	const string sep = "\t";

	vector<string> lines;
	string line;

	for (size_t i=0; i < data_len; i++) {
		char c = raw_data[i];

		if (c != '\n') {
			line += c;
		} else {
			lines.push_back(line);
			line = "";
		}
	}

	size_t vecSize = lines.size();

	for (size_t i=0; i<vecSize; i++) {
		
	}

}
