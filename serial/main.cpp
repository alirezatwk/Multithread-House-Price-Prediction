#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "utils.hpp"

using namespace std;


vector<vector<int>> dataset;
vector<string> columns;
int dataset_size = 0;
int cheap_size = 0, expensive_size = 0;
vector<double> cheap_mean;
vector<double> expensive_mean;
vector<double> cheap_var;
vector<double> expensive_var;
vector<int> predictions;


const string FILENAME = "dataset.csv";
const string GrLivArea = "GrLivArea";

int main(int argc, char* argv[]){


	string dataset_path(argv[1]);
	int threshold = atoi(argv[2]);

	string complete_address = append_address(dataset_path, FILENAME);
	read_dataset(complete_address);
	classify_price(threshold);
	calc_mean_var();

	int GrLivArea_ind;
	for(uint i = 0; i < columns.size(); i++)
		if(columns[i] == GrLivArea)
			GrLivArea_ind = i;

	predict(GrLivArea_ind);
	print_accuracy();

	return 0;
}