#include <iostream>
#include <string>
#include <vector>

using namespace std;

int i = 1;

template<class T>
class Node {
  public:
  Node(){}
  Node(T data) // construct a new Node obj to put in
  {
    this->data = data;
    next = prev = NULL;
  } 

  Node(T data, Node<T> *prev, Node<T> *next) 
  {
    this->data = data;
    this->prev = prev;
    this->next = next;

  }
  void setPrev(Node<T> *prev)
  {
    this->prev = prev;
  }
  void setNext(Node<T> *next)
  {
    this->next = next;
  }
  Node<T> *getPrev(){ return prev;}
  Node<T> *getNext(){ return next;}
  T getData(){ return data;}
  void setData(T d) { this->data = d;}

  private: 
    Node<T> *prev;
    Node<T> *next;
    T data;
};

template<class T>
class LinkedList {
  public:
  LinkedList() { this->size = 0;  this->head = this->tail = NULL;}
  Node<T> *getHead(){ return this->head;}
  Node<T> *getTail(){ return this->tail;}
  
  void addToTail(T data) 
  {
    Node<T> *n = new Node<T>(data); //Creating a new node

    if ( this->head == NULL ) //If list is empty
    {
      this->head = this->tail = n;
    }
    else {
      n->setPrev( tail );
      tail->setNext(n);
      tail = n;
    }
    size++;
  }
  void addToHead(T data) 
  {
    if (head == NULL) //List is empty
      this->head = this->tail = new Node<T> (data, NULL, NULL);
    else
    {
      Node<T> *n = new Node<T> (data, NULL, this->head);
      this->head->setPrev(n);
      this->head = n;
    }

    size++;
  }
  void sort()
  {
    Node<T> *cur = this->getHead();
    Node<T> *nex = cur;
    T temp;
    

    while ( cur != NULL)
    {
        nex = cur->getNext();
        while ( nex != NULL)
        {
            if( cur->getData()->getData() > nex->getData()->getData() )       
            {
              temp = cur->getData();
              cur->setData(nex->getData());
              nex->setData(temp);
            }
            nex = nex->getNext();
        }
      cur = cur->getNext();
    }
    
  }
  void deleteData(T data) 
  {
    Node<T> *cur = head;
    if (this->head == NULL) { return; }   // link is empty cannot delete anything

    if (this->head == this->tail) // 1 Node in list only
    {
      if(cur->getData() == data)
      {
        this->head = this->tail = NULL;
      }
    }
    else //More than 1 Node
    {
      while (cur != NULL)
      {

        if (cur->getData() == data){
          if(cur == this->head){ //Remove Head 
            this->head = cur->getNext();
            this->head->setPrev(NULL);
          }
          else if (cur == tail) //Remove tail
          {
            tail = cur->getPrev();
            tail->setNext(NULL);
          }
          else {
            cur->getPrev()->setNext(cur->getNext());
            cur->getNext()->setPrev(cur->getPrev());
          }
          break;
        }
        cur = cur->getNext();
      }
    }
    size--;
  }
  
  void deleteData(T data, int n) 
  {
    for (int i = 0; i < n; i++)
    {
      deleteData(data);
    }
  }
  friend std::ostream &operator<<(std::ostream &out, LinkedList<T> *n) 
  {
    Node<T> *temp = n->getHead();

    cout << "(";

    while (temp != NULL){
      cout << (temp->getData()->getData());
      temp = temp->getNext();
      if(temp != NULL)
        cout << ", ";
    }
    cout << ")\n";
    return out;
  }

    int getSize(){  return this->size;}
  private: 
    Node<T> *head;
    Node<T> *tail;
    int size;
};


template<class T>
class TreeNode {
  public:
   virtual TreeNode<T>* getParent() = 0;
   virtual void setParent(TreeNode<T>* parent) = 0;
    virtual LinkedList<TreeNode<T>*>* getChildren() = 0;
    virtual void setChildren(LinkedList<TreeNode<T>*>* children) = 0;
    virtual T getData() = 0;
    virtual void setData (T d) = 0;
    virtual bool getTerminal() = 0;
    virtual void setTerminal(bool t) = 0;

