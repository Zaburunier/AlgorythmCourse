#include <iostream>


class QueueElement {
private:
    int priority;
    QueueElement *leftInherit;
    QueueElement *rightInherit;
    QueueElement *parent;
    static QueueElement *head;
    static int amountOfElements;

    void Swap(bool isLeft) {//Swapping this element with its inherit (left or right)
        QueueElement *parent = this->parent;
        QueueElement *inherit;
        if (isLeft) {
            inherit = this->leftInherit;
        } else {
            inherit = this->rightInherit;
        }
        QueueElement *inheritLeftInherit = inherit->leftInherit,
            *inheritRightInherit = inherit->rightInherit;

        // Firstly connecting inherit and parent directly
        if (this == parent->leftInherit) {
            parent->leftInherit = inherit;
        } else { //rightInherit
            parent->rightInherit = inherit;

        }
        inherit->parent = parent;
        // Secondly making this element as inherit to current inherit (and such a change for parenting)
        if (isLeft) {
            inherit->leftInherit = this;
        } else {
            inherit->rightInherit = this;
        }
        this->parent = inherit;
        // Thirdly connecting other elements to new hierarchy
        if (isLeft) {// repair connection to the RIGHT child (left has been swapped earlier)
            inherit->rightInherit = this->rightInherit;
            inherit->rightInherit->parent = inherit;
        } else {// same but LEFT
            inherit->leftInherit = this->leftInherit;
            inherit->leftInherit->parent = inherit;
        }
        this->leftInherit = inheritLeftInherit;
        this->rightInherit = inheritRightInherit;
        inheritLeftInherit->parent = this;
        inheritRightInherit->parent = this;
    }

    void SiftUp() {
        QueueElement *elementPtr = this;
        while (elementPtr->priority > elementPtr->parent->priority) {
            elementPtr->parent->Swap(elementPtr == elementPtr->parent->leftInherit);
            elementPtr = elementPtr->parent;
        }
    }

    void SiftDown() {
        QueueElement *elementPtr = this;
        while (elementPtr->priority < elementPtr->leftInherit->priority || elementPtr->priority < elementPtr->rightInherit->priority) {
            if (elementPtr->priority < elementPtr->leftInherit->priority) {
                elementPtr->Swap(true);
                elementPtr = elementPtr->leftInherit;
            } else {
                elementPtr->Swap(false);
                elementPtr = elementPtr->rightInherit;
            }
        }
    }

public:

    QueueElement() {}

    QueueElement(int newElementPriority) : priority(newElementPriority) {
        amountOfElements = amountOfElements + 1;
        this->leftInherit = nullptr;
        this->rightInherit = nullptr;
        if (head == nullptr) {
            this->parent = nullptr;
            head = this;
        } else {
            QueueElement *elementPtr = head;
            while (true) {
                if (elementPtr->leftInherit == nullptr) {
                    elementPtr->leftInherit = this;
                    this->parent = elementPtr;
                    break;
                } else if (elementPtr->rightInherit == nullptr) {
                    elementPtr->rightInherit = this;
                    this->parent = elementPtr;
                    break;
                } else {
                    
                }
            }
        }
    }

    QueueElement(const QueueElement &element) : priority(element.priority), leftInherit(element.leftInherit), rightInherit(element.rightInherit), parent(element.parent) {}
    
    ~QueueElement() {}

    static void Insert(int priority) {
    }
    static void ExtractMax() {
    }

};

QueueElement* QueueElement::head = nullptr;
int QueueElement::amountOfElements = 0;


int main()
{
    QueueElement *queue = new QueueElement[20];
}