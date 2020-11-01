#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <iostream>


class Fibonacci {
public:
	static int get_remainder(long long n, int m) {
		assert(n >= 1);
		assert(m >= 2);
		int* remainderArray = (int*)malloc(6 * m * sizeof(int));
		bool checkForPeriod = false;//проверка на возможное наличие периода
		int firstMatchingNumber = 0;//первый член, совпадающий по остатку с нулевым
		remainderArray[0] = 0;
		remainderArray[1] = 1;
		remainderArray[2] = 1;
		for (int i = 3; i <= 6 * m; i++) {
			remainderArray[i] = (remainderArray[i - 1] + remainderArray[i - 2]) % m;
			if (checkForPeriod) {
				if (remainderArray[i] != remainderArray[i - firstMatchingNumber]) {//Если не равно, то совпадение невозможно
					checkForPeriod = false;
				} else if (i == 2 * firstMatchingNumber || i == 6 * m) {//Если равно и мы добрались до финального члена, то можно выходить из цикла 
					break;
				}
			}
			if (remainderArray[i] == 0) {//Возможное совпадение
				checkForPeriod = true;
				firstMatchingNumber = i;//запоминаем, поскольку проверку нужно проводить до (2*i + 1)-го числа
			}
		}
		int index = n % firstMatchingNumber;
		return remainderArray[index];
	}
};

int main(void) {
	long long* n = (long long*) malloc(sizeof(long long));
	int* m = (int*)malloc(sizeof(int));
	scanf("%lld", n);
	scanf("%d", m);
	printf("%d", Fibonacci::get_remainder(*n, *m));
	free(n);
	free(m);
	return 0;
}