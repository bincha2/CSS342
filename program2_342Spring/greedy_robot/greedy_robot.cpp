#include "greedy_robot.h"

void GreedyRobot::FindPaths(int max_distance, Cord robot, Cord treasure, string path_so_far, vector<string>& paths, int dir_count)
{
    // Base case
    if (robot.x == treasure.x && robot.y == treasure.y) 
    {
        paths.push_back(path_so_far);
        cout << path_so_far << endl;
        return;
    }

    // Moving east
    if (robot.x < treasure.x && (dir_count < max_distance || path_so_far.empty() || path_so_far.back() != 'E'))
    {
        if (path_so_far.empty() || path_so_far.back() != 'E') 
        {
            FindPaths(max_distance, {robot.x + 1, robot.y}, treasure, path_so_far + "E", paths, 1);
        } 
        else 
        {
            FindPaths(max_distance, {robot.x + 1, robot.y}, treasure, path_so_far + "E", paths, dir_count + 1);
        }
    }

    // Moving west
    if (robot.x > treasure.x && (dir_count < max_distance || path_so_far.empty() || path_so_far.back() != 'W'))
    {
        if (path_so_far.empty() || path_so_far.back() != 'W')
        {
            FindPaths(max_distance, {robot.x - 1, robot.y}, treasure, path_so_far + "W", paths, 1);
        } 
        else 
        {
            FindPaths(max_distance, {robot.x - 1, robot.y}, treasure, path_so_far + "W", paths, dir_count + 1);
        }
    }

    // Moving north
    if (robot.y < treasure.y && (dir_count < max_distance || path_so_far.empty() || path_so_far.back() != 'N'))
    {
        if (path_so_far.empty() || path_so_far.back() != 'N') 
        {
            FindPaths(max_distance, {robot.x, robot.y + 1}, treasure, path_so_far + "N", paths, 1);
        } 
        else 
        {
            FindPaths(max_distance, {robot.x, robot.y + 1}, treasure, path_so_far + "N", paths, dir_count + 1);
        }
    }

    // Moving south
    if (robot.y > treasure.y && (dir_count < max_distance || path_so_far.empty() || path_so_far.back() != 'S'))
    {
        if (path_so_far.empty() || path_so_far.back() != 'S') 
        {
            FindPaths(max_distance, {robot.x, robot.y - 1}, treasure, path_so_far + "S", paths, 1);
        } 
        else 
        {
            FindPaths(max_distance, {robot.x, robot.y - 1}, treasure, path_so_far + "S", paths, dir_count + 1);
        }
    }
}