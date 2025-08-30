#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>

enum class State {kEmpty, kObstacle, kClosed, kPath};

std::vector<State> ParseLine(const std::string &line){
    std::istringstream sline(line);
    int state;
    char delimiter;
    std::vector<State> row;

    while(sline >> state >> delimiter && delimiter == ',') {
        if(state == 0) {
            row.push_back(State::kEmpty);
        } else {
            row.push_back(State::kObstacle);
        }
    }
    return row;
}

void PrintBoard(const std::vector<std::vector<State>> &board){
    for(auto row : board) {
        for(auto col : row) {
            if(col == State::kEmpty) {
                std::cout << "0 ";
            } else if(col == State::kObstacle) {
                std::cout << "1 ";
            } else if(col == State::kPath) {
                std::cout << "* ";  // Or use "*" or "P"
            } else if(col == State::kClosed) {
                std::cout << "x ";
            }
        }
        std::cout << std::endl;
    }
}

int Heuristic(int x1, int y1, int x2, int y2){
    return abs(x2 - x1) + abs(y2 - y1);
}

void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<State>> &gridMap, std::vector<std::vector<int>> &openList){
    
    std::vector<int> node = {x,y,g,h};
    openList.push_back(node);
    gridMap[x][y] = State::kClosed;
}

std::vector<std::vector<State>> ReadBoardFile(const std::string &path){
    std::ifstream boardFile(path);
    std::vector<std::vector<State>> board{};

    if(boardFile) {
        std::string line;
        while(std::getline(boardFile, line)) {
            std::vector<State> row = ParseLine(line);
            board.push_back(row);
        } 
    }
    return board;
}

bool Compare(const std::vector<int> node1, const std::vector<int> node2){
    int f1 = node1[2] + node1[3];
    int f2 = node2[2] + node2[3];
    return f1 > f2;
}

bool CheckValidCell(int x, int y, const std::vector<std::vector<State>> &gridMap){
    
    bool onGridX = (x>=0 && x<gridMap.size());
    bool onGridY = (y>=0 && y<gridMap[0].size());
    if(onGridX && onGridY)
        return gridMap[x][y] == State::kEmpty;
    return false;
}

void CellSort(std::vector<std::vector<int>> *v) {
    std::sort(v->begin(), v->end(), Compare);
}

void ExpandNeighbors(std::vector<int> currentNode, const int goal[2], std::vector<std::vector<State>> &gridMap, std::vector<std::vector<int>> &openList) {
    
    int xCurrent = currentNode[0];
    int yCurrent = currentNode[1];
    int gCurrent = currentNode[2];

    const int directionalDeltas[4][2] = {{-1,0}, {0,-1}, {1,0}, {0,1}};

    for (auto delta : directionalDeltas){
        int xNeighbor  = xCurrent + delta[0];
        int yNeighbor  = yCurrent + delta[1];

        if(CheckValidCell(xNeighbor, yNeighbor, gridMap)){
            int gNeighbor = gCurrent + 1;
            int hNeighbor = Heuristic(xNeighbor, yNeighbor, goal[0], goal[1]);
            AddToOpen(xNeighbor, yNeighbor, gNeighbor, hNeighbor, gridMap, openList);
        }
    }

}

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> &gridMap, const int start[2], const int goal[2]) {
    std::vector<std::vector<int>> openList{};

    int startX = start[0];
    int startY = start[1];
    int g = 0;
    int h = Heuristic(startX, startY, goal[0], goal[1]);

    AddToOpen(startX, startY, g, h, gridMap, openList);

    while(!openList.empty()) {

        CellSort(&openList);
        auto currentNode = openList.back();
        openList.pop_back();

        int x = currentNode[0];
        int y = currentNode[1];
        gridMap[x][y] = State::kPath;
        if(x == goal[0] && y == goal[1]) {
            return gridMap;
        }
        ExpandNeighbors(currentNode, goal, gridMap, openList);
    }

    std::cout << "No path found!" << std::endl;
    return std::vector<std::vector<State>>{};
}

int main() {

    
    int start[] = {0,0};
    int goal[] = {8,10};

    auto map = ReadBoardFile("map.txt");
    PrintBoard(map);
    printf("\n");
    std::vector<std::vector<State>> solution = Search(map,start, goal);
    PrintBoard(solution);
}