    bool operator > ( TreeNode<T> *a ){
        return ( this->getData() > a->getData() );
    }

  protected:
    T data;
    LinkedList<TreeNode<T>*>* children;
    bool terminal;
    TreeNode<T> *parent;
};

template<class T, class D>
class Tree {
  public:
    virtual void levelorder() = 0;
    virtual void inorder() = 0;
    virtual void preorder() = 0;
    virtual void postorder() = 0;
    virtual bool insert(D data) = 0;
    virtual bool remove(D data) = 0;
    virtual TreeNode<T>* search(D data) = 0;
    virtual void setRoot(TreeNode<T>* root) = 0;
    virtual string serialize() = 0;
  protected:
    TreeNode<T>* root;
};

template<class T>
class GeneralTreeNode : public TreeNode<T> {
    public:
    GeneralTreeNode ()
    {
      this->setParent(NULL);
      this->setChildren(NULL);
      this->terminal = false;
    }
    GeneralTreeNode(TreeNode<T> *p, LinkedList<TreeNode<T> *> *c)
    {
      this->parent = p;
      this->children = c;
      this->terminal = false;
    }

    virtual void setParent(TreeNode<T>* parent){  this->parent = parent;}
    virtual void setChildren(LinkedList<TreeNode<T>*>* children){ this->children = children;}
    virtual TreeNode<T>* getParent(){  return this->parent;}
    virtual LinkedList<TreeNode<T>*>* getChildren(){   return this->children;}
    virtual T getData () {  return this->data; }
    virtual void setData (T d) { this->data = d; }
    virtual bool getTerminal() {  return this->terminal; }
    virtual void setTerminal (bool t) { this->terminal = t;}
};

template<class T, class D>
class GeneralTree : public Tree<T, D> {
  public:
    GeneralTree(){
      this->root = new GeneralTreeNode<T>( NULL, new LinkedList<TreeNode<T>*>() );
    }

    TreeNode<T> * getRoot(){ return this->root; }

    virtual void levelorder()
    {
      Node<TreeNode<T> *> *t = this->root->getChildren()->getHead();
      cout << "root";
      while( t ){
        _preorder( t );
        t = t->getNext();
      }

      cout << endl;
    }

    virtual void inorder()
    {
      Node<TreeNode<T> *> *t = this->root->getChildren()->getHead();
      cout << "root";
      while( t ){
        _postorder( t );
        t = t->getNext();
      }

      cout << endl;
    }
  
    void _preorder( Node<TreeNode<T>*> *p){
      if( p == NULL )
        return;
      
      cout << ", " << p->getData()->getData();
      Node<TreeNode<T>*> *t = p->getData()->getChildren()->getHead();

      while( t ){
        _preorder(t);
        t = t->getNext();
      }
    }

    virtual void preorder()
    {
      Node<TreeNode<T> *> *t = this->root->getChildren()->getHead();
      cout << "root";
      while( t ){
        _preorder( t );
        t = t->getNext();
      }

      cout << endl;
    }

    void _postorder(Node<TreeNode<T> *> *p)
    {
      Node<TreeNode<T> *> *t = p->getData()->getChildren()->getHead();
      if ( p == NULL)
        return;
      
      while(t)
      {
        _postorder(t);
        t = t->getNext();
      }
      cout << p->getData()->getData() <<  ", " ;
    }

    virtual void postorder()
    {
      Node<TreeNode<T> *> *t = this->root->getChildren()->getHead();
      while(t)
      {
        _postorder(t);
        t = t->getNext();
      }
      cout << "root" << endl;
    }
    
    TreeNode<T> *createBranch(D data)
    {
      TreeNode<T> *t = new GeneralTreeNode<T>(NULL, new LinkedList<TreeNode<T>*>() );
      t->setData( data[0] );
      TreeNode<T> *p = t;
      TreeNode<T> *c;

      for (int i = 1; i < data.length(); i++)
      {
        c = new GeneralTreeNode<T>(p, new LinkedList<TreeNode<T>*>() );
        c->setData( data[i] );
        p->getChildren()->addToTail( c );
        p =  c;
      }
      
      p->setTerminal(true);

      return t;
    }

