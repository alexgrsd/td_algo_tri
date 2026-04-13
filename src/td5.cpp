#include <stdio.h>
#include <string>
#include <iostream>

size_t folding_string_hash(std::string const& s, size_t max){
    size_t hash {0};
    for (size_t i {0}; i<s.size(); i++){
        hash += s[i];
    }
    return hash % max;
}

size_t folding_string_ordered_hash(std::string const& s, size_t max){
    size_t hash {0};
    for (size_t i {0}; i<s.size(); i++){
        hash += s[i] * (i+1);
    }
    return hash % max;
}


int main() {

    return 0;
}