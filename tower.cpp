// use linked list implementation because the stack can grow dynamically
#include <iostream>
using namespace std;

template <class T>
class Node
{
public:
    Node()
    {
        this->prev = nullptr;
        this->next = nullptr;
    }

    Node(T data)
    {
        this->prev = nullptr;
        this->next = nullptr;
        this->data = data;
    }

    Node(T data, Node<T> *prev, Node<T> *next)
    {
        this->prev = prev;
        this->next = next;
        this->data = data;
        if (prev)
            prev->setNext(this);
        if (next)
            next->setPrev(this);
    }

    T getData()
    {
        return this->data;
    }

    Node *getNext()
    {
        return this->next;
    }

    Node *getPrev()
    {
        return prev;
    }

    void setData()
    {
        this->data = data;
    }

    void setNext(Node<T> *n)
    {
        next = n;
    }

    void setPrev(Node<T> *n)
    {
        prev = n;
    }

private:
    Node<T> *prev;
    Node<T> *next;
    T data;
};

template <class T>
class LinkedList
{
public:
    /**
     * Construct a new LinkedList object with no parameter
     */
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    LinkedList(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        head = newNode;
        tail = newNode;
    }

    void addToTail(T data)
    {
        // check if it is the first node of the linkedList to be created
        if (tail == NULL)
        {
            // create a new node and assign it data
            Node<T> *newNode = new Node<T>(data);
            head = newNode;
            tail = newNode;
        }
        else
        {
            // node to be added to tail
            Node<T> *newNode = new Node<T>(data);
            // next of tail must point to new node
            tail->setNext(newNode);
            // newNode must point to tail
            newNode->setPrev(tail);
            // make the new node the tail by pointing tail to newNode
            tail = newNode;
        }
    }

    /**
     * Add a node to the head of the linked list
     * @param data: data to put in
     */
    void addToHead(T data)
    {
        if (head == nullptr)
        {
            // create a new node and assign it data
            Node<T> *newNode = new Node<T>(data);
            head = newNode;
            tail = newNode;
        }
        else
        {
            // node to be added to head
            Node<T> *newNode = new Node<T>(data);
            // point prev of head to newNode
            head->setPrev(newNode);
            // newNode next point to head
            newNode->setNext(head);
            // make the new node the head by pointing head to newNode
            head = newNode;
        }
    }

    void addBetween(T data, T data1, T data2)
    {
        Node<T> *previous = this->getNode(data1);
        Node<T> *next = this->getNode(data2);
        if (previous && next)
        {
            if (previous->getNext() == next)
            {
                Node<T> *newNode = new Node<T>(data, previous, next);
                cout << "inserted succesfully!\n";
            }
        }
        else
        {
            cout << "One or more nodes could not be found!\n";
        }
    }

    // getter for head
    Node<T> *getHead()
    {
        return this->head;
    }

    // getter for tail
    Node<T> *getTail()
    {
        return this->tail;
    }

    // helper to get ba particular node by its data
    Node<T> *getNode(T data)
    {
        Node<T> *node = this->head;
        while (node != nullptr)
        {
            if (node->getData() == data)
                return node;
            node = node->getNext();
        }
        return NULL;
    }
    /**
     * Delete a node from the linked list with the given data from the head
     * If there are no data to be deleted, then do nothing
     * @param data: data to delete
     */
    void deleteData(T data)
    {
        // delete node with value = data if found
        // if not found, do nothing
        // if nodes from head to tail are deleted, set head and tail to null
        Node<T> *node = this->head;
        while (node != nullptr)
        {
            if (node->getData() == data)
            {
                if (node == head)
                {
                    if (node->getNext() == nullptr)
                    {
                        head = nullptr;
                        tail = nullptr;
                    }
                    else
                    {
                        head = node->getNext();
                        head->setPrev(nullptr);
                    }
                }
                else if (node == tail)
                {
                    if (node->getPrev() == nullptr)
                    {
                        head = nullptr;
                        tail = nullptr;
                    }
                    else
                    {
                        tail = node->getPrev();
                        tail->setNext(nullptr);
                    }
                }
                else
                {
                    node->getPrev()->setNext(node->getNext());
                    node->getNext()->setPrev(node->getPrev());
                }
                delete node;
                return;
            }
            node = node->getNext();
        }
    }

