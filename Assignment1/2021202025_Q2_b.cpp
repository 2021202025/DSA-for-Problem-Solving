#include <iostream>
#include <map>

using namespace std;

class Freq_Node {
public:
    int value;
    int key;
    int freq;
    Freq_Node *next;
    Freq_Node *prev;

    Freq_Node()
    {
        next = nullptr;
        prev = nullptr;
    }

    Freq_Node(int k, int v) {
        this->key = k;
        this->value = v;
        this->freq = 1;
        next = nullptr;
        prev = nullptr;
    }
};


class LinkedList {
public:
    Freq_Node *head, *tail;
    int size;
    LinkedList()
    {
        head = new Freq_Node();
        tail = new Freq_Node();
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    void addToFront(Freq_Node *node) {
        Freq_Node *temp1 = head->next;
        head->next = node;
        node->prev = head;
        node->next = temp1;
        temp1->prev = node;
        size++;
    }

    void removeNode(Freq_Node *node) {
        Freq_Node *p = node->prev;
        Freq_Node *n = node->next;
        p->next = n;
        n->prev = p;
        size--;
    }
    
};

class LFUCache
{
public:
    map<int, Freq_Node*> bykey_mp;
    map<int, LinkedList*> freq_mp;

    int minfreq, size, curr_size;

    LFUCache(int capacity) {
        size = capacity;
        curr_size = 0;
        minfreq = 0;
    }
 
    bool isCapacityPermitted() {
        if(this->size == 0){
            // cout<< "Cache capacity = 0 cannot store any key-value pair."<<endl;
            return false;
        }   
        return true;
    }

    void updateMap(Freq_Node * node) {
        freq_mp[node->freq]->removeNode(node);
        bykey_mp.erase(node->key);
        if(node->freq == minfreq && freq_mp[node->freq]->size == 0)        
            minfreq++;
        LinkedList *next_high_freq = new LinkedList();
        if(freq_mp.find(node->freq +1) != freq_mp.end()) {
            next_high_freq = freq_mp[node->freq +1];
        }
        node->freq++;
        next_high_freq->addToFront(node);
        bykey_mp[node->key] =  node;
        freq_mp[node->freq] = next_high_freq;
        return;
    }

    void set(int key, int val) {
        if(isCapacityPermitted() == false) {
            return;
        } 
        if(bykey_mp.find(key) != bykey_mp.end())
        {
            bykey_mp[key]->value = val;
            updateMap(bykey_mp[key]);
        }
        else {
            if(curr_size == size) {
                bykey_mp.erase(freq_mp[minfreq]->tail->prev->key);
                freq_mp[minfreq]->removeNode(freq_mp[minfreq]->tail->prev);
                curr_size--;
            }
            minfreq = 1;
            LinkedList *new_list = new LinkedList();
            if(freq_mp.find(minfreq) != freq_mp.end()) {
                new_list = freq_mp[minfreq];
            }
            Freq_Node * new_node = new Freq_Node(key, val);
            new_list->addToFront(new_node);
            bykey_mp[key] = new_node;
            freq_mp[minfreq] = new_list;

            curr_size++;

            //Printing minimum frequency nodes in frequency list
            // cout<<"New minimum freq: "<<minfreq<< endl;
            // Freq_Node *n = new_list->head->next;
            // while(n->next != NULL)
            // {
            //     cout<< n->key<< " ";
            //     n = n->next;
            // }
            // cout<<endl;
        }
        return;
    }

    int get(int key) {
        if(bykey_mp.find(key) != bykey_mp.end())
        {
            updateMap(bykey_mp[key]);
            // cout<<"New Freq of this node after getting the value : "<< bykey_mp[key]->freq << endl;
            // cout<<"New minimum freq: "<<minfreq<< endl;
            // Freq_Node *n = freq_mp[bykey_mp[key]->freq]->head->next;
            // while(n->next != NULL)
            // {
            //     cout<< n->key<< " ";
            //     n = n->next;
            // }
            // cout<<endl;
            return bykey_mp[key]->value;
        }
        return -1;
    }
};


int main() {
    int capacity;    
    int tests;
    // cout<<"Enter cache capacity : ";
    cin>> capacity >> tests;
    // if(capacity == 0)
    //     cout<<"Cache is initialised with 0 capacity. No key-value pairs will be stored. Choose Exit(3)."<< endl;
    LFUCache* obj = new LFUCache(capacity);



    while(tests--)
    {
        int optn;
        // cout <<"Choose operation to perform: \n 1. Enter 1 for set operation \n 2. Enter 2 for get operation \n 3. Exit" << endl;
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