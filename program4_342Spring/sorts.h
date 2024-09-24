// Program 4 342 Spring Dimpsey - David H. Kim
#ifndef SORTS_H_
#define SORTS_H_
#include <vector>
#include <cmath>
using namespace std;

void InsertionSort(vector<int> &vec, int first, int last)
{
    int size = last - first + 1;

    for (int i = 1; i < size; i++)
    {
        int temp = vec[i];
        int j = i;
        while ((j > 0) && (vec[j - 1] > temp))
        {
            vec[j] = vec[j - 1];
            j--;
        }
        vec[j] = temp;
    }
}

void BubbleSort(vector<int> &vec, int first, int last)
{
    int size = last - first + 1;

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (vec[j] > vec[j + 1])
            {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

void ShellSort(vector<int> &vec, int first, int last)
{
    int size = last - first + 1;

    // sort through using gap size iterations
    for (int gap = (size / 2); gap > 0; gap = (gap == 2) ? 1 : int(gap / 2.2))
    {
        for (int i = gap; i < size; i++)
        {
            int tmp = vec[i];
            int j = i;
            for (; (j >= gap) && (tmp < vec[j - gap]); j -= gap)
            {
                vec[j] = vec[j - gap];
            }
            vec[j] = tmp;
        }
    }
}

void Merge(vector<int> &vec, int first, int mid, int last)
{
    // create size variable using indices
    int size = last - first + 1;

    // tmp_arr ptr to store sorted values
    int *tmp_arr;
    tmp_arr = new int[size];

    // assign first half and second half indices to make iteration easier
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = 0;

    // iterate through array comparing first half and second half
    while ((first1 <= last1) && (first2 <= last2))
    {
        if (vec[first1] < vec[first2])
        {
            tmp_arr[index] = vec[first1];
            first1++;
        }
        else
        {
            tmp_arr[index] = vec[first2];
            first2++;
        }
        index++;
    }

    // add remaining values to tmp_arr
    while (first1 <= last1)
    {
        tmp_arr[index] = vec[first1];
        first1++;
        index++;
    }

    while (first2 <= last2)
    {
        tmp_arr[index] = vec[first2];
        first2++;
        index++;
    }

    // now add sorted tmp_arr back into the original array
    for (index = 0; index < size; index++)
    {
        vec[first] = tmp_arr[index];
        first++;
    }

    // deallocate tmp_arr so there are no memory leaks
    delete[] tmp_arr;
}

void MergeSort(vector<int> &vec, int first, int last)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        MergeSort(vec, first, mid);
        MergeSort(vec, mid + 1, last);
        Merge(vec, first, mid, last);
    }
}

void IterativeMergeSort(vector<int> &vec, int first, int last)
{
    // Function allocates only one additional vector each time for loop operations as Merge() allocates & deallocates vector<int> tmp once it reaches out of scope
    int size = last - first + 1;
    int width;

    // bottom-up non-recursive approach using sub-array widths doubling each time 1,2,4,8,16...
    for (width = 1; width < size; width = 2 * width)
    {
        for (int i = first; i < last; i = i + 2 * width)
        {
            int left = i;
            int mid = min(i + width - 1, last);
            int right = min(i + 2 * width - 1, last);
            Merge(vec, left, mid, right); // merge the sub-arrays for each loop calling Merge()
        }
    }
}

// helper function for the quicksort using efficient pivot algorithm
int Partition(vector<int> &vec, int first, int last)
{
    int pivot = vec[last];
    int i = first - 1;

    for (int j = first; j < last; j++)
    {
        if (vec[j] <= pivot)
        {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[last]);
    return i + 1;
}

void QuickSort(vector<int> &vec, int first, int last)
{
    if (first < last)
    {
        int pivot = Partition(vec, first, last);
        QuickSort(vec, first, pivot - 1);
        QuickSort(vec, pivot + 1, last);
    }
}

#endif