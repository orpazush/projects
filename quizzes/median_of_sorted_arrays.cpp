//
// Created by orpaz on 13/01/2021.
//

#include <cstddef>  //size_t
#include <vector>   //vector
#include <iostream>

double MedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
{
    size_t median = (nums1.size() + nums2.size()) / 2;
    bool isOdd = (nums1.size() + nums2.size()) % 2;
    int lastSmallerNum = 0;
    int result = 0;

    int *currNum1 = &nums1[0];
    int *currNum2 = &nums2[0];
    int *endOfNum1 = currNum1 + nums1.size();
    int *endOfNum2 = currNum2 + nums2.size();
    size_t i = 0;

    for (i = 0; i < median; ++i)
    {
        if (currNum1 == endOfNum1)
        {
            currNum2 += median - i;
            return (isOdd)
                   ? *(currNum2)
                   : (double)(*currNum2 + *(currNum2-1))/2;
        }

        if (currNum2 == endOfNum2)
        {
            currNum1 += median - i;
            return (isOdd)
                   ? *(currNum1)
                   : (double)(*currNum1 + *(currNum1-1))/2;
        }

        if (*currNum1 < *currNum2)
        {
            lastSmallerNum = *currNum1;
            ++currNum1;
        }
        else
        {
            lastSmallerNum = *currNum2;
            ++currNum2;
        }
    }
    if (currNum1 == endOfNum1)
    {
        result = *currNum2;
    }
    else if (currNum2 == endOfNum2)
    {
        result = *currNum1;
    }
    else
    {
        result = (*currNum1 < *currNum2) ? *currNum1 : *currNum2;
    }

    return (isOdd) ? result : (double)(result + lastSmallerNum)/2;
}

int main()
{
    std::vector<int> nums1 = {1, 2};
    std::vector<int> nums2 = {3, 4};

    std::cout << MedianSortedArrays(nums1, nums2) << std::endl;

    std::vector<int> nums11 = {1, 2, 3};
    std::vector<int> nums22 = {4, 5};

    std::cout << MedianSortedArrays(nums11, nums22) << std::endl;

    std::vector<int> nums111 = {1};
    std::vector<int> nums222 = {2, 3, 4, 5};

    std::cout << MedianSortedArrays(nums111, nums222) << std::endl;

    std::vector<int> nums1111 = {1};
    std::vector<int> nums2222 = {2, 3, 4, 5, 6};

    std::cout << MedianSortedArrays(nums1111, nums2222) << std::endl;

    std::vector<int> nums3 = {};
    std::vector<int> nums4 = {1};

    std::cout << MedianSortedArrays(nums3, nums4) << std::endl;

    double check = (double)(3+4)/2;
    std::cout << check << std::endl;


    return 0;
}