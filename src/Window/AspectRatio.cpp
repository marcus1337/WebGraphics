#include "AspectRatio.h"
#include <math.h>
#include <iostream>
#include <algorithm>

AspectRatio::AspectRatio()
{
    for (int i = 640; i <= 1920; i++)
    {
        int width = i;
        widths.push_back(width);
        int height = (int)std::floor(((float)i / 16.0f) * 9.0f + 0.5f);
        heights.push_back(height);
        areas.push_back((int64_t) width * (int64_t) height);
    }
}
int AspectRatio::maxWidth()
{
    return widths[widths.size()-1];
}
int AspectRatio::minWidth()
{
    return widths[0];
}
int AspectRatio::maxHeight()
{
    return heights[heights.size()-1];
}
int AspectRatio::minHeight()
{
    return heights[0];
}

int AspectRatio::getWidth()
{
    return widths[index];
}

int AspectRatio::getHeight()
{
    return heights[index];
}

void AspectRatio::increase()
{
    index = std::min<int>(index + 1, (int)widths.size());
}
void AspectRatio::decrease()
{
    index = std::max<int>(0, index - 1);
}

void AspectRatio::setIndexToClosestAspectRatio(int width, int height)
{
    int64_t area = (int64_t) width * (int64_t) height;
    if (area >= maxArea()){
        setIndexToMax();
    } else if( area <= minArea()){
        index = 0;
    }else{
        std::vector<int64_t>::iterator it = std::upper_bound (areas.begin(), areas.end(), area);
        index = (int)(it - areas.begin()) - 1;
    }
}

void AspectRatio::setIndexToMax(){
    index = widths.size()-1;
}

int64_t AspectRatio::maxArea(){
    return (int64_t) maxWidth() * (int64_t) maxHeight();
}

int64_t AspectRatio::minArea(){
    return (int64_t) minWidth() * (int64_t) minHeight();
}