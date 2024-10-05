#include "FileInteractions.hpp"

#include <cstring>

using namespace std;
using namespace Dijkstra;

const char READONLY_MODE = 'r';
const char sep = '\t';

/*void Fichiers::LoadGraphFromCSV(string VerticesFilename, string LinksFilename, Dijkstra::Utils::Graph* WorkGraph) {
	vector<Dijkstra::Utils::Sommet> sommets;
	vector<Dijkstra::Utils::Lien> liens;

	return;
}*/

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

	char** endptr;

	FILE* fp = fopen(VerticesFilename.c_str(), &READONLY_MODE);

	size_t n_entries = 0;

	char c = 0;

	while (c != EOF) {
		c = getc(fp);

		if (c == '\n') {
			n_entries++;
		}
	}

	c = 0;

	fseek(fp, 0, SEEK_SET);
	Vertices->reserve(n_entries);

	uint8_t col_number = 0;
	int64_t current_entry = 0;

	s_id_t id;
	string name;
	double x,y,z;

	string current_id = "";

	string current_x;
	string current_y;
	string current_z;

	while (c != EOF) {
		c = getc(fp);

		if (c == EOF) {
			break;
		}

		if (c == sep) {
			col_number++;

		} else if (c == '\n') {

			id = stol(current_id);

			x = stod(current_x);
			y = stod(current_y);
			z = stod(current_z);

			Utils::Sommet s = {id, name, x, y, z};
			Vertices->push_back(s);

			current_id = "";
			current_x = "";
			current_y = "";
			current_z = "";

			name = "";
			col_number = 0;

		} else {
			switch (col_number) {
				case 0:
					current_id += c;
					break;

				case 1:
					name.push_back(c);
					break;

				case 2:
					current_x += c;
					break;

				case 3:
					current_y += c;
					break;

				case 4:
					current_z += c;
					break;

				default:
					break;
			}
		}
	}

	Vertices->shrink_to_fit();

	// cout << n_entries << endl;
	fclose(fp);
}

void Fichiers::LoadLinksFromCSV(string LinksFilename, vector<Dijkstra::Utils::Lien>* Links) {
	//char **endptr;

	FILE* fp = fopen(LinksFilename.c_str(), &READONLY_MODE);

	size_t n_entries = 0;

	char c = 0;

	while (c != EOF) {
		c = getc(fp);

		if (c == '\n') {
			n_entries++;
		}
	}

	c = 0;

	fseek(fp, 0, SEEK_SET);
	Links->reserve(n_entries);

	uint8_t col_number = 0;
	int64_t current_entry = 0;

	s_id_t idA;
	s_id_t idB;
	Utils::TypeLien type;

	string current_idA = "";
	string current_idB = "";

	while (c != EOF) {
		c = getc(fp);

		if (c == EOF) {
			break;
		}

		//printf("%c", c);

		if (c == sep) {
			col_number++;

		} else if (c == '\n') {
			idA = stol(current_idA);
			idB = stol(current_idB);

			if (idA == idB) {
				type = Utils::TypeLien::ERR;
			}

			Utils::Lien l = {idA, idB, type};
			Links->push_back(l);

			col_number = 0;
			current_idA = "";
			current_idB = "";

		} else {
			switch (col_number) {
				case 0:
					current_idA += c;
					break;

				case 1:
					current_idB += c;
					break;

				case 2:
					if (c == '1') {
						type = Dijkstra::Utils::LIEN_UNI;
					} else if (c == '2') {
						type = Dijkstra::Utils::LIEN_BI;
					} else {
						type = Dijkstra::Utils::ERR;
					}
					break;

				default:
					break;
			}
		}
	}

	Links->shrink_to_fit();

	//cout << n_entries << endl;
	fclose(fp);
}
