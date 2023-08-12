#include <iostream>
#include <stdexcept>

using namespace std;

template<class T>
class Node {
public:
    Node() {
        data = new T;
    }
    Node(T d) {
        data = new T;
        *data = d;
    }
    T &getData() {
        return *data;
    }
    void setData(T d) {
        *data = d;
    }
    bool operator==(T b) {
        cout<<"!";
        if(*data == b)
            return true;
        return false;
    }
    friend ostream &operator<<(ostream &out, Node<T> d) {
        out<<*(d.data);
        return out;
    }
    friend ostream &operator<<(ostream &out, Node<T> *d) {
        out<<*(d->data);
        return out;
    }
private:
    T *data;
};
template<class T>
class ListNode : public Node<T> {
public:
    ListNode() : Node<T>() {
        prev = NULL;
        next = NULL;
    }
    ListNode(T d) : Node<T>(d) {
        prev = NULL;
        next = NULL;
    }
    void setPrev(ListNode *p) {
        prev = p;
    }
    void setNext(ListNode *n) {
        next = n;
    }
    ListNode *getPrev() {
        return prev;
    }
    ListNode *getNext() {
        return next;
    }
private:
    ListNode *prev, *next;
};
template<class T>
class LinkList {
public:
    LinkList() {
        head = NULL;
        tail = NULL;
    }
    ListNode<T> *insertHead(T d) {
        ListNode<T> *newNode = new ListNode<T>(d);
        if(head == NULL) {
            head = newNode;
            tail = newNode;
            return newNode;
        }
        else {
            newNode->setNext(head);
            head->setPrev(newNode);
            head = newNode;
            return newNode;
        }

    }
    ListNode<T> *insertTail(T d) {
        ListNode<T> *newNode = new ListNode<T>(d);
        if(head == NULL) {
            head = newNode;
            tail = newNode;
            return newNode;
        }
        else {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
            return newNode;
        }
    }
    ListNode<T> *insertAfter(T d, ListNode<T> *p) {
        if(!exist(p))
            return NULL;
        ListNode<T> *newNode = new ListNode<T>(d);
        if(p == tail)
            return insertTail(d);
        else {
            ListNode<T> *n = p->getNext();
            p->setNext(newNode);
            newNode->setPrev(p);
            newNode->setNext(n);
            n->setPrev(newNode);
            return newNode;
        }
    }
    ListNode<T> *removeHead() {
        if(head == NULL)
            return NULL;
        ListNode<T> *temp = head;
        head = head->getNext();
        if(head != NULL)
            head->setPrev(NULL);
        else
            tail = NULL;
        temp->setNext(NULL);
        return temp;
    }
    ListNode<T> *removeTail() {
        if(head == NULL)
            return NULL;
        ListNode<T> *temp = tail;
        tail = tail->getPrev();
        if(tail != NULL)
            tail->setNext(NULL);
        else
            head = NULL;
        temp->setNext(NULL);
        return temp;
    }
    ListNode<T> *removeElement(ListNode<T> *n) {
        if(!exist(n))
            return NULL;
        if(n == head)
            return removeHead();
        else if(n == tail)
            return removeTail();
        else {
            ListNode<T> *prevNode = n->getPrev();
            ListNode<T> *nextNode = n->getNext();
            n->setNext(NULL);
            n->setPrev(NULL);
            prevNode->setNext(nextNode);
            nextNode->setPrev(prevNode);
            return n;
        }
    }
    ListNode<T> *find(T d) {
        ListNode<T> *cur = head;
        while(cur != NULL) {
            if(*cur == d)
                break;
            cur = cur->getNext();
        }
        return cur;
    }
    int size() {
        ListNode<T> *cur = head;
        int s = 0;
        while(cur != NULL) {
            s ++;
            cur = cur->getNext();
        }
        return s;
    }
    bool exist(ListNode<T> *p) {
        ListNode<T> *cur = head;
        while(cur != NULL) {
            if(cur == p)
                return true;
            cur = cur->getNext();
        }
        return false;
    }
    T &operator[](int n) {
        ListNode<T> *k = NULL;
        int j;
        for(j = 0, k = head;j < n;j ++, k = k->getNext())
            if(k == NULL)
                break;
        if(k == NULL)
            throw std::invalid_argument("array out of range");
        return k->getData();
    }
private:
    ListNode<T> *head, *tail;
};

template<class T>
class Stack : LinkList<T> {
public:
    Stack() : LinkList<T>() {}
    ListNode<T> *push(T d) {
        return this->insertHead(d);
    }
    ListNode<T> *pop() {
        return this->removeHead();
    }
};
template<class T>
class Queue : LinkList<T> {
public:
    Queue() : LinkList<T>() {}
    ListNode<T> *enqueue(T d) {
        return this->insertHead(d);
    }
    ListNode<T> *dequeue() {
        return this->removeTail();
    }
};
/*template<class T>
bool operator==(ListNode<T> a, T b) {
        cout<<"?";
    if(a.getData() == b)
        return true;
    return false;
}*/

template<class T>
class TreeNode : public Node<T> {
public:
    TreeNode(T d) : Node<T>(d) {
        children = new LinkList<TreeNode<T> *>();
    }
    TreeNode<T> *addChild(T d) {
        TreeNode<T> *newNode = new TreeNode<T>(d);
        children->insertTail(newNode);
        return newNode;
    }
    TreeNode<T> &operator[](int n) {
        try {
            TreeNode<T> &temp = *((*children)[n]);
            return temp;
        }
        catch(std::invalid_argument e) {
            throw e;
        }
    }
private:
    LinkList<TreeNode<T> *> *children;
};

template<class T>
class Tree {
public:
    Tree() {
        root = NULL;
    }
    TreeNode<T> *addChild(TreeNode<T> *node, T d) {
        if(node == NULL) {
            root = new TreeNode<T>(d);
            return root;
        }
        else {
            return node->addChild(d);
        }
    }
    void display() {
        _display(root, 0);
    }
private:
    TreeNode<T> *root;
    void _display(TreeNode<T> *n, int d) {
        int j;
        for(j = 0;j < d;j ++)
            cout<<"  ";
        cout<<n<<endl;
        try {
            for(j = 0;;j ++) {
                _display(&(*n)[j], d + 1);
            }
        }
        catch(std::invalid_argument e) {
        }
    }
};

int main()
{
    Tree<int> *tree = new Tree<int>();
    TreeNode<int> *node1 = tree->addChild(NULL, 1);
    TreeNode<int> *node2 = tree->addChild(node1, 2);
    tree->addChild(node1, 3);
    TreeNode<int> *node4 = tree->addChild(node1, 4);
    tree->addChild(node2, 5);
    TreeNode<int> *node6 = tree->addChild(node2, 6);
    tree->addChild(node4, 7);
    tree->addChild(node6, 8);
    tree->addChild(node6, 9);
    tree->addChild(node6, 10);
    tree->display();
}
