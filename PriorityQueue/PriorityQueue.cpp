#include <iostream>

struct Queue {
private:
	int *priorities;
	static int length;

	void SiftUp(int currentIndex) {
		int elementIndex = currentIndex,
			parentIndex = (elementIndex + 1) / 2;
		while (parentIndex > 1) {
			if (priorities[elementIndex] > priorities[parentIndex - 1]) {
				int temp = priorities[elementIndex + 1];
				priorities[elementIndex] = priorities[parentIndex - 1];
				priorities[parentIndex - 1] = temp;
			}
			elementIndex = parentIndex;
			parentIndex = (elementIndex + 1) / 2;
		}
	}

	void SiftDown(int currentIndex) {
		int elementIndex = currentIndex,
			inheritIndex = (elementIndex + 1) * 2;
		while (elementIndex < length) {
			if (priorities[elementIndex] < priorities[inheritIndex - 1]) { // left inherit
				int temp = priorities[elementIndex];
				priorities[elementIndex] = priorities[inheritIndex - 1];
				priorities[inheritIndex - 1] = temp;
				elementIndex = inheritIndex - 1;
			} else if (priorities[elementIndex] < priorities[inheritIndex]) { // right inherit
				int temp = priorities[elementIndex];
				priorities[elementIndex] = priorities[inheritIndex];
				priorities[inheritIndex] = temp;
				elementIndex = inheritIndex;
			}
			inheritIndex = (elementIndex + 1) * 2;
			
		}

	}
public:
	Queue(int initialPriority) {
		length = 1;
		priorities = new int[1];
		priorities[0] = initialPriority;
	}

	void Insert(int priority) {
		length = length + 1;
		int *new_priorities = new int[length];
		for (int i = 0; i < length - 1; i = i + 1) {
			new_priorities[i] = priorities[i];
		}
		new_priorities[length - 1] = priority;
		delete[] priorities;
		priorities = new_priorities;
		SiftUp(length - 1);
	}

	int ExtractMax() {
		int extracted = priorities[0];
		length = length - 1;
		int *new_priorities = new int[length];
		new_priorities[0] = priorities[length];
		for (int i = 1; i < length; i = i + 1) {
			new_priorities[i] = priorities[i];
		}
		delete[] priorities;
		priorities = new_priorities;
		SiftDown(0);
		return extracted;
	}
};


int main() {
	Queue* queue = new Queue(6);
	queue->Insert(3);
	queue->Insert(7);
	queue->Insert(2);
	queue->Insert(11);
	std::cout << queue->ExtractMax();
}