#include <iostream>
#include <memory>
#include <chrono>
#include <list>
#include <map>
#include <utility>
#include <list>
#include "../include/allocator.h"
#include "../include/queue.h"

int main(int argc, char **argv){

    std::map<int, int, std::less<int>, mystd::Allocator<std::pair<const int, int>, 1000>> my_map;
    my_map[0] = 1;

    for(int i{1}; i <= 10; ++i){
        my_map[i] = my_map[i-1] * i;
    }

    for(const auto& [k,v]: my_map)
        std::cout << k << "->" << v << std::endl;

    std::cout << "--------------------------\n";

    my_q::Queue<int,mystd::Allocator<int>> my_queue;

    for(int i{100}; i < 110; ++i){
        my_queue.push(i);
    }

    for(auto it = my_queue.begin(); it != my_queue.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Queue size = " << my_queue.get_size() << std::endl;
    
    return 0;
}
