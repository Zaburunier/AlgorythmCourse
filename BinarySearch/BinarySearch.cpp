#include <iostream>

void GetArray(int &length, int *&_array) {
    scanf_s("%d%*c", &length);
    _array = new int[length];
    for (int i = 0; i < length; i = i + 1) {
        scanf_s("%d%*c", &_array[i]);
    }
    /*for (int i = 0; i < length; i = i + 1) {
        printf("%d ", _array[i]);
    }*/
}

int BinarySearch(int key, int* _array, int length) {
    // Границы массива на текущей итерации
    int leftEnd = 0, rightEnd = length - 1;
    int centre;
    while (leftEnd <= rightEnd) {
        centre = leftEnd + 0.5 * (rightEnd - leftEnd);
        if (_array[centre] == key) {
            return centre;
        } else if (_array[centre] < key) {
            leftEnd = centre + 1;
        } else {
            rightEnd = centre - 1;
        }
    }
    return -1;
}

int main()
{
    int arrayLength, keyLength;
    int *nums, *keys;
    GetArray(arrayLength, nums);
    GetArray(keyLength, keys);
    int *returnedIndexes = new int[keyLength];
    for (int i = 0; i < keyLength; i = i + 1) {
        printf("%d ", BinarySearch(keys[i], nums, arrayLength));
    }
}



