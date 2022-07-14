#include <iostream>
#include <iterator>
#include <map>
#include<unordered_map>

using namespace std;

class Node {
public:
    int key;
    int value;
    Node *prev;
    Node *next;

    Node() {
        prev = nullptr;
        next = nullptr;
    }

    Node(int k, int val) {
        this->key = k;
        this->value = val;
        prev = nullptr;
        next = nullptr;
    }
};

class LinkedList {
public:
    Node *head, *tail;
    LinkedList()
    {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    void setRecentlyUsed(Node *node) {
        Node *temp1 = head->next;
        head->next = node;
        node->prev = head;
        node->next = temp1;
        temp1->prev = node;
    }

    void removeNode(Node *node) {
        Node *p = node->prev;
        Node *n = node->next;
        p->next = n;
        n->prev = p;
    }
    
    void updateRecentlyUsed(Node *node) {
        if(head->next == node)
            return;
        Node *temp1 = head->next;
        Node *temp2 = node->prev;
        Node *temp3 = node->next;
        head->next = node;
        node->prev =  head;
        node->next = temp1;
        temp1->prev = node;
        temp2->next = temp3;
        temp3->prev = temp2;
    }
};


class LRUCache {
public:
    int size;
    LinkedList cache;
    unordered_map<int, Node*> mp;

    
    LRUCache(int capacity) {
        this->size = capacity;
    }    
        
    bool isCapacityPermitted() {
        if(this->size == 0){
            //cout<< "Cache capacity = 0 cannot store any key-value pair."<<endl;
            return false;
        }   
        return true;
    }

    int get(int key) {
        if(mp.find(key) != mp.end())
        {
            cache.updateRecentlyUsed(mp[key]);
            // Node *n = cache.head->next;
            // while(n->next != NULL)
            // {
            //     cout<< n->key<< " ";
            //     n = n->next;
            // }
            // cout<<endl;
            return mp[key]->value;
        }
        return -1;
    }
    
    void set(int key, int value) {
        if(isCapacityPermitted() == false) {
            return;
        } 
        if(mp.find(key) != mp.end())
        {
            //cout << "Found" << endl;
            cache.removeNode(mp[key]);
            mp.erase(key);
        }

        if(mp.size() >= size)
        {
            mp.erase(cache.tail->prev->key);
            cache.removeNode(cache.tail->prev);
        }

        mp[key]=  new Node(key,value);
        cache.setRecentlyUsed(mp[key]);     
        
        // cout << "values added:" << key << " " << mp[key]->value <<endl;
        // Node *n = cache.head->next;
        // while(n->next != NULL)
        // {
        //     cout<< n->key<< " ";
        //     n = n->next;
        // }
        // cout<<endl;
        return;
    }
};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       

int main()
{
    int capacity, tests;
    // cout <<"Enter cache capacity: ";
    cin >> capacity >> tests;
    // if(capacity == 0)
    //     cout<<"Cache is initialised with 0 capacity. No key-value pairs will be stored. Choose Exit(3)."<< endl;
    LRUCache* obj = new LRUCache(capacity);
    
    while(tests--)
    {
        int optn;
        // cout <<"Choose operation to perform: \n 1. Enter 1 for set operation \n 2. Enter 2 for get operation \n 3. Exit " << endl;
        cin >> optn;
        
        if(optn == 2)
        {            
            int key, value;
            // cout <<"Enter key and value: ";
            cin >> key >> value;
            obj->set(key,value);
        } 
        else if(optn == 1)
        {
            int key;
            // cout <<"Enter key: ";
            cin >> key;
            int value = obj->get(key);
            cout << value << endl;
            // cout <<"Value: " << value << "\n";
        }
        else
            break;
    }

    return 0;
}

