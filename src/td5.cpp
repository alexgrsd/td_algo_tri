#include <stdio.h>
#include <string>

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

bool operator == (position const& p1, position const& p2){
    return (p1.x == p2.x) && (p1.y == p2.y);
}

std::ostream& operator << (std::ostream& os, position const& p){
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

position operator += (position& p, direction d){
    switch (d) {
        case direction::NORTH:
            p.y += 1;
            break;
        case direction::EAST:
            p.x += 1;
            break;
        case direction::SOUTH:
            p.y -= 1;
            break;
        case direction::WEST:
            p.x -= 1;
            break;
    }
    return p;
}

position operator += (position const& p, position const& d){
    position result;
    result.x = p.x + d.x;
    result.y = p.y + d.y;
    return result;
}


enum class direction {NORTH, EAST, SOUTH, WEST};



struct position {
    int x;
    int y;
};

int main(){
    return 0;
}