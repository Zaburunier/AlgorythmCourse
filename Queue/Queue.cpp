#include <iostream>
#include <chrono>
#include <vector>

struct Queue {
private:
	std::vector<int> priorities;
	static int length;

	void SiftUp(int currentIndex) {
		int i = currentIndex;
		while (i >= 0 && priorities[i] > priorities[(i - 1) / 2]) {
			int temp = priorities[i];
			priorities[i] = priorities[(i - 1) / 2];
			priorities[(i - 1) / 2] = temp;
			i = (i - 1) / 2;
		}
	}

	void SiftDown(int currentIndex) {
		int i = currentIndex;
		while (i * 2 + 1 < length) {
			int leftInheritIndex = 2 * i + 1;
			int rightInheritIndex = 2 * i + 2;
			int inheritIndex = leftInheritIndex;
			if (rightInheritIndex < length && priorities[rightInheritIndex] > priorities[leftInheritIndex]) {
				inheritIndex = rightInheritIndex;
			}
			if (priorities[i] > priorities[inheritIndex]) {
				break;
			}
			int temp = priorities[i];
			priorities[i] = priorities[inheritIndex];
			priorities[inheritIndex] = temp;
			i = inheritIndex;
		}

	}
public:
	Queue(int initialPriority = 0) {
		length = 1;
		priorities.push_back(initialPriority);
	}

	void Insert(int priority) {
		length = length + 1;
		priorities.push_back(priority);
		int i = length - 1;
		while (i >= 0 && priorities[i] > priorities[(i - 1) / 2]) {
			int temp = priorities[i];
			priorities[i] = priorities[(i - 1) / 2];
			priorities[(i - 1) / 2] = temp;
			i = (i - 1) / 2;
		}
	}

	int ExtractMax() {
		int extracted = priorities[0];
		length = length - 1;
		priorities[0] = priorities[length];
		priorities.pop_back();
		int i = 0;
		while (i * 2 + 1 < length) {
			int leftInheritIndex = 2 * i + 1;
			int rightInheritIndex = 2 * i + 2;
			int inheritIndex = leftInheritIndex;
			if (rightInheritIndex < length && priorities[rightInheritIndex] > priorities[leftInheritIndex]) {
				inheritIndex = rightInheritIndex;
			}
			if (priorities[i] > priorities[inheritIndex]) {
				break;
			}
			int temp = priorities[i];
			priorities[i] = priorities[inheritIndex];
			priorities[inheritIndex] = temp;
			i = inheritIndex;
		}
		return extracted;
	}
};

int Queue::length = 0;

int main() {
	int *commandsAmount = new int;
	Queue *queue = new Queue();
	bool first = true;
	scanf_s("%d", commandsAmount);
	for (int i = 0; i < *commandsAmount; i = i + 1) {
		char *command = new char[11];
		scanf_s("%s", command);
		if (command[0] == 'E') {
			printf("%d\n", queue->ExtractMax());
		} else if (command[0] == 'I') {
			int *priorityValue = new int;
			scanf_s(" %d", priorityValue);
			if (first) {
				first = false;
				queue = new Queue(*priorityValue);
			} else {
				queue->Insert(*priorityValue);
			}
		}
	}
}