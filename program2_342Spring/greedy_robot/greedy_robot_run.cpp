/*
GREEDY ROBOT BY DAVID KIM - DIMPSEY 342
Assuming all 5 inputs are integers and no error conditions as inputs
*/

#include "greedy_robot.h"

int main(int argc, char** argv)
{

int max_distance = stoi(argv[1]);
int robot_x = stoi(argv[2]);
int robot_y = stoi(argv[3]);
int treasure_x = stoi(argv[4]);
int treasure_y = stoi(argv[5]);

GreedyRobot robot;
vector<string> paths;

robot.FindPaths(max_distance, {robot_x, robot_y},{treasure_x, treasure_y}, "", paths, 0);
cout << "Number of paths: " << paths.size() << endl;
return 0;


}
