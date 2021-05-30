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

// void calculate_cols_min_max(void) {
//     for (int feature_idx = 0; feature_idx < 20; feature_idx++) {
//         cols_min_max[feature_idx].min = dataset[0][feature_idx];
//         cols_min_max[feature_idx].max = dataset[0][feature_idx];

//         for (unsigned long i = 0; i < dataset_size; i++) {
//             if (dataset[i][feature_idx] < cols_min_max[feature_idx].min)
//                 cols_min_max[feature_idx].min = dataset[i][feature_idx];
//             if (dataset[i][feature_idx] > cols_min_max[feature_idx].max)
//                 cols_min_max[feature_idx].max = dataset[i][feature_idx];
//         }
//     }
// }

// void normalize_dataset(void) {
//     for (unsigned long i = 0; i < dataset_size; i++) {
//         for (int feature_idx = 0; feature_idx < 20; feature_idx++) {
//             dataset[i][feature_idx] = (dataset[i][feature_idx] - cols_min_max[feature_idx].min)
//                                     / (cols_min_max[feature_idx].max - cols_min_max[feature_idx].min);
//         }
//     }
// }

// void guess_classification(void) {
//     for (unsigned long i = 0; i < dataset_size; i++) {
//         double range_0_dot_product = 0.0;
//         double range_1_dot_product = 0.0;
//         double range_2_dot_product = 0.0;
//         double range_3_dot_product = 0.0;

//         for (int feature_idx = 0; feature_idx < 20; feature_idx++) {
//             range_0_dot_product += weights[0][feature_idx] * dataset[i][feature_idx];
//             range_1_dot_product += weights[1][feature_idx] * dataset[i][feature_idx];
//             range_2_dot_product += weights[2][feature_idx] * dataset[i][feature_idx];
//             range_3_dot_product += weights[3][feature_idx] * dataset[i][feature_idx];
//         } 
//         range_0_dot_product += weights[0][20];
//         range_1_dot_product += weights[1][20];
//         range_2_dot_product += weights[2][20];
//         range_3_dot_product += weights[3][20];

//         classification_results.push_back(get_best_classification(range_0_dot_product, range_1_dot_product, range_2_dot_product, range_3_dot_product));
//         if (classification_results[i] == dataset[i][20])
//             correct_detected_classification++;
//     }
// }

// double get_best_classification(double range_0_dot_product, double range_1_dot_product,
//                          double range_2_dot_product, double range_3_dot_product) {

//     int max_idx = 0;
//     double max_val = range_0_dot_product;

//     if (range_1_dot_product > max_val) {
//         max_val = range_1_dot_product;
//         max_idx = 1;
//     }
//     if (range_2_dot_product > max_val) {
//         max_val = range_2_dot_product;
//         max_idx = 2;
//     }
//     if (range_3_dot_product > max_val) {
//         max_val = range_3_dot_product;
//         max_idx = 3;
//     }

//     return (double)max_idx;
// }

// void print_accuracy(void) {
//     double accuracy = 100*(correct_detected_classification/(double)dataset_size);
//     printf("Accuracy: %.2f%\n", accuracy);
// }