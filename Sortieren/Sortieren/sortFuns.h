#pragma once

#include <iterator>
#include <algorithm>

template<typename RAIter>
bool compare(const RAIter a, const RAIter b) {

    typename std::iterator_traits<RAIter>::value_type tmpa = *a;
    typename std::iterator_traits<RAIter>::value_type tmpb = *b;
    return (tmpa < tmpb);

};


template<typename RAIter>
void swap(RAIter a, RAIter b)
{
    typename std::iterator_traits<RAIter>::value_type t = *a;
    *a = *b;
    *b = t;
}

template<typename RAIter> void shell_sort(RAIter first, RAIter last, bool comp(const RAIter a, const RAIter b) = compare ) {
	
    int n = last - first;
   
    int gap, j, k;
    for (gap = n / 2; gap > 0; gap = gap / 2) {        //initially gap = n/2,

        for (j = gap; j < n; j++) {
            for (k = j - gap; k >= 0; k -= gap) {
                if (comp(first+(k + gap), (first+k)))
                    break;
                else
                    swap((first + (k + gap)), (first + k)); 
            }
        }
    }

};


template<typename RAIter>
int partition(RAIter arr, int low, int high, bool comp(const RAIter a, const RAIter b))
{
    typename std::iterator_traits<RAIter>::value_type pivot = *(arr+high);    // pivot 
    int i = (low-1);  // Index of smaller element 
    for (int j = low; j < high; j++)
    {
        // If current element is smaller than or 
        // equal to pivot change to bigger to sort from highest to lowest

        if (comp((arr + high), (arr + j)))
        {
            i++;    // increment index of smaller element 
            swap(arr+i, arr+j);
        }
    }
    swap(arr+(i+1) , arr+high);
    return (i + 1);
}

template<typename RAIter>
void intern_quickSort(RAIter arr, int low, int high,bool comp(const RAIter a, const RAIter b))
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high,comp);

        // Separately sort elements before 
        // partition and after partition 
        intern_quickSort(arr, low, pi - 1,comp);
        intern_quickSort(arr, pi + 1, high,comp);
    }
}

template<typename RAIter> void quick_sort(RAIter first, RAIter last, bool comp(const RAIter a, const RAIter b) = compare) {

    intern_quickSort(first, 0, last - first-1,comp);
};


