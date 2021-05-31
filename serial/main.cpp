#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
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
bool print_times = true;

const string FILENAME = "dataset.csv";
const string GrLivArea = "GrLivArea";

int main(int argc, char* argv[]){
	auto start_all = chrono::high_resolution_clock::now();

	string dataset_path(argv[1]);
	int threshold = atoi(argv[2]);

	string complete_address = append_address(dataset_path, FILENAME);

	auto start = chrono::high_resolution_clock::now();
	read_dataset(complete_address);
	auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    if(print_times)
    	cout << "Time taken for reading dataset is : " << fixed << time_taken << setprecision(9) << " sec" << endl;

    start = chrono::high_resolution_clock::now();
	classify_price(threshold);
	end = chrono::high_resolution_clock::now();
	time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    if(print_times)
    	cout << "Time taken for classifying is : " << fixed << time_taken << setprecision(9) << " sec" << endl;

    start = chrono::high_resolution_clock::now();
	calc_mean_var();
	end = chrono::high_resolution_clock::now();
	time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    if(print_times)
    	cout << "Time taken for calculating mean and variance is : " << fixed << time_taken << setprecision(9) << " sec" << endl;

	int GrLivArea_ind;
	for(uint i = 0; i < columns.size(); i++)
		if(columns[i] == GrLivArea)
			GrLivArea_ind = i;

	start = chrono::high_resolution_clock::now();
	predict(GrLivArea_ind);
	print_accuracy();
	end = chrono::high_resolution_clock::now();
	time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    if(print_times)
    	cout << "Time taken for predicting and printing is : " << fixed << time_taken << setprecision(9) << " sec" << endl;

    auto end_all = chrono::high_resolution_clock::now();
    time_taken = chrono::duration_cast<chrono::nanoseconds>(end_all - start_all).count();
    time_taken *= 1e-9;
    if(print_times)
    	cout << "Time taken is : " << fixed << time_taken << setprecision(9) << " sec" << endl;


	return 0;
}