    virtual bool insert(D data)
    {
      if( wExists(data) )
        return false;
      TreeNode<T> *p = this->root;
      TreeNode<T> *tp = p;
      TreeNode<T> *srch = NULL;
      string s = "";

      for( int i = 0; i < data.length(); i++ ){
        srch = search( p , data[i] );
        if( srch == NULL ){
          s = data.substr(i);
          TreeNode<T> *temp = createBranch(s);
          temp->setParent(p);
          p->getChildren()->addToTail(temp);
          return true;
        }
        else{
          if( i == data.length()-1){
            srch->setTerminal(true);
            return true;
          }
          p = srch;
        }
      }

      return true;
    }

    bool wExists( D s ){
      if( wordExists( s ) )
        return true;

      return false;
    }

    TreeNode<T> *wordExists( D data ){
      bool exists = false;
      TreeNode<T> *p = this->root;
      TreeNode<T> *srch = NULL;

      for( int i = 0; i < data.length(); i++ ){
        srch = search( p, data[i] );
        if( srch == NULL ){
          return NULL;
        }
        p = srch;
      }

      if( p->getTerminal() ){
          return p;
      }

      return NULL;
    }

    virtual bool remove(D data)
    {
      bool exists = false;
      TreeNode<T> *p = wordExists( data );
      TreeNode<T> *c = p;

      if( p != NULL ){
        p->setTerminal(false);
        while( p != this->root ){
          if( p->getChildren()->getSize() > 0 ){
            p->setTerminal(false);
            return true;
          }
          else if( p->getChildren()->getSize() == 0  && p->getTerminal() == true)
            break;
          else{
            c = p;
            p = p->getParent();
            p->getChildren()->deleteData( c );
          }
        }
        return true;
      }

      return false;
    }
     virtual TreeNode<T> *search( D data )
     {
        return wordExists( data );
     }

     TreeNode<T> *search( TreeNode<T> *p, T &target )
    {
        Node<TreeNode<T> *> *child = p->getChildren()->getHead();
        while ( child != NULL )
        {
          if (child->getData()->getData() == target){
            return child->getData();
          }

          child = child->getNext();
        }
      
      return NULL;
    }

    virtual void setRoot(TreeNode<T>* root)
    {
      this->root = root;
    }

    void serializeH( LinkedList<TreeNode<T>*> *list, string &str){
        if( list->getSize() == 0 )    return ;

        list->sort();
        Node<TreeNode<T>*> *n = list->getHead();

        while( n != NULL ){
            str += "{\"children\":[";
            serializeH( n->getData()->getChildren(), str );
            str += "],\"data\":\"";
            str += n->getData()->getData();
            str += "\"";
            if( n->getData()->getTerminal() ){
              str += ",\"end\":\"true\"}";
            }
            else
              str += "}";
        
            if( n != list->getTail() )
              str += ",";

            n = n->getNext();
        }
    }

    virtual string serialize()
    {
        if( this->root->getChildren()->getSize() == 0 )
            return "{\"root\":{\"children\":[],\"data\":\"\"}}";

        string result = "{\"root\":{\"children\":[";
        serializeH( this->root->getChildren(), result );
        result += "],\"data\":\"\"}}";

        return result;
    }
};

int main() {

  GeneralTree<char, string> *g = new GeneralTree<char, string>();
  
  string str = "";
  int insrt, check;

  vector<string> in, ch;

  cin >> insrt;
  cin >> check;
  cin.ignore(1, '\n');

  for ( int i = 0; i < insrt; i++ ){
    getline( cin, str ); 
    in.push_back( str );
  }

  for ( int i = 0; i < check; i++ ){
    getline( cin, str ); 
    ch.push_back( str );
  }

  for( string s : in ){
    g->insert( s );
  }


  for( string s : ch ){
    cout << g->wExists( s ) << endl;
  }

  cout << g->serialize();

  return 0;
}
