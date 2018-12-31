#include <iostream>
#include <vector>

int main() {
	std::vector<std::pair<char, int> > vector_with_pairs1, vector_with_pairs2;


	for(int i = 0; i < 10; ++i) {	
		vector_with_pairs1.push_back(std::make_pair('a'+i, i));
		vector_with_pairs2.push_back(std::make_pair('a'+i, i+1));
	}
	
	if(vector_with_pairs1 == vector_with_pairs2) {
		std::cout << "equal" << std::endl;
	} else {
		std::cout << "not equal" << std::endl;
	}

	return 0;
}
