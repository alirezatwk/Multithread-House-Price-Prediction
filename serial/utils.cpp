#include "utils.hpp"

using namespace std;

string append_address(string directory, string filename){
	string begin("../");
	if(directory[directory.size() - 1] == '/')
		return begin + directory + filename;
	return begin + directory + "/" + filename;
}

void split_one_csv_line(vector<int> &result, string line){
	stringstream ss(line);
	string token;
	while(getline(ss, token, ','))
		result.push_back(atoi(token.c_str()));
}

void split_one_csv_line(vector<string> &result, string line){
	stringstream ss(line);
	string token;
	while(getline(ss, token, ','))
		result.push_back(token);
}


void read_dataset(string dataset_address){
	ifstream dataset_file(dataset_address);
	if(!dataset_file){
		cerr << "Error opening dataset.csv" << endl;
		exit(1);
	}

	string line;
	int value;

	// Set Columns
	getline(dataset_file, line);
	split_one_csv_line(columns, line);

	// Read dataset
	while(getline(dataset_file, line)){
		vector<int> new_entry;
		split_one_csv_line(new_entry, line);
		dataset.push_back(new_entry);
	}
	dataset_size = dataset.size();
	dataset_file.close();
}

void classify_price(int threshold){
	for(int i = 0; i < dataset_size; i++)
		if(dataset[i][dataset[i].size() - 1] >= threshold){
			dataset[i][dataset[i].size() - 1] = 1;
			expensive_size++;
		}
		else{
			dataset[i][dataset[i].size() - 1] = 0;
			cheap_size++;
		}
}

void calc_mean_var(void){
	// Initialization
	for(uint i = 0; i < columns.size(); i++){
		cheap_mean.push_back(0.0);
		expensive_mean.push_back(0.0);
		cheap_var.push_back(0.0);
		expensive_var.push_back(0.0);
	}

	// Mean
	int price_ind = columns.size() - 1;
	for(int i = 0; i < dataset_size; i++){
		if(dataset[i][price_ind] == 0){
			for(uint j = 0; j < columns.size(); j++)
				cheap_mean[j] += dataset[i][j];
		}
		else{
			for(uint j = 0; j < columns.size(); j++)
				expensive_mean[j] += dataset[i][j];
		}
	}
	for(uint i = 0; i < columns.size(); i++){
		cheap_mean[i] /= cheap_size;
		expensive_mean[i] /= expensive_size;
	}

	//Variance
	for(int i = 0; i < dataset_size; i++){
		if(dataset[i][price_ind] == 0){
			for(uint j = 0; j < columns.size(); j++)
				cheap_var[j] += (dataset[i][j] - cheap_mean[j]) * (dataset[i][j] - cheap_mean[j]);
		}
		else{
			for(uint j = 0; j < columns.size(); j++)
				expensive_var[j] += (dataset[i][j] - expensive_mean[j]) * (dataset[i][j] - expensive_mean[j]);
		}
	}
	for(uint i = 0; i < columns.size(); i++){
		cheap_var[i] /= cheap_size - 1;
		expensive_var[i] /= expensive_size - 1;
	}
}

void predict(int column_id){
	double sd = sqrt(expensive_var[column_id]);

	double begin = expensive_mean[column_id] - sd;
	double end = expensive_mean[column_id] + sd;

	for(int i = 0; i < dataset_size; i++){
		if(dataset[i][column_id] < begin || end < dataset[i][column_id])
			predictions.push_back(0);
		else
			predictions.push_back(1);
	}
}

void print_accuracy(void) {
	int correct_detected_classification = 0;
	int price_ind = columns.size() - 1;

	for(int i = 0; i < dataset_size; i++)
		if(dataset[i][price_ind] == predictions[i])
			correct_detected_classification++;
    double accuracy = 100 * (correct_detected_classification / (double)dataset_size);
    printf("Accuracy: %.2f%\n", accuracy);
}