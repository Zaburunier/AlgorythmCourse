#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

void SortNewElement(long long***, int);

int main(void) {
	long long** points = (long long**) malloc(2 * sizeof(long long*));
	int* amountOfPoints = (int*)malloc(sizeof(int));;
	scanf("%d", amountOfPoints);
	points[0] = (long long*)malloc(*amountOfPoints * sizeof(long long));
	points[1] = (long long*)malloc(*amountOfPoints * sizeof(long long));
	for (int i = 0; i < *amountOfPoints; i++) {
		scanf("%lld %lld", &points[0][i], &points[1][i]);
		SortNewElement(&points, i);
	}

	long long* resultPoints = (long long*) malloc(sizeof(long long));
	int* amountOfResultPoints = (int*)malloc(sizeof(int));
	*amountOfResultPoints = 0;
	long long* currentPoint = (long long*)malloc(sizeof(long long));
	*currentPoint = -1;
	for (int i = 0; i < *amountOfPoints; i++) {
		if ((points[1][i] > * currentPoint && points[0][i] > * currentPoint)
			|| (points[1][i] < *currentPoint && points[0][i] < *currentPoint)) {
			long long* temp = (long long*)realloc(resultPoints, ++(*amountOfResultPoints) * sizeof(long long));
			resultPoints = temp;
			resultPoints[*amountOfResultPoints - 1] = points[1][i];
			*currentPoint = points[1][i];
		}
	}

	printf("%d\n", *amountOfResultPoints);
	for (int i = 0; i < *amountOfResultPoints; i++) {
		printf("%lld ", resultPoints[i]);
	}
	return 0;
}

void SortNewElement(long long*** points, int lastIndex) {
	long long** pointArray = *points;
	if (lastIndex == 0) return;
	int i = lastIndex;
	if (pointArray[0][i] > pointArray[1][i]) {
		long long temp = pointArray[1][i];
		pointArray[1][i] = pointArray[0][i];
		pointArray[0][i] = temp;
	}
	int currentIndex = lastIndex;
	while (--i >= 0 
	&& 
	pointArray[1][currentIndex] < pointArray[1][i] 
	) {
		long long temp1 = pointArray[0][i], temp2 = pointArray[1][i];
		pointArray[0][i] = pointArray[0][currentIndex];
		pointArray[1][i] = pointArray[1][currentIndex];
		pointArray[0][currentIndex] = temp1;
		pointArray[1][currentIndex] = temp2;
		currentIndex = i;
	}
}