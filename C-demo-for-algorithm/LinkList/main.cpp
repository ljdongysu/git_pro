#include <iostream>
#include <vector>
struct Node{
    Node *next;
    int value;
    Node(int tempvalue = 0){
        value = tempvalue;
        next = nullptr;
    }
};

Node *mergeNewTwo(Node *list1, Node *list2)
{
    Node *newList = nullptr;
    Node *p1 = list1;
    Node *p2 = list2;
    if(p1->value > p2->value)
    {
        newList = p2;
        p2 = p2->next;
    }
    else {
        newList = p1;
        p1 = p1->next;
    }

    Node *temp = newList;

    while (p1 != nullptr && p2 != nullptr) {
        if(p1->value < p2->value)
        {
            temp->next = p1;
            p1 = p1->next;
            temp = temp->next;

        }
        else
        {
            temp->next = p2;
            p2 = p2->next;
            temp = temp->next;
        }
    }
    if (p1 != nullptr) {
        temp->next = p1;
    }
    if(p2 != nullptr)
    {
        temp->next = p2;
    }
    return newList;
}

Node * creatNodeList(std::vector<int> arr)
{
    if(arr.size() == 0)
    {
        return new Node();
    }
    Node *nodeList = new Node(arr[0]);
    Node *resultList = nodeList;
    for(int i = 1; i < arr.size(); ++i)
    {
        nodeList->next = new Node(arr[i]);
        nodeList = nodeList->next;
    }
    nodeList->next = nullptr;
    return resultList;
}
void printNode(Node *node)
{
    Node *p = node;
    while (p != nullptr) {
        std::cout<<p->value<<" ";
        p = p->next;
    }
    std::cout<<std::endl;
}
int main(){
    std::vector<int> a = {1,2,3,4,5};
    Node *pa = creatNodeList(a);
    std::vector<int> b = {2,4,6,8,10,12,14};
//    printNode(pa);
    Node *pb = creatNodeList(b);
    Node *combineab = mergeNewTwo(pa,pb);
    printNode(combineab);
    return 0;

}
