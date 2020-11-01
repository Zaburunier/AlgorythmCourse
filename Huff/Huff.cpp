#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


struct Huffman;
struct Huffman {
	char ch;
	int freq;
	Huffman* next;
	Huffman* leftPrev;
	Huffman* rightPrev;
	short* code;
	short amountOfDigits;
};


bool CheckForPresence(Huffman**, char, int);
void Sort(Huffman**, int);
void HuffmanStep(Huffman**, int, int);
void SortNewElement(Huffman**, int);
void HuffmanCodes(Huffman**, int);
void AddCodes(Huffman*, Huffman*, short);
Huffman* DeleteExcessNodes(Huffman*, int&);

int main()
{
	char* string = (char*)malloc(sizeof(char));
	Huffman* list = (Huffman*)malloc(sizeof(Huffman));
	char currentChar = 0;
	int freqCounter = 0, charCounter = 0;
	currentChar = getchar();
	while (currentChar != '\n') {
		freqCounter++;
		char* tempStr = (char*)realloc(string, freqCounter * sizeof(char));
		string = tempStr;
		string[freqCounter - 1] = currentChar;
		if (!CheckForPresence(&list, currentChar, charCounter)) {  //Если новый символ
			charCounter++;
			Huffman* temp = (Huffman*)realloc(list, charCounter * sizeof(Huffman));
			list = temp;
			list[charCounter - 1].ch = currentChar;
			list[charCounter - 1].freq = 1;
			list[charCounter - 1].leftPrev = nullptr;
			list[charCounter - 1].rightPrev = nullptr;
			list[charCounter - 1].code = (short*)malloc(8 * sizeof(short));
			list[charCounter - 1].amountOfDigits = 0;
		}
		currentChar = getchar();
	}
	Sort(&list, charCounter);

	int listCounter = charCounter;
	int stepCounter = 0;
	while (list[listCounter - 1].freq != freqCounter) {
		Huffman* _temp = (Huffman*)realloc(list, ++listCounter * sizeof(Huffman));
		list = _temp;
		HuffmanStep(&list, listCounter, stepCounter++);
		SortNewElement(&list, listCounter - 1);
	}

	AddCodes(list[listCounter - 1].leftPrev, &(list[listCounter - 1]), 0);
	AddCodes(list[listCounter - 1].rightPrev, &(list[listCounter - 1]), 1);
	list = DeleteExcessNodes(list, listCounter);


	printf("%d %d\n", charCounter, freqCounter);
	for (int i = 0; i < listCounter; i++) {
		printf("%c: ", list[i].ch);
		for (int k = 0; k < list[i].amountOfDigits; k++) printf("%d", list[i].code[k]);
		printf("\n");
	}

	for (int i = 0; i < freqCounter; i++) {
		for (int j = 0; j < listCounter; j++) {
			if (string[i] == list[j].ch) {
				for (int k = 0; k < list[j].amountOfDigits; k++) printf("%d", list[j].code[k]);
				break;
			}
		}
	}
	return 0;
}

bool CheckForPresence(Huffman** list, char ch, int count) {
	Huffman* tempList = *list;
	for (int i = 0; i < count; i++) {
		if (ch == tempList[i].ch) {  //Если нашлось совпадение
			tempList[i].freq++;
			return true;
		}
	}
	return false;
}


void Sort(Huffman** list, int count) {
	Huffman* tempList = *list;
	for (int i = 0; i < count; i++) {
		int k = i;
		int current = i;
		while (--k >= 0 && tempList[current].freq < tempList[k].freq) {
			Huffman temp = tempList[current];
			tempList[current] = tempList[k];
			tempList[k] = temp;
			current = k;
		}
	}
}

void SortNewElement(Huffman** list, int lastIndex) {
	Huffman* tempList = *list;
	int i = lastIndex;
	int currentIndex = lastIndex;
	while (--i >= 0 && tempList[currentIndex].freq < tempList[i].freq) {
		Huffman temp = tempList[currentIndex];
		tempList[currentIndex] = tempList[i];
		tempList[i] = temp;
		currentIndex = i;
	}
}

void HuffmanStep(Huffman** list, int count, int stepCount) {
	Huffman* tempList = *list;
	Huffman tempNode;
	int firstMin = 2 * stepCount, secondMin = 2 * stepCount + 1;

	tempNode.ch = 0;
	tempNode.freq = tempList[firstMin].freq + tempList[secondMin].freq;
	tempNode.leftPrev = &(tempList[firstMin]);
	tempNode.rightPrev = &(tempList[secondMin]);
	tempNode.code = (short*)malloc(8 * sizeof(short));
	tempNode.amountOfDigits = 0;
	tempList[count - 1] = tempNode;
}

void HuffmanCodes(Huffman** list, int count) {
	Huffman* tempList = *list;
	if (count == 1) {
		tempList[0].amountOfDigits = 1;
		tempList[0].code[0] = 0;
		return;
	}
	/*AddCodes(tempList[count - 1]->leftPrev, list[count - 1], 0);
	AddCodes(tempList[count - 1]->rightPrev, list[count - 1], 1);*/

}

void AddCodes(Huffman* node, Huffman* prevNode, short value) {
	Huffman* tempNode = node;
	tempNode->amountOfDigits = prevNode->amountOfDigits + 1;
	for (int i = 0; i < tempNode->amountOfDigits - 1; i++)
		tempNode->code[i] = prevNode->code[i];
	tempNode->code[tempNode->amountOfDigits - 1] = value;
	if (tempNode->leftPrev != nullptr) AddCodes(tempNode->leftPrev, tempNode, 0);
	if (tempNode->rightPrev != nullptr) AddCodes(tempNode->rightPrev, tempNode, 1);
}

Huffman* DeleteExcessNodes(Huffman* list, int& counter) {
	for (int i = 0; i < counter; i++) {
		while (list[i].ch == 0) {
			for (int k = i; k < counter; k++) list[k] = list[k + 1];
			Huffman* tempList = (Huffman*)realloc(list, --counter * sizeof(Huffman));
			list = tempList;
		}
	}

	return list;
}