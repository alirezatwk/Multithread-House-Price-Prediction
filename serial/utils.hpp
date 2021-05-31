#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>

extern std::vector<std::vector<int>> dataset;
extern std::vector<std::string> columns;
extern int dataset_size;
extern int cheap_size;
extern int expensive_size;
extern std::vector<double> cheap_mean;
extern std::vector<double> expensive_mean;
extern std::vector<double> cheap_var;
extern std::vector<double> expensive_var;
extern std::vector<int> predictions;

std::string append_address(std::string directory, std::string filename);
void read_dataset(std::string dataset_address);
void classify_price(int threshold);
void calc_mean_var(void);
void predict(int column_id);
void print_accuracy(void);


#endif