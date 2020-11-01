// HuffmanDecoding.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct Huffman {
    char letter;
    char* code;
};

char CheckForPresence(Huffman*, int, char*);
void ClearBuffer(char**);
int main()
{
    // Получение информации о строке
    int amount, length;
    scanf("%d %d", &amount, &length);
    getchar();
    Huffman* codes = new Huffman[amount];

    // Получение кодов
    for (int i = 0; i < amount; i = i + 1) {
        codes[i].code = new char[8];
        for (int j = 0; j < 8; j = j + 1)
            codes[i].code[j] = 0;
        scanf("%c: ", &codes[i].letter);
        char current;
        scanf("%c", &current);
        int index = 0;
        while (current == 48 || current == 49) {
            codes[i].code[index] = current;
            index = index + 1;
            scanf("%c", &current);
        }
    }

    // Получение и анализ закодированной строки
    char* decodedString = nullptr;
    char* buffer = new char[8];
    ClearBuffer(&buffer);
    int counter = 0, charCounter = 0, currentIndex = 0;
    while (counter < length) {
        counter = counter + 1;
        scanf("%c", &buffer[currentIndex]);
        currentIndex = currentIndex + 1;
        char c;
        if ((c = CheckForPresence(codes, amount, buffer)) != 0) {
            ClearBuffer(&buffer);
            charCounter = charCounter + 1;
            currentIndex = 0;
            char* newStr = new char[charCounter];
            for (int k = 0; k < charCounter - 1; k = k + 1)
                newStr[k] = decodedString[k];
            newStr[charCounter - 1] = c;
            decodedString = newStr;
        }
    }
    for (int i = 0; i < charCounter; i = i + 1) {
        printf("%c", decodedString[i]);
    }
}

char CheckForPresence(Huffman* codes, int c_length, char* sequence) {
    char ch = 0;
    bool found;
    for (int i = 0; i < c_length; i = i + 1) {
        found = true;
        for (int j = 0; j < 8; j = j + 1) {
            if (codes[i].code[j] != sequence[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            ch = codes[i].letter;
            break;
        }
    }

    return ch;
}

void ClearBuffer(char** buf) {
    char* buffer = *buf;
    for (int i = 0; i < 8; i = i + 1)
        buffer[i] = 0;
}