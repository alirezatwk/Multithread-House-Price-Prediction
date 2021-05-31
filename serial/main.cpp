#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "utils.hpp"

using namespace std;


vector<vector<int>> dataset;
vector<string> columns;
int dataset_size = 0;

const string FILENAME = "dataset.csv";



int main(int argc, char* argv[]){


	string dataset_path(argv[1]);
	int threshold = atoi(argv[2]);

	string complete_address = append_address(dataset_path, FILENAME);
	read_dataset(complete_address);
	classify_price(threshold);

	for(int i = 0; i < 10; i++){
		for(auto x : dataset[i])
			cout << x << ' ';
		cout << '\n';
	}
	


	return 0;
}