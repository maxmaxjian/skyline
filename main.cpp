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
	    result.push_back(std::make_pair(buildings[0][1], 0));
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
                           std::pair<int,int> rtn;
			   if (pr.second < rec[2])
			       rtn = std::make_pair(pr.first, rec[2]);
			   else
			       rtn = pr;
                           return rtn;
		       });
	if (right_prev->second < rec[2])
	    toPrepend.push_back(std::make_pair(rec[1], right_prev->second));

	auto curr = toPrepend.begin(), next = std::next(curr);
        while (next != toPrepend.end()) {
            if (curr->second == next->second)
                next = toPrepend.erase(next);
            else {
                curr = next;
                next = std::next(curr);
            }
        }
	
	auto it = result.erase(result.begin(), right_gt);
	result.insert(it, toPrepend.begin(), toPrepend.end());

        curr = result.begin(), next = std::next(curr);
        while (next != result.end()) {
            if (curr->first == next->first)
                curr = result.erase(curr);
            else
                curr = next;
            next = std::next(curr);
        }
        
	return result;
    }
};

int main() {
    // std::vector<std::vector<int>> buildings{
    //     {2, 9, 10},
    //     {3, 7, 15},
    //     {5, 12, 12},
    //     {15, 20, 10},
    //     {19, 24, 8}
    // };

    std::vector<std::vector<int>> buildings{
        {2,9,10},
        {9,10,11},
        {10,12,10}
    };

    solution soln;
    auto skyline = soln.getSkyline(buildings);
    std::copy(skyline.begin(), skyline.end(), std::ostream_iterator<std::pair<int,int>>(std::cout, " "));
    std::cout << std::endl;
}
