#ifndef ASTAR_PATHFINDER_H
#define ASTAR_PATHFINDER_H

#include <vector>
#include "types.hpp"
#include "map.hpp"

namespace astar{

class Pathfinder {
public: 
    Pathfinder() = default;

    bool FindPath(Map& map, const Point& start, const Point& goal);

    std::vector<Point> GetPath() const {return path_;}

private: 

    std::vector<Point> path_ ;

    int CalculateHeuristic(const Point& source, const Point& goal) const;

    void AddToOpenList(const Point& position, int g_cost , int h_cost, 
                        Map& map, std::vector<Node>& open_list);
    
    void ExpandNeighbors(const Node& current , const Point& goal,
                        Map& map, std::vector<Node>& open_list);

    void SortOpenList(std::vector<Node>& open_list) const; //this is const as it does not modify the state of the pathfinder object itself
                                                           //This modifies the open_list parameter which is passed by reference from the outside

    static constexpr int kDirections[4][2] = {{-1,0}, {0,-1},{1,0},{0,1}};   
};

}

#endif