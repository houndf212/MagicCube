#ifndef DEFINE_H
#define DEFINE_H


#include "vertex.h"

constexpr GLfloat cube_len = 0.4f;
constexpr GLfloat cube_half_len = 0.197f;
constexpr int cube_planr_size = 6;
constexpr int surface_cube_size = 9;
constexpr int planr_vertex_size = 6;

constexpr int magic_vertex_size = 9*surface_cube_size*planr_vertex_size;

//////////////////////////  R  G  B
constexpr Color col_O(250/255.0f, 128/255.0f, 10/255.0f);
constexpr Color col_R(1, 0, 0);
constexpr Color col_Y(1, 1, 0);
constexpr Color col_B(0, 0, 1);
constexpr Color col_W(1, 1, 1);
constexpr Color col_G(0, 1, 0);

//constexpr Color col_front = col_O;
//constexpr Color col_back = col_R;
//constexpr Color col_up = col_Y;
//constexpr Color col_down = col_W;
//constexpr Color col_left = col_B;
//constexpr Color col_right = col_G;

constexpr Color col_front = col_B;
constexpr Color col_back = col_G;
constexpr Color col_up = col_Y;
constexpr Color col_down = col_W;
constexpr Color col_left = col_O;
constexpr Color col_right = col_R;

constexpr Color planr_colors[cube_planr_size] =
{
    col_front, // front
    col_back, // back
    col_up, // up
    col_down, // left
    col_left, // down
    col_right  // right
};

constexpr int p_front = 0;
constexpr int p_back = 1;
constexpr int p_up = 2;
constexpr int p_down = 3;
constexpr int p_left = 4;
constexpr int p_right = 5;

constexpr Vertex p0(-cube_half_len, cube_half_len, cube_half_len);
constexpr Vertex p1(-cube_half_len, -cube_half_len, cube_half_len);
constexpr Vertex p2(cube_half_len, -cube_half_len, cube_half_len);
constexpr Vertex p3(cube_half_len, cube_half_len, cube_half_len);

constexpr Vertex p4(-cube_half_len, cube_half_len, -cube_half_len);
constexpr Vertex p5(-cube_half_len, -cube_half_len, -cube_half_len);
constexpr Vertex p6(cube_half_len, -cube_half_len, -cube_half_len);
constexpr Vertex p7(cube_half_len, cube_half_len, -cube_half_len);

constexpr Vertex cube_vertices[cube_planr_size][planr_vertex_size] =
{
    {p0, p1, p2, p2, p3, p0}, //front
    {p4, p5, p6, p6, p7, p4}, //back
    {p4, p0, p3, p3, p7, p4}, //up
    {p5, p1, p2, p2, p6, p5}, //down
    {p0, p1, p5, p5, p4, p0}, //left
    {p3, p2, p6, p6, p7, p3}  //right
};

enum class Rotate
{
    Clock_Wise = -1,
    Anti_Clock = 1,
};

#endif // DEFINE_H
