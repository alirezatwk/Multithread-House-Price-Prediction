#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "utils.hpp"

using namespace std;


vector<vector<int>> dataset;
vector<string> columns;
int dataset_size = 0;
int threshold;

const string FILENAME = "dataset.csv";



int main(int argc, char* argv[]){


	string dataset_path(argv[1]);
	threshold = atoi(argv[2]);

	string complete_address = append_address(dataset_path, FILENAME);
	read_dataset(complete_address);

	


	return 0;
}