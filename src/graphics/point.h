#ifndef SRC_GRAPHICS_POINT_H
#define SRC_GRAPHICS_POINT_H

struct Point {
    Point() = default;

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    int x, y;
};

#endif // SRC_GRAPHICS_POINT_H