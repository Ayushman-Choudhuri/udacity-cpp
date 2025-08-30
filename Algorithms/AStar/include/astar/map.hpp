#ifndef ASTAR_BOARD_HPP
#define ASTAR_BOARD_HPP

#include <vector>
#include <string>
#include "astar/types.hpp"

namespace astar {

class Map {

public:
    Map() = default;

    bool LoadFromFile(const std::string& filepath);

    void Print() const;

    State GetState(int x, int y) const;
    void SetState(int x, int y, State state);

    bool IsValidCell(int x, int y) const;
    bool IsEmpty(int x, int y) const; 

    size_t GetRows() const; //can be optimized with inline optimization
    size_t GetCols() const; //can be optimized with inline optimization

    std::vector<std::vector<State>>& getGrid(); //can be optimized with inline optimization

private: 
    std::vector<std::vector<State>> grid_;

    std::vector<State> ParseLine(const std::string& line);
};

}

#endif