    /**
     * Delete valid n nodes from the linked list with the given data from the head
     * If there are no more data to be deleted, then just skip
     * @param data: data to delete
     * @param n: max number of nodes to delete
     */
    void deleteData(T data, int n)
    {
        // delete n nodes with value = data if found
        // if not found, do nothing
        // if node is head, set head to next node or null if no next node
        // if node is tail, set tail to prev node or null if no prev node
        // if nodes from head to tail are deleted, set head and tail to null
        Node<T> *node = this->head;
        while (node != nullptr && n > 0)
        {
            if (node->getData() == data)
            {
                if (node == head)
                {
                    head = node->getNext();
                    head->setPrev(nullptr);
                }
                else if (node == tail)
                {
                    tail = node->getPrev();
                    tail->setNext(nullptr);
                }
                else
                {
                    node->getPrev()->setNext(node->getNext());
                    node->getNext()->setPrev(node->getPrev());
                }
                Node<T> *temp = node;
                node = node->getNext();
                delete temp;
                n--;
            }
            else
            {
                node = node->getNext();
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &out, LinkedList *n)
    {
        if (!n)
        {
            out << "()\n";
            return out;
        }
        Node<T> *listIter = n->head;
        out << "(";
        while (listIter)
        {
            out << listIter->getData();
            listIter = listIter->getNext();
            if (listIter)
                out << ", ";
            else
                break;
        }

        out << ")" << endl;

        return out;
    }

private:
    Node<T> *head;
    Node<T> *tail;
};

template <class T>
class Stack
{
public:
    /**
     * Construct a new Stack object with no parameter
     */
    Stack() {
        this->list = new LinkedList<T>();
    }

    /**
     * Add a data to stack
     * @param data: data to be added to stack
     */
    void push(T data) {
        this->list->addToTail(data);
    }

    /**
     * Remove a data from stack and return it
     * @return the data removed from stack
     */
    T pop() {
        if (isEmpty())
            return 0;
        T data = this->list->getTail()->getData();
        this->list->deleteData(data);
        return data;
    }

    /**
     * @return the last element in the stack
     */
    T top() {
        if (isEmpty())
            return NULL;
        return this->list->getTail()->getData();
    }

    /**
     * @return true if stack is empty, false otherwise
     */
    bool isEmpty() {
        return this->list->getHead() == nullptr;
    }

    /**
     * @return the size of the stack
     */
    int size() {
        //count nodes in linked list
        int count = 0;
        Node<T> *node = this->list->getHead();
        while (node != nullptr)
        {
            count++;
            node = node->getNext();
        }
        return count;
    }

    //inherit << operator from LinkedList
    friend std::ostream &operator<<(std::ostream &out, Stack *n)
    {
        out << n->list;
        return out;
    }

private:
    LinkedList<T> *list;
};
// Function to implement legal movement between
// two poles
void moveDisksBetweenTwoPoles(Stack<int> *src, Stack<int> *dest)//define two pointers to 2 stacks, (source and destination)
{
    if (src->size() == 0) //check if source is empty
    {
        src->push(dest->pop());// move from destination into source
    }
    else if (dest->size() == 0)//check if the destination is empty
    {
        dest->push(src->pop()); //move from source to destination
        
    }
    else if (src->top() > dest->top())//check if source is disk is bigger than destination disk
    {
        src->push(dest->pop());
        
    }
    else
    {
        dest->push(src->pop());// When top disk of pole1 < top disk of pole2
        
    }
}

void solveTheGame(int num_of_disks, Stack<int> *src, Stack<int> *aux, Stack<int> *dest)
{
    int i;//number of minimum moves

    Stack<int> *destReference = dest; //define a pointer and set to point to the same address as dest
    bool flagSwaped = false;
    //depending on whether disks are odd or even, we will start differently
    //so we swap aux and dest if disks are even so that in our code the first move is always moving to destination.
    //the sequence of events is always the same, only the starting pole changes
    if (num_of_disks % 2 == 0)
    {
        flagSwaped = true;

        Stack<int> *t = dest; //swapping the dest and auxilarly
        dest = aux;
        aux = t;
    }
    //Larger disks will be pushed first to the source
    for (i = num_of_disks; i > 0; i--) 
    {
        src->push(i);
    }

    for (i = 1; destReference->size() != num_of_disks; i++)
    {
        if (i % 3 == 1)
            moveDisksBetweenTwoPoles(src, dest);

        else if (i % 3 == 2)
            moveDisksBetweenTwoPoles(src, aux);

        else if (i % 3 == 0)
            moveDisksBetweenTwoPoles(dest, aux);
    }

    cout << i - 1 << endl;
}

// Driver Program
int main()
{

    int num_of_disks;
    while (cin >> num_of_disks)
    {
        // Input: number of disks
        Stack<int> *src, *dest, *aux;

        // allocating memory for the three pegs
        src = new Stack<int>;
        aux = new Stack<int>;
        dest = new Stack<int>;

        // calling iterative function to solve the game
        solveTheGame(num_of_disks, src, aux, dest);
    }

    return 0;
}
