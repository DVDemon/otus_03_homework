#include "lib.h"
#include <vector>
#include <map>

template <int N> int factorial(){
    return N*factorial<N-1>();
}
template <> int factorial<0>(){
    return 1;
}

using map_type = std::map<int,int>;
using map_type_with_allocator = std::map<int,int,std::less<int>,homework::my_allocator<std::pair<const int,int>,10>>;

template <int N> void fill_map(map_type &map){
    map.insert(std::pair<int,int>(N,factorial<N>()));
    fill_map<N-1>(map);
}

template <> void fill_map<0>(map_type &map){
    map.insert(std::pair<int,int>(0,factorial<0>()));
}

template <int N> void fill_map(map_type_with_allocator &map){
    map.insert(std::pair<int,int>(N,factorial<N>()));
    fill_map<N-1>(map);
}

template <> void fill_map<0>(map_type_with_allocator &map){
    map.insert(std::pair<int,int>(0,factorial<0>()));
}

int main(int argc, char* argv[]){
 
 map_type my_map;
 fill_map<9>(my_map);
 
 map_type_with_allocator my_map_with_allocator;
 fill_map<9>(my_map_with_allocator);

 for(auto p:my_map_with_allocator) std::cout << p.first << " " << p.second << std::endl;

 homework::my_container<int,std::allocator<int>> container;
 for(size_t i=0;i<10;i++) container.push_back(i);

 homework::my_container<int,homework::my_allocator<int,10>> container_with_my_allocator;
 for(size_t i=0;i<10;i++) container_with_my_allocator.push_back(i);
 for(auto i: container_with_my_allocator) std::cout<< i << std::endl;



 UNUSED(argc);
 UNUSED(argv);
 return 0;
}