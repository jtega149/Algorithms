
#include<iostream>
#include<cstdlib>
#include<chrono> //Will be used to track how long the program takes to sort

struct listnode{ 
   struct listnode *next;
   long value; 
};

//getMid() method to access middle node of linked list easily
listnode* getMid(listnode* head){
    listnode* slow = head; //Slow pointer
    listnode* fast = head->next; //Fast pointer that reaches end of linked list quicker
    while(fast != nullptr && fast->next != nullptr){ //Will loop until fast == nullptr
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; //Slow will point to a node in the middle of linked list
}
struct listnode * mergesort(struct listnode *a){
    if(a == nullptr || a->next == nullptr) return a; //Base case for recursion
    
    //Dividing the linked list into 2 different lists
    listnode *leftList = a;
    listnode *rightList = getMid(a);
    listnode *temp = rightList->next;
    rightList->next = nullptr;
    rightList = temp;

    //Recursion occurs here, essentially dividing the already divided lists until we reach base case
    //Cursors point to the begining of these divided lists
    listnode *leftCursor = mergesort(leftList);
    listnode *rightCursor = mergesort(rightList);

    //tailPtr will point to the tail of the sorted linked list, and headPtr points to the head of it
    listnode *tailPtr = new listnode();
    listnode *headPtr = tailPtr;

    //Will loop and merge until either of the cursors for the divided lists no longer points to a node
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

    //Inserting remaining nodes into linked list
    while(leftCursor != nullptr){
        tailPtr->next = leftCursor;
        leftCursor = leftCursor->next;
    }
    while(rightCursor != nullptr){
        tailPtr->next = rightCursor;
        rightCursor = rightCursor->next;
    }

    //headPtr pointed to a dummy node that's not in use, we just free its memory to the heap here
    listnode* sortedHead = headPtr->next;
    delete headPtr;  //Free the unused head node
    return sortedHead;
}


//main() will be used to test my mergesort method on a linked list of size 200,000
int main(){
    listnode* head = new listnode;
    head->value = 179987;
    head->next = nullptr;
    listnode* current = head;
    long N = 200000;

    //Creating 200,000 more nodes
    for(long i = 0; i < N; i++) {
        listnode* newNode = new listnode;
        newNode->value = rand() % (N + 100000) + 1;
        newNode->next = nullptr;
        current->next = newNode;
        current = newNode;
    }

    std::cout << "First 5 nodes of unsorted linked list: " << std::endl;
    current = head;
    for (int i = 0; i < 5; ++i) { // Print first 5 nodes
        std::cout << "Node " << i + 1 << ": " << current->value << std::endl;
        current = current->next;
    }

    //Start timing
    auto start = std::chrono::high_resolution_clock::now();
    head = mergesort(head);
    //End timing
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "First 5 nodes of sorted linked list: " << std::endl;
    current = head;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Node " << i + 1 << ": " << current->value << std::endl;
        current = current->next;
    }
    
    //Calculating time taken
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken to sort " << N  << " elements: " << duration.count() << " seconds" << std::endl;

    //Freeing the memory to heap of our linked list
    current = head;
    while (current != nullptr) {
        listnode* temp = current;
        current = current->next;
        delete temp;
    }
    return 0;
}