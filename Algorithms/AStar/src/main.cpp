#include <iostream>
#include "astar/map.hpp"
#include "astar/pathfinder.hpp"

int main() {

    try{
            astar::Map map;
            if(!map.LoadFromFile("map.txt")){
                std::cerr << "Failed to load map file!" <<std::endl ;
                return 1;
            }

        std::cout << "Map loaded successfully.." << std::endl;
        map.Print();
        std::cout<<std::endl;

        astar::Point start(0, 0);
        astar::Point goal(0, 1);
        
        // Create pathfinder and find path
        astar::Pathfinder pathfinder;

        if (pathfinder.FindPath(map, start, goal)) {
            std::cout << "Path found!" << std::endl;
            std::cout << "Solution Board:" << std::endl;
            map.Print();
        } else {
            std::cout << "No path exists between start and goal!" << std::endl;
        }

        } catch (const std::exception& e){
            std::cerr << "Error: " << e.what() <<std::endl ;
            return 1;
        }

    return 0;
}

