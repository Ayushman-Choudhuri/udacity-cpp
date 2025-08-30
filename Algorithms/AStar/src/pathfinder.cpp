#include "astar/pathfinder.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace astar {

    bool Pathfinder::FindPath(Map& map, const Point& start, const Point& goal){

        path_.clear();

        if (!map.IsEmpty(start.x , start.y) || !map.IsEmpty(goal.x , goal.y)){

            std::cerr<< "Error: Start or goal position is not empty!" << std::endl;
            return false;
        }

        //initialization
        std::vector<Node> open_list;    
        int h = CalculateHeuristic(start, goal);
        AddToOpenList(start, 0, h, map, open_list);

        //search loop
        while(!open_list.empty()) {

            SortOpenList(open_list);
            Node current_node = open_list.back(); //get node with lowest f-score
            open_list.pop_back();

            map.SetState(current_node.position.x, current_node.position.y, State::kPath);

            if(current_node.position == goal){
                return true;
            }

            ExpandNeighbors(current_node, goal, map, open_list);
        }

        std::cout << "No Path Found" << std::endl;
        
        return false;

    }

        

    int Pathfinder::CalculateHeuristic(const Point& source, const Point& goal) const {

        return std::abs(source.x - goal.x) + std::abs(source.y - goal.y);
    }

    void Pathfinder::AddToOpenList(const Point& position, int g_cost, int h_cost, 
                                    Map& map, std::vector<Node>& open_list){

        open_list.emplace_back(position.x, position.y, g_cost, h_cost); //more efficient than creating a new node and using push_back
        map.SetState(position.x, position.y, State::kClosed);

    }

    void Pathfinder::ExpandNeighbors(const Node& current, const Point& goal,
                                    Map& map, std::vector<Node>& open_list){
        for (const auto& direction : kDirections) {
            int new_x = current.position.x + direction[0];
            int new_y = current.position.y + direction[1];
            
            if (map.IsEmpty(new_x, new_y)) {
                int g = current.g + 1;
                int h = CalculateHeuristic(Point(new_x, new_y), goal);
                AddToOpenList(Point(new_x, new_y), g, h, map, open_list);
            }
    
        }
    }

    void Pathfinder::SortOpenList(std::vector<Node>& open_list) const {
    std::sort(open_list.begin(), open_list.end(),
              [](const Node& a, const Node& b) {
                  return a.f() < b.f(); // Lowest f() values at the end
              });
    }


}

