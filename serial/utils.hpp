#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

extern std::vector<std::vector<int>> dataset;
extern std::vector<std::string> columns;
extern int dataset_size;

std::string append_address(std::string directory, std::string filename);
void read_dataset(std::string dataset_address);
void classify_price(int threshold);

// void calculate_cols_min_max(void);
// void normalize_dataset(void);
// void guess_classification(void);
// double get_best_classification(double range_0_dot_product, double range_1_dot_product, double range_2_dot_product, double range_3_dot_product);
// void print_accuracy(void);

#endif