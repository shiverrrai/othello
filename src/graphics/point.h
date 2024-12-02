#ifndef SRC_GRAPHICS_POINT_H
#define SRC_GRAPHICS_POINT_H

struct Point {
    Point() = default;

    Point(int x, int y) :
        x_(x), y_(y) {}

    int x_, y_;
};

#endif // SRC_GRAPHICS_POINT_H