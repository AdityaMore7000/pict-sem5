#include<iostream>
using namespace std;
class Node{
    int id;
    Node *next;
    public:
    Node(int);
    friend class Ring;
};
class Ring{
    Node*head;
    public:
    Ring();
    void createRing(int);
    int getCoordinator();
};
Node::Node(int id = -1){
    this->id = id;
    this->next = NULL;
}
Ring::Ring(){
    this->head = NULL;
}
int main(){
cout<<"Hello World\n";
return 0;
}