#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double sum_vector(vector<double> vec);
double mean_vector(vector<double> vec);
double median_vector(vector<double> vec);
double range_vector(vector<double> vec);
double covar(vector<double> first_vec, vector<double> sec_vec);
double cor(vector<double> first_vec, vector<double> sec_vec);
void print_stats(vector<double> vec);


int main(int arg, char** argv) {

	const int MAX_LEN = 1000;
	ifstream inFS("Boston.csv");
	string line;
	string rm_in, medv_in;

	vector<double> rm(MAX_LEN);
	vector<double> medv(MAX_LEN);

	cout << "Opening file Boston.csv." << endl;
	if (!inFS.is_open()) {
		cout << "Could not open file Boston.csv." << endl;
		return 1;
	}

	cout << "Reading line 1" << endl;
	getline(inFS, line);

	cout << "heading: " << line << endl;

	int numObservations = 0;

	while (inFS.good()) {
		getline(inFS, rm_in, ',');
		getline(inFS, medv_in, '\n');

		rm.at(numObservations) = stof(rm_in);
		medv.at(numObservations) = stof(medv_in);
		numObservations++;
	}

	rm.resize(numObservations);
	medv.resize(numObservations);

	cout << "new length " << rm.size() << endl;

	cout << "Closing file Boston.csv." << endl;
	inFS.close();

	cout << "Number of records: " << numObservations << endl << endl;

	cout << "Stats for rm" << endl;
	print_stats(rm);

	cout << "Stats for medv" << endl;
	print_stats(medv);

	cout << "Covariance = " << covar(rm, medv) << endl;
	
	cout << "Correlation = " << cor(rm, medv) << endl;

	cout << "Program terminated.";
	return 0;
}


double sum_vector(vector<double> vec) {
	double vec_sum = 0;
	for (vector<double>::iterator it = vec.begin(); it != vec.end(); it++) {
		vec_sum += *it;
	}

	return vec_sum;
}


double mean_vector(vector<double> vec) {
	double vec_mean;
	vec_mean = sum_vector(vec) / vec.size();
	return vec_mean;
}


double median_vector(vector<double> vec) {
	double vec_median;

	// Copy original vec to new vec to preserve state of original vec
	vector<double> temp_vec = vec;
	sort(temp_vec.begin(), temp_vec.end());

	// if even number of obs
	if (temp_vec.size() % 2 == 0) {
		vec_median = (((temp_vec.size() / 2) + (temp_vec.size() / 2) + 1) / 2);
	}
	else {	// else odd number of obs
		vec_median = (temp_vec.size() + 1) / 2;
	}
	return vec_median;
}


double range_vector(vector<double> vec) {
	// Copy original vec to new vec to preserve state of original vec
	vector<double> temp_vec = vec;
	sort(temp_vec.begin(), temp_vec.end());
	double vec_range = temp_vec.end() - temp_vec.begin();
	return vec_range;
}


double covar(vector<double> first_vec, vector<double> sec_vec) {
	double first_vec_mean = mean_vector(first_vec);
	double sec_vec_mean = mean_vector(sec_vec);
	double cov = 0;

	vector<double>::iterator first_vec_it = first_vec.begin();
	vector<double>::iterator sec_vec_it = sec_vec.begin();

	for (; first_vec_it != first_vec.end(); first_vec_it++, sec_vec_it++) {
		cov += (*first_vec_it - first_vec_mean) * (*sec_vec_it - sec_vec_mean);
	}
	cov = cov / (first_vec.size() - 1);
	return cov;
}


double cor(vector<double> first_vec, vector<double> sec_vec) {
	double first_vec_std_dev = 0;
	double sec_vec_std_dev = 0;
	double first_vec_mean = mean_vector(first_vec);
	double sec_vec_mean = mean_vector(sec_vec);
	double correlation = 0;

	vector<double>::iterator first_vec_it = first_vec.begin();
	vector<double>::iterator sec_vec_it = sec_vec.begin();

	for (; first_vec_it != first_vec.end(); first_vec_it++, sec_vec_it++) {
		first_vec_std_dev += pow((*first_vec_it - first_vec_mean), 2);
		sec_vec_std_dev += pow((*sec_vec_it - sec_vec_mean), 2);
	}

	first_vec_std_dev = first_vec_std_dev / first_vec.size();
	sec_vec_std_dev = sec_vec_std_dev / sec_vec.size();
	first_vec_std_dev = sqrt(first_vec_std_dev);
	sec_vec_std_dev = sqrt(sec_vec_std_dev);

	correlation = covar(first_vec, sec_vec) / (first_vec_std_dev * sec_vec_std_dev);
	return correlation;
}


void print_stats(vector<double> var) {
	cout << "Sum = " << sum_vector(var) << endl;
	cout << "Mean = " << mean_vector(var) << endl;
	cout << "Median = " << median_vector(var) << endl;
	cout << "Range = " << range_vector(var) << endl << endl;
}