#ifndef DRAGANALYSIS_H
#define DRAGANALYSIS_H

#include "define.h"
#include <QPoint>

constexpr int horizontal_order_size = 4;
constexpr int horizontal_order[horizontal_order_size] =
{
    p_front,
    p_right,
    p_back,
    p_left
};

constexpr int horizontal_order_map[cube_planr_size]
{
    0, //front
    2, //back
    0, //up
    0, //down
    3, //left
    1, //right
};

class DragAnalysis
{
public:
    static bool analysis(int width, int height, QPoint start, QPoint end, int angle, std::pair<int, Rotate> *rotate);
    static int getFrontPlanr(int angle);
private:
    static int getNextPlanr(int planr, int right);
    static constexpr int min_diff = 10;

};

#endif // DRAGANALYSIS_H
