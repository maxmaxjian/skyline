#include <iostream>
#include <vector>
#include <utility>

class solution {
public:
    std::vector<pair<int,int>> getSkyline(const std::vector<std::vector<int>> & buildings) {
	
    }
};

int main() {
    std::vector<std::vector<int>> buildings{
	{2, 9, 10},
	{3, 7, 15},
	{5, 12, 12},
	{15, 20, 10},
	{19, 24, 8}
    };

    solution soln;
    auto skyline = soln.getSkyline(buildings);
    
}
