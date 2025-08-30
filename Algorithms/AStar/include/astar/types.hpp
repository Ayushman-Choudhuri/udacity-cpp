#ifndef ASTAR_TYPE_HPP
#define ASTAR_TYPE_HPP

namespace astar {

enum class State {
    kEmpty,
    kObstacle,
    kClosed,
    kPath,
    kStart,
    kGoal
};


struct Point {
    int x;
    int y;

    Point(int x = 0, int y = 0): x(x) , y(y) {}

    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }
};

struct Node {
    Point position;
    int g;
    int h;

    Node(int x , int y, int g_cost , int h_cost)
        : position(x, y), g(g_cost), h(h_cost) {}

    int f() const { return g + h; }

};

}

#endif