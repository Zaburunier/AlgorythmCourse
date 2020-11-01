#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <iostream>


class Fibonacci {
public:
	static int get_remainder(long long n, int m) {
		assert(n >= 1);
		assert(m >= 2);
		int* remainderArray = (int*)malloc(6 * m * sizeof(int));
		bool checkForPeriod = false;//�������� �� ��������� ������� �������
		int firstMatchingNumber = 0;//������ ����, ����������� �� ������� � �������
		remainderArray[0] = 0;
		remainderArray[1] = 1;
		remainderArray[2] = 1;
		for (int i = 3; i <= 6 * m; i++) {
			remainderArray[i] = (remainderArray[i - 1] + remainderArray[i - 2]) % m;
			if (checkForPeriod) {
				if (remainderArray[i] != remainderArray[i - firstMatchingNumber]) {//���� �� �����, �� ���������� ����������
					checkForPeriod = false;
				} else if (i == 2 * firstMatchingNumber || i == 6 * m) {//���� ����� � �� ��������� �� ���������� �����, �� ����� �������� �� ����� 
					break;
				}
			}
			if (remainderArray[i] == 0) {//��������� ����������
				checkForPeriod = true;
				firstMatchingNumber = i;//����������, ��������� �������� ����� ��������� �� (2*i + 1)-�� �����
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