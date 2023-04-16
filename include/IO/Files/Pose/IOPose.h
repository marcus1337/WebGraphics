#ifndef IO_POSE_H
#define IO_POSE_H
#include <string>
#include <vector>

class IOPose {

public:
    void loadAnimations(std::vector<std::string> colladaFilePaths, std::vector<std::string> colladaNames);

};

#endif // !IO_POSE_H
