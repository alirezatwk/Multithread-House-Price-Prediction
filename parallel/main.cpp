#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <pthread.h>
#include <iomanip>
#include "utils.hpp"

using namespace std;

const string GrLivArea = "GrLivArea";

vector<vector<int>> dataset;
int dataset_size = 0;
int cheap_size = 0, expensive_size = 0;
vector<double> cheap_mean;
vector<double> expensive_mean;
vector<double> cheap_var;
vector<double> expensive_var;
vector<int> predictions;
bool print_times = true;


pthread_mutex_t mutex_dataset;

DatasetReadingArgs dataset_reading_args[NUMBER_OF_THREADS];

void* read_dataset_multi(void* args) {
    DatasetReadingArgs* thread_args = (DatasetReadingArgs*) args;
    string dataset_folder = thread_args->dataset_folder;
    int threshold = thread_args->threshold;
    long tid = thread_args->tid;
    string dataset_filename = append_address(dataset_folder, "dataset_" + to_string(tid) + ".csv");
    // cout << dataset_filename << '\n';
    vector<vector<int>> local_dataset = read_dataset(dataset_filename);
    classify_price(threshold, local_dataset);


    pthread_mutex_lock(&mutex_dataset);
    dataset.insert(dataset.end(), local_dataset.begin(), local_dataset.end());
    dataset_size += local_dataset.size();
    pthread_mutex_unlock(&mutex_dataset);

    pthread_exit(NULL);
}


int main(int argc, char* argv[]){
	auto start_all = chrono::high_resolution_clock::now();

	string dataset_path(argv[1]);
	int threshold = atoi(argv[2]);

	pthread_t threads[NUMBER_OF_THREADS];
	pthread_mutex_init(&mutex_dataset, NULL);

	for(long tid = 0; tid < NUMBER_OF_THREADS; tid++){
        dataset_reading_args[tid].dataset_folder = dataset_path;
        dataset_reading_args[tid].tid = tid;
        dataset_reading_args[tid].threshold = threshold;
        int ret = pthread_create(&threads[tid], NULL, read_dataset_multi, (void*) &dataset_reading_args[tid]);
    }
    for(long tid = 0; tid < NUMBER_OF_THREADS; tid++)
        pthread_join(threads[tid], NULL);


	calc_mean_var();

	predict(5);
	print_accuracy();

    auto end_all = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end_all - start_all).count();
    time_taken *= 1e-9;
    if(print_times)
    	cout << "Time taken is : " << fixed << time_taken << setprecision(9) << " sec" << endl;

	pthread_mutex_destroy(&mutex_dataset);
    pthread_exit(NULL);
}