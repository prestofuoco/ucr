#include "minFunc.h"
const int * min (const int arr[], int arrSize) {
    if (arrSize == 0) {
        return nullptr;
    }
    if (arrSize == 1) {
        return &arr[0];
    }
    const int* minLoc = min(arr, arrSize - 1);
    if (arr[arrSize - 1] > *minLoc) {
        return minLoc;
    }
    return &arr[arrSize - 1];
}