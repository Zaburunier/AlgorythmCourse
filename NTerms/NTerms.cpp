// NTerms.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

bool CheckForPresence(int**, int, int);

int main()
{
	int num;
	scanf("%d", &num);

	int currentNum = 1;
	int counter = 1;
	int currentTerm = 2;
	int* terms = (int*)malloc(sizeof(int));
	terms[0] = 1;


	while (true) {
		if (num == 1) break;
		if (num == 2) {
			currentNum = 2;
			terms[0] = 2;
			break;
		}
		if (!CheckForPresence(&terms, currentTerm, counter)) {
			if ((currentNum + currentTerm) < num) {
				counter++;
				int* temp = (int*)realloc(terms, counter * sizeof(int));
				terms = temp;
				terms[counter - 1] = currentTerm;
				currentNum += currentTerm;
				currentTerm++;
			}
			else if ((currentNum + currentTerm) > num) {
					currentNum -= terms[counter - 1];
					counter--;
					int* temp = (int*)realloc(terms, counter * sizeof(int));
					terms = temp;			
			}
			else if ((currentNum + currentTerm) == num) {
				counter++;
				int* temp = (int*)realloc(terms, counter * sizeof(int));
				terms = temp;
				terms[counter - 1] = currentTerm;
				currentNum += currentTerm;
				break;
			}
		} else {
			currentTerm++;
		}
		
	}

	printf("%d\n", counter);
	for (int i = 0; i < counter; i++) printf("%d ", terms[i]);

	return 0;
}

bool CheckForPresence(int** terms, int checkedTerm, int count) {
	int* _terms = *terms;
	for (int i = 0; i < count; i++) {
		if (_terms[i] == checkedTerm) return true;
	}
	
	return false;
}
