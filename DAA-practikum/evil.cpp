#include <iostream>
#include <vector>


int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::pair<int, int> > pairs;
	int left, right;

	std::cin >> left >> right;
	pairs.push_back(std::make_pair(left, right));
	bool inInterval;
	for(int i = 0; i < m-1; ++i) {
		std::cin >> left >> right;

		inInterval = false;
		for(auto& p : pairs) {
			if(p.first <= left && p.second >= right) {			
				inInterval = true;
				break;
			} else if(left < p.first && right <= p.second && right >= p.first) {
				p.first = left;
				inInterval = true;
				break;
			} else if(left >= p.first && left <= p.second && right > p.second) {
				inInterval = true;
				p.second = right;
				break;
			} else if(left < p.first && right > p.second) {
				inInterval = true;
				p.first = left;
				p.second = right;
				break;
			}	
		}
		if(!inInterval) {	
			pairs.push_back(std::make_pair(left, right));
		}

	}

	for(auto& p : pairs) {
		std::cout << "left: " << p.first << ", right: " << p.second << std::endl;
	}


	return 0;
}
