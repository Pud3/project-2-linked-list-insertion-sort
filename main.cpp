// Project Part 2
// Insertion Sort on a Singly Linked List
// Jonathan Puddie
// 4/18/26

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_SIZE = 5000;

struct Node {
    int data;
    Node* next;
};

// Loads integers from file into an array.
// Returns true if the file was opened successfully.
bool LoadNumbers(const string& filename, int* array, int& count) {
    ifstream fin(filename);
    if (!fin) {
        return false;
    }

    count = 0;
    while (count < MAX_SIZE && fin >> array[count]) {
        count++;
    }

    fin.close();
    return true;
}

// Adds a new node with value to the end of the list.
void insertAtEnd(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Prints up to "limit" values from the list.
void printListPreview(Node* head, int limit = 20) {
    cout << "[";

    Node* current = head;
    int count = 0;

    while (current != nullptr && count < limit) {
        cout << current->data;
        current = current->next;
        count++;

        if (current != nullptr && count < limit) {
            cout << ", ";
        }
    }

    if (current != nullptr) {
        cout << ", ...";
    }

    cout << "]" << endl;
}

// Deletes all nodes in the list and sets head to nullptr.
void deleteList(Node*& head) {
    Node* current = head;

    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
}

// Sort the linked list using insertion sort.
void insertionSortList(Node*& head) {
    Node* sorted = nullptr;
    Node* current = head;

    while (current != nullptr) {
        Node* nextNode = current->next;

        if (sorted == nullptr || current->data < sorted->data) {
            current->next = sorted;
            sorted = current;
        }
        else {
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->data < current->data) {
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }

        current = nextNode;
    }

    head = sorted;
}

int main() {
    int allNumbers[MAX_SIZE];
    int totalCount = 0;

    if (!LoadNumbers("numbers_dataset_5000.txt", allNumbers, totalCount)) {
        cout << "Error: could not open file." << endl;
        return 1;
    }

    int sizes[3] = {100, 1000, 5000};

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];

        if (n > totalCount) {
            cout << "Not enough data for subset size " << n << endl;
            continue;
        }

        Node* head = nullptr;

        // Build linked list from first n values
        for (int i = 0; i < n; i++) {
            insertAtEnd(head, allNumbers[i]);
        }

        cout << "\nDATASET SIZE: " << n << endl;
        cout << "UNSORTED PREVIEW: ";
        printListPreview(head);

        insertionSortList(head);

        cout << "SORTED PREVIEW:   ";
        printListPreview(head);

        deleteList(head);
    }

    return 0;
}

/*
Reflection:

Insertion sort on a linked list is different from insertion sort on an array
because arrays use positions and indexes, while linked lists use pointers to
connect nodes.

The linked-list structure made insertion easier in one way because I did not
have to shift a lot of values like in an array. Instead, I changed pointers to
place the node in the correct position. However, it was harder overall because
pointer handling is more confusing and easier to mess up.

Both array insertion sort and linked-list insertion sort can still behave like
O(n^2) because each new value may still need to be compared against many items
already in the sorted part before it is inserted in the right place.

The array version was easier for me to write and debug. The linked-list version
was harder because I had to carefully keep track of node links and make sure I
did not lose part of the list.
*/
