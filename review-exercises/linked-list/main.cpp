#include <iostream>
using namespace std;
  
class List
{
private:
    class Node
    {
    public:
        Node(int _data,Node *n = nullptr,Node *p = nullptr) 
            : data(_data),next(n),previous(p) {};
        int data;
        Node *next;
        Node *previous;
    };
public:
    class Iterator
    {
    public:
        int get_element()
        {
            return current->data;
        }
        void goto_next()
        {
            if(current != NULL)
                current = current->next;
        }
        bool has_more_elements()
        {
            return current != NULL;
        }
    friend class List;
    private:
        Node *current;
        List *list;
        Iterator(Node *_current,List *_list) : current(_current), list(_list) {};
    };
public:
    List();
    ~List();
    //Copy constructor
    List(const List&);
    List& operator=(const List &l);
    void print();
    void push_front(int x);
    void push_back(int x);
    Iterator find(int x);
    Iterator ger_iterator(){return Iterator(head,this);}
private:
    Node *head;
    Node *last;
    void remove_nodes();
    void make_copy(Node *_head);
    Node* find_node(List::Node *_head,int x) const;
};

List::List()
{
    head = nullptr;
    last = nullptr;
}

List::List(const List& l)
{
    make_copy(l.head);
}

List& List::operator=(const List &l)
{
    if(&l != this)
        make_copy(l.head);
    return *this;
}

List::Iterator List::find(int x)
{
    return Iterator(find_node(head,x),this);
}

Node* List::find_node(List::Node *_head,int x) const
{
    Node *found = nullptr;
    Node *n = _head;
    while(n != nullptr)
    {
        if(x == n->data)
        {
            found = n;
            break;
        }
        n = n->next;
    }
    return found;
}

void List::push_front(int x)
{
    Node *new_node = new Node(x);
    new_node->next = head;
    if (head != NULL)
        head->previous = new_node;
    head = new_node;
    if (last == NULL)
        last = new_node;
}

void List::push_back(int x)
{
    if (head == NULL)
        push_front(x);
    else {
        Node *new_node = new Node(x);
        new_node->previous = last;
        last->next = new_node;
        last = new_node;
    }
}

void List::make_copy(Node *_head)
{
    bool is_head = true;
    Node *n = _head;
    Node *prev = nullptr;
    while(n != nullptr)
    {
        Node *new_node = new Node(n->data,nullptr,prev);
        prev = new_node;
        if(is_head)
            head = new_node;
        else
            is_head = false;
        if(n->next == nullptr)
            last = new_node;
        n = n->next;
    }
}

List::~List()
{
    remove_nodes();
}

void List::remove_nodes()
{
    Node *n = head;
    while(n != nullptr)
    {
        Node *temp = n;
        n = n->next;
        delete temp;
    }
    head = nullptr;
    last = nullptr;
}

void List::print()
{
    for(Node *node = head;node != nullptr;node = node->next)
        cout << node->data << " ";
}

int main()
{

    return 0;
}