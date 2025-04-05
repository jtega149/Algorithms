#include<iostream>
#include<cstdlib>
#include<chrono>

struct listnode{ 
   struct listnode *next;
   long value; 
};

listnode* getMid(listnode* head){
    listnode* slow = head;
    listnode* fast = head->next; 
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
struct listnode * mergesort(struct listnode *a){
    if(a == nullptr || a->next == nullptr) return a;

    listnode *leftList = a;
    listnode *rightList = getMid(a);
    listnode *temp = rightList->next;
    rightList->next = nullptr;
    rightList = temp;

    listnode *leftCursor = mergesort(leftList);
    listnode *rightCursor = mergesort(rightList);
    
    listnode *tailPtr = new listnode();
    listnode *headPtr = tailPtr;

    while(leftCursor != nullptr && rightCursor != nullptr){
        if(leftCursor->value < rightCursor->value){
            tailPtr->next = leftCursor;
            leftCursor = leftCursor->next;
        }
        else{
            tailPtr->next = rightCursor;
            rightCursor = rightCursor->next;
        }
        tailPtr = tailPtr->next;
    }

    while(leftCursor != nullptr){
        tailPtr->next = leftCursor;
        leftCursor = leftCursor->next;
    }
    while(rightCursor != nullptr){
        tailPtr->next = rightCursor;
        rightCursor = rightCursor->next;
    }

    listnode* sortedHead = headPtr->next;
    delete headPtr;
    return sortedHead;
}

int main(){
    listnode* head = new listnode;
    head->value = 179987;
    head->next = nullptr;
    listnode* current = head;
    long N = 200000;

    for(long i = 0; i < N; i++) {
        listnode* newNode = new listnode;
        newNode->value = rand() % (N + 100000) + 1;
        newNode->next = nullptr;
        current->next = newNode;
        current = newNode;
    }

    std::cout << "First 5 nodes of unsorted linked list: " << std::endl;
    current = head;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Node " << i + 1 << ": " << current->value << std::endl;
        current = current->next;
    }

    auto start = std::chrono::high_resolution_clock::now();
    head = mergesort(head);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "First 5 nodes of sorted linked list: " << std::endl;
    current = head;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Node " << i + 1 << ": " << current->value << std::endl;
        current = current->next;
    }
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken to sort " << N  << " elements: " << duration.count() << " seconds" << std::endl;

    current = head;
    while (current != nullptr) {
        listnode* temp = current;
        current = current->next;
        delete temp;
    }
    return 0;
}