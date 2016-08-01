#ifndef CIRCLE_H
#define CIRCLE_H

#include "block.h"

constexpr int circle_inner_size = 8;
constexpr int circle_outer_size = 3*4;

constexpr int step_inner = 2;
constexpr int step_outer = 3;

// the clock order is unknown
constexpr Block circle_inner[cube_planr_size][circle_inner_size] =
{
    //front
    {{0, p_front},{1, p_front},{2, p_front},{5, p_front},
     {8, p_front},{7, p_front},{6, p_front},{3, p_front}},
    //back
    {{20, p_back},{19, p_back},{18, p_back},{21, p_back},
     {24, p_back},{25, p_back},{26, p_back},{23, p_back}},
    //up
    {{18, p_up},{19, p_up},{20, p_up},{11, p_up},
     { 2, p_up},{ 1, p_up},{ 0, p_up},{ 9, p_up}},
    //down
    {{24, p_down},{25, p_down},{26, p_down},{17, p_down},
     { 8, p_down},{ 7, p_down},{ 6, p_down},{ 15, p_down}},
    //left
    {{18, p_left},{ 9, p_left},{ 0, p_left},{ 3, p_left},
     { 6, p_left},{15, p_left},{24, p_left},{21, p_left}},
    //right
    {{ 2, p_right},{11, p_right},{20, p_right},{23, p_right},
     {26, p_right},{17, p_right},{ 8, p_right},{5, p_right}}
};

constexpr Block circle_outer[cube_planr_size][circle_outer_size] =
{
    //front
    {{0, p_up},{1, p_up},{2, p_up},
     {2, p_right},{5, p_right},{8, p_right},
     {8, p_down},{7, p_down},{6, p_down},
     {6, p_left},{3, p_left},{0, p_left}},
    //back
    {{20, p_up},{19, p_up},{18, p_up},
     {18, p_left},{21, p_left},{24, p_left},
     {24, p_down},{25, p_down},{26, p_down},
     {26, p_right},{23, p_right},{20, p_right}},
    //up
    {{18, p_back},{19, p_back},{20, p_back},
     {20, p_right},{11, p_right},{2, p_right},
     {2, p_front},{1, p_front},{0, p_front},
     {0, p_left},{9, p_left},{18, p_left},},
    //down
    {{24, p_back},{25, p_back},{26, p_back},
     {26, p_right},{17, p_right},{8, p_right},
     {8, p_front},{7, p_front},{6, p_front},
     {6, p_left},{15, p_left},{24, p_left},},
    //left
    {{18, p_up},{9, p_up},{0, p_up},
     {0, p_front},{3, p_front},{6, p_front},
     {6, p_down},{15, p_down},{24, p_down},
     {24, p_back},{21, p_back},{18, p_back},},
    //right
    {{2, p_up},{11, p_up},{20, p_up},
     {20, p_back},{23, p_back},{26, p_back},
     {26, p_down},{17, p_down},{8, p_down},
     {8, p_front},{5, p_front},{2, p_front},}
};

class MagicCube;

class Circle
{
public:
    Circle(int p, int s, MagicCube* m);
    void rotate(Rotate d);
private:
    const int planr;
    const int step;
    MagicCube* magic;
private:
    void circle_reverse(std::vector<Block> *vec);
};

#endif // CIRCLE_H
