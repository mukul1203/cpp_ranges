#include "range/v3/all.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {1,2,4,5,6,78,5,34,57,54};
    ranges::actions::sort(v);
    std::cout<<ranges::views::all(v)<<std::endl;
    std::cout<<"Hello world!"<<std::endl;
    return 0;
}