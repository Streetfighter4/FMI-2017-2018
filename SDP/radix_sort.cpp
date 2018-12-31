#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string.h>
#include <ctime>

size_t countLetter(char* fileName) {
	std::unordered_set<char> countSet;

	std::ifstream ifs(fileName);
	char c;
	if(ifs.is_open()) {
		while(!ifs.eof()) {
				
			ifs.get(c);	
			countSet.insert(c);
		}
	}
	return countSet.size();
}

size_t alpha_count;

void msd_radix_sort_strings(std::vector<std::string>& strings, int low, int high, int pos) {
	if(high <= low) {
		return;
	}
	
	std::queue<std::string> buckets[alpha_count];
	int bucket_ind;
	for(int j = low; j < high; ++j) {	
		bucket_ind = (strings[j][pos] ? strings[j][pos] - 'a' + 1 : 0);
		buckets[bucket_ind].push(strings[j]);
	}

	int start_ind = low;
	int finish_ind = low;

	for(int j = 0; j < alpha_count; ++j) {
		
		while(!buckets[j].empty()) {
			strings[finish_ind++] = buckets[j].front();
			buckets[j].pop();
		}

		if(finish_ind > low+1) {
			msd_radix_sort_strings(strings, start_ind, finish_ind, pos+1);
		}

		start_ind = finish_ind;
	}
}

void parseFile(std::vector<std::string>& strings, char* fileName) {
	
	std::ifstream ifs(fileName);
	char buff[1024];
	if(ifs.is_open()) {
		while(!ifs.eof()) {		
			ifs.getline(buff, 1024);
			strings.push_back(buff);
			memset(buff, 0, 1024);
		}
	}
}

void print(const std::vector<std::string>& strings) {
	for(auto& str : strings) {
		std::cout << str << std::endl;
	}		
}

int main(int argc, char* argv[]) {
	alpha_count = countLetter(argv[1]);
	std::vector<std::string> strings;

	parseFile(strings, argv[1]);
	unsigned int start = clock();
	msd_radix_sort_strings(strings, 0, strings.size(), 0);
	unsigned int end = clock();

	std::cout << "start: " << start << std::endl;
	std::cout << "end: " << end << std::endl;

	std::cout << "time: " << (end-start)/double(CLOCKS_PER_SEC)*1000 << std::endl;
	return 0;
}
