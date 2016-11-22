#include <iostream>
#include <vector>
#include <utility>
#include <iterator>
#include <algorithm>

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::pair<int,int> & pr) {
	os << "(" << pr.first << "," << pr.second << ")";
	return os;
    }
}


class solution {
public:
    std::vector<std::pair<int,int>> getSkyline(const std::vector<std::vector<int>> & buildings) {
	std::vector<std::pair<int,int>> result;
	if (buildings.size() == 1) {
	    result.push_back(std::make_pair(buildings[0][0], buildings[0][2]));
	    result.push_back(std::make_pair(buildings[0][2], 0));
	}
	else if (buildings.size() > 1) {
	    std::vector<int> curr = buildings[0];
	    std::vector<std::pair<int,int>> prev = getSkyline(std::vector<std::vector<int>>(buildings.begin()+1, buildings.end()));
	    result = combine(curr, prev);
	}
	return result;
    }

private:
    std::vector<std::pair<int,int>> combine(const std::vector<int> & rec, const std::vector<std::pair<int,int>> & skyline) {
	auto result = skyline;
	auto right_gt = std::upper_bound(result.begin(), result.end(), rec[1],
					[](int val, const std::pair<int,int> & pr){
					    return val < pr.first;
					});
	auto right_prev = std::prev(right_gt);

	std::vector<std::pair<int,int>> toPrepend{std::make_pair(rec[0], rec[2])};
	std::transform(result.begin(), right_gt, std::inserter(toPrepend, toPrepend.end()),
		       [&](const std::pair<int,int> & pr){
			   if (pr.second < rec[2])
			       return std::make_pair(pr.first, rec[2]);
			   else
			       return pr;
		       });
	if (right_prev->second < rec[2])
	    toPrepend.push_back(std::make_pair(rec[1], right_prev->second));

	
	
	auto it = result.erase(result.begin(), right_gt);
	result.insert(it, toPrepend.begin(), toPrepend.end());
	return result;
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
    std::copy(skyline.begin(), skyline.end(), std::ostream_iterator<std::pair<int,int>>(std::cout, " "));
    std::cout << std::endl;
}
