// Backpack.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct Item {
    int price;
    int volume;
    double ppv; //price per volume
};

void SortNewItem(Item**, int);

int main()
{
    int* amountOfItems = (int*)malloc(sizeof(int));
    int* capacity = (int*)malloc(sizeof(int));
    scanf("%d %d", amountOfItems, capacity);
    Item* items = (Item*)malloc(*amountOfItems * sizeof(Item));
    for (int i = 0; i < *amountOfItems; i++) {
        scanf("%d %d", &items[i].price, &items[i].volume);
        items[i].ppv = (double) items[i].price / items[i].volume;
        SortNewItem(&items, i);
    }

    double* takenPrice = (double*)malloc(sizeof(double));
    double* takenVolume = (double*)malloc(sizeof(double));
    *takenPrice = 0;
    *takenVolume = 0;
    for (int i = 0; i < *amountOfItems; i++) {
        if (*takenVolume < *capacity) {
            if (*capacity - *takenVolume > items[i].volume) {
                *takenPrice += items[i].price;
                *takenVolume += items[i].volume;
            } else {
                *takenPrice += (double)(*capacity - *takenVolume) * items[i].ppv;
                break;
            }
        }
    }

    printf("%5.3f", *takenPrice);


    return 0;
}

void SortNewItem(Item** items, int lastIndex) {
    Item* itemArray = *items;
    if (lastIndex == 0) return;
    int i = lastIndex;
    int currentIndex = lastIndex;
    while (--i >= 0 && itemArray[currentIndex].ppv > itemArray[i].ppv) {
        Item temp = itemArray[currentIndex];
        itemArray[currentIndex] = itemArray[i];
        itemArray[i] = temp;
        currentIndex = i;
    }

}