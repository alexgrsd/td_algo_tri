#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>

enum class direction { NORTH, EAST, SOUTH, WEST };

struct position {
    int x;
    int y;
};

bool operator==(position const& p1, position const& p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
}

bool operator<(position const& p1, position const& p2) {
    if (p1.x != p2.x) return p1.x < p2.x;
    return p1.y < p2.y;
}

std::ostream& operator<<(std::ostream& os, position const& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

position& operator+=(position& p1, position const& p2) {
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

position operator+(position p1, position const& p2) {
    p1 += p2;
    return p1;
}

position direction_to_position(direction d) {
    switch (d) {
        case direction::NORTH: return {0, -1};
        case direction::EAST:  return {1, 0};
        case direction::SOUTH: return {0, 1};
        case direction::WEST:  return {-1, 0};
    }
    return {0, 0};
}

position& operator+=(position& p, direction d) {
    p += direction_to_position(d);
    return p;
}

position operator+(position p, direction d) {
    p += d;
    return p;
}

direction turn_right(direction d) {
    switch (d) {
        case direction::NORTH: return direction::EAST;
        case direction::EAST:  return direction::SOUTH;
        case direction::SOUTH: return direction::WEST;
        case direction::WEST:  return direction::NORTH;
    }
    return direction::NORTH;
}

struct InputStructure {
    position guard_pos;
    direction guard_dir;
    std::set<position> obstacles;
    int width;
    int height;
};

direction char_to_direction(char c) {
    switch (c) {
        case '^': return direction::NORTH;
        case '>': return direction::EAST;
        case 'v': return direction::SOUTH;
        case '<': return direction::WEST;
    }
    return direction::NORTH;
}

InputStructure read_input(std::istream& is) {
    InputStructure input;

    std::string line;
    int y = 0;

    while (std::getline(is, line)) {
        input.width = line.size();
        for (int x = 0; x < (int)line.size(); x++) {
            char c = line[x];
            position pos {x, y};

            if (c == '#') {
                input.obstacles.insert(pos);
            }
            else if (c == '^' || c == '>' || c == 'v' || c == '<') {
                input.guard_pos = pos;
                input.guard_dir = char_to_direction(c);
            }
        }
        y++;
    }

    input.height = y;
    return input;
}

namespace std {
    template <>
    struct hash<position> {
        std::size_t operator()(const position& pos) const {
            std::size_t h1 = std::hash<int>()(pos.x);
            std::size_t h2 = std::hash<int>()(pos.y);
            return h1 ^ (h2 << 1);
        }
    };
}

struct WalkResult {
    position final_position;
    size_t steps_taken;
    std::unordered_set<position> visited_positions;
};

WalkResult simulate_walk(InputStructure const& input) {
    WalkResult result;

    position pos = input.guard_pos;
    direction dir = input.guard_dir;

    result.steps_taken = 0;
    result.visited_positions.insert(pos);

    while (true) {
        position next = pos + dir;

        if (next.x < 0 || next.y < 0 || next.x >= input.width || next.y >= input.height) {
            result.final_position = pos;
            return result;
        }

        if (input.obstacles.find(next) != input.obstacles.end()) {
            dir = turn_right(dir);
        } else {
            pos = next;
            result.visited_positions.insert(pos);
            result.steps_taken++;
        }
    }
}

void print_map(InputStructure const& input,
               std::unordered_set<position> const& visited) {

    for (int y = 0; y < input.height; y++) {
        for (int x = 0; x < input.width; x++) {
            position p {x, y};

            if (input.obstacles.find(p) != input.obstacles.end()) {
                std::cout << "#";
            }
            else if (visited.find(p) != visited.end()) {
                std::cout << "X";
            }
            else {
                std::cout << ".";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    std::ifstream file("../map.txt");

    if (!file) return 1;

    InputStructure input = read_input(file);

    WalkResult result = simulate_walk(input);

    std::cout << "Final position: " << result.final_position << "\n";
    std::cout << "Steps: " << result.steps_taken << "\n";
    std::cout << "Visited: " << result.visited_positions.size() << "\n\n";

    print_map(input, result.visited_positions);

    return 0;
}