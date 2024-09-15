#include "FileInteractions.hpp"

#include <cstring>

using namespace std;
using namespace Dijkstra;

const char READONLY_MODE = 'r';

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
	char** endptr;

	FILE* fp = fopen(VerticesFilename.c_str(), &READONLY_MODE);

	//myfile.open(VerticesFilename, ios::in);

	string current_line;
	//size_t data_len = raw_data.length();

	const char sep = '\t';

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

		if (c == '\t') {
			col_number++;
			field_col = 0;

		} else if (c == '\n') {
			//printf("%l\t%s\t");
			printf("\n");
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

			printf("%c", c);
			field_col++;
		}
	}

	cout << n_entries << endl;
	fclose(fp);
}
