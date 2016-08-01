#include "draganalysis.h"

bool DragAnalysis::analysis(int width, int height, QPoint start, QPoint end, int angle, std::pair<int, Rotate> *rotate)
{
    int dx = qAbs(end.x()-start.x());
    int dy = qAbs(end.y()-start.y());

    if (dx<width/min_diff && dy<height/min_diff)
        return false;

    if (dx-dy > 0) //up or down
    {
        if (start.y() < height/2 && end.y()<height/2) //up
        {
            if (end.x() > start.x())
                *rotate = std::make_pair(p_up, Rotate::Anti_Clock);
            else
                *rotate = std::make_pair(p_up, Rotate::Clock_Wise);

            return true;
        }
        else if (start.y() > height/2 && end.y() > height/2) //down
        {
            if (end.x() > start.x())
                *rotate = std::make_pair(p_down, Rotate::Anti_Clock);
            else
                *rotate = std::make_pair(p_down, Rotate::Clock_Wise);

            return true;
        }
        else
            return false;
    }
    else // left or right
    {
        int frontplanr = getFrontPlanr(angle);
        if (start.x()<width/2 && end.x()<width/2) //left
        {
//            int leftplanr = getNextPlanr(frontplanr, -1);
            int leftplanr = getNextPlanr(frontplanr, -1+horizontal_order_size);
            if (end.y()>start.y())
                *rotate = std::make_pair(leftplanr, Rotate::Clock_Wise);
            else
                *rotate = std::make_pair(leftplanr, Rotate::Anti_Clock);

            return true;
        }
        else if (start.x()>width/2 && end.x()>width/2) //right
        {
            int rightplanr = getNextPlanr(frontplanr, 1);
            if (end.y()>start.y())
                *rotate = std::make_pair(rightplanr, Rotate::Anti_Clock);
            else
                *rotate = std::make_pair(rightplanr, Rotate::Clock_Wise);
            return true;
        }
        else
            return false;
    }

    return false;
}

int DragAnalysis::getFrontPlanr(int angle)
{
    if (180-45<angle && angle<=180+45)
        return p_right;

    if (90-45<angle && angle<=90+45)
        return p_back;

    if (270-45<angle && angle<=270+45)
        return p_front;

    return p_left;
}

int DragAnalysis::getNextPlanr(int planr, int right)
{
    assert(0<=planr && planr<cube_planr_size);
    int index = horizontal_order_map[planr];
    index+=right;
    index %= horizontal_order_size;
//    if (index<0)
//        index+=horizontal_order_size;
    return horizontal_order[index];
}
