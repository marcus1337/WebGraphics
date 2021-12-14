
#include <vector>


#ifndef ASPECTRATIO_H
#define ASPECTRATIO_H

class AspectRatio{

    std::vector<int> widths;
    std::vector<int> heights;
    std::vector<int64_t> areas;
    int index = 0;
    int maxWidth();
    int minWidth();
    int maxHeight();
    int minHeight();
    int64_t maxArea();
    int64_t minArea();
    void setIndexToMax();

public:
    AspectRatio();

    int getWidth();
    int getHeight();

    void increase();
    void decrease();
    void setIndexToClosestAspectRatio(int width, int height);
};


#endif

