#include "astar/map.hpp"
#include <fstream>
#include<iostream>
#include<sstream>

namespace astar {

bool Map::LoadFromFile(const std::string &filepath){  

    std::ifstream file{filepath};
    if(!file.is_open()){
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return false;
    };

    grid_.clear();
    std::string line;
    while(std::getline(file, line)){
        std::vector<State> row = ParseLine(line);
        if(!row.empty()){
            grid_.push_back(row);
        }
    }

    return !grid_.empty();
}

std::vector<State> Map::ParseLine(const std::string& line){
    std::istringstream stream(line);
    std::vector<State> row;
    int state;
    char delimiter;

    while (stream >> state >> delimiter && delimiter == ','){
        row.push_back(state == 0 ? State::kEmpty : State::kObstacle);
    }

    return row;

}

void Map::Print() const{

    std::cout<<std::endl;
    for(const auto& row: grid_){
        for( const auto& cell: row){
            switch(cell){
                case State::kEmpty:
                    std::cout<<"0 ";
                    break;
                case State::kObstacle:
                    std::cout<<"1 ";
                    break;
                case State::kPath:
                    std::cout << "* ";
                    break;
                case State::kStart:
                    std::cout << "S ";
                    break;
                case State::kGoal:
                    std::cout << "G ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

State Map::GetState(int x, int y) const {
    if(IsValidCell(x,y)) {
        return grid_[x][y];
    }
    return State::kObstacle;
}

void Map::SetState(int x , int y, State state) {
    if(IsValidCell(x,y)) {
        grid_[x][y] = state;
    }
}

bool Map::IsValidCell(int x , int y) const {

    return x >= 0 && x < static_cast<int>(grid_.size())  &&
           y >= 0 && y < static_cast<int>(grid_.size());

}

bool Map::IsEmpty(int x , int y) const {
    return IsValidCell(x,y) && grid_[x][y] == State::kEmpty;
}

size_t Map::GetRows() const {
    return grid_.size();
}

size_t Map::GetCols() const {
    return grid_.empty() ? 0 : grid_[0].size();
}

std::vector<std::vector<State>>& Map::getGrid(){
    return grid_;
}


}
