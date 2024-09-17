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

	uint8_t col_number = 0;
	int8_t field_col = 0;
	int64_t current_entry = 0;

	int64_t id;
	string name;
	double x,y,z;

	char current_id[20];

	char current_x[30];
	char current_y[30];
	char current_z[30];

	memset(current_id, 0, 20);
	memset(current_x, 0, 30);
	memset(current_y, 0, 30);
	memset(current_z, 0, 30);

	while (c != EOF) {
		c = getc(fp);

		if (c == sep) {
			col_number++;
			field_col = 0;

		} else if (c == '\n') {
			id = strtol(current_id, endptr, 10);

			x = strtod(current_x, endptr);
			y = strtod(current_y, endptr);
			z = strtod(current_z, endptr);

			Utils::Sommet s = {id, name, x, y, z};
			Vertices->push_back(s);

			name.clear();
			col_number = 0;
			field_col = 0;

		} else {
			switch (col_number) {
				case 0:
					current_id[field_col] = c;
					break;

				case 1:
					name.push_back(c);
					break;

				case 2:
					current_x[field_col] = c;
					break;

				case 3:
					current_y[field_col] = c;
					break;

				case 4:
					current_z[field_col] = c;
					break;

				default:
					break;
			}

			field_col++;
		}
	}

	//cout << n_entries << endl;
	fclose(fp);
}

void Fichiers::LoadLinksFromCSV(string LinksFilename, vector<Dijkstra::Utils::Lien>* Links) {
	char **endptr;

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
	uint8_t col_number = 0;
	int8_t field_col = 0;
	int64_t current_entry = 0;

	int64_t idA;
	int64_t idB;
	Utils::TypeLien type;

	char current_idA[20];
	char current_idB[20];
	char current_type[2];

	memset(current_idA, 0, 20);
	memset(current_idB, 0, 20);
	memset(current_type, 0, 2);

	while (c != EOF) {
		c = getc(fp);

		if (c == sep) {
			col_number++;
			field_col = 0;

		} else if (c == '\n') {
			idA = strtol(current_idA, endptr, 10);
			idB = strtol(current_idB, endptr, 10);

			//type = (Dijkstra::Utils::TypeLien)strtol(current_type, endptr, 10);

			Utils::Lien l = {idA, idB, type};
			Links->push_back(l);

			col_number = 0;
			field_col = 0;

		} else {
			switch (col_number) {
				case 0:
					current_idA[field_col] = c;
					break;

				case 1:
					current_idA[field_col] = c;
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

			field_col++;
		}
	}

	//cout << n_entries << endl;
	fclose(fp);
}