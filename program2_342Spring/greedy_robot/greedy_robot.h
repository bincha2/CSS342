#ifndef GREEDY_ROBOT_H_
#define GREEDY_ROBOT_H_
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

typedef struct
{
    int x;
    int y;
} Cord;

class GreedyRobot
{
    public:
    void FindPaths(int max_distance, Cord robot, Cord treasure, string path_so_far, vector<string>& paths, int dir_count);
};
#endif

