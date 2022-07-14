#include <iostream>
#include <sstream>
#include <vector>
#include <typeinfo>

using namespace std;

#define TABLE_SIZE 4999

// bool flag = false;

template <class X, class Y>
class unorderedMap
{
public:
    class HashNode
    {
    public:
        X key;
        Y value;
        HashNode *next;

        HashNode(X k, Y data)
        {
            key = k;
            value = data;
            next = NULL;
        }
    };

    HashNode *hash[TABLE_SIZE];
    int hashFunc(X key);
    int hashFunc2(X key);
    // HashNode* createHashNode(X key, Y data);
    void insert(X key, Y data);
    void erase(X key);
    bool find(X data);
    Y operator[](X key);

    unorderedMap()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            hash[i] = NULL;
        }
    }

    HashNode *createHashNode(X key, Y data)
    {
        HashNode *temp = new HashNode(key, data);
        return temp;
    }
};

template <class X, class Y>
int unorderedMap<X, Y>::hashFunc(X key)
{
    // stringstream ss(key);
    // string token;
    // vector <string>  tokens;
    // while (getline(ss, token, ' ')) {
    //     tokens.push_back(token);
    // }

    // for (int i = 0; i < tokens.size(); i++) {
    //     cout << token[i] << endl;
    // }
    ostringstream ss;
    ss << key;
    string s = ss.str();

    if (s.size() % 2)
    {
        const int mulFactor = 97;
        int factor = 1;
        int idx = 0;
        for (int i = 0; i < s.size(); i++)
        {
            // cout  << idx << endl;
            idx = (idx + (s[i] * factor)) % TABLE_SIZE;
            factor = (factor * mulFactor) % 100000007;
            // idx %= TABLE_SIZE;
            // cout << s[i] << " " << factor << " " << idx << endl;
            // factor = (factor * 10) % TABLE_SIZE;
            // cout << factor << endl;
        }

        // cout << "Hola" << endl;
        // cout << idx << endl;
        // cout << "Ciao" << endl;
        return idx;
    }

    auto i = hashFunc2(key);

    // // for (int i = 0; i < s.size(); i++)
    // // {
    // //     cout << s[i] << endl;
    // // }
    return i;
}

template <class X, class Y>
int unorderedMap<X, Y>::hashFunc2(X key)
{
    // stringstream ss(key);
    // string token;
    // vector <string>  tokens;
    // while (getline(ss, token, ' ')) {
    //     tokens.push_back(token);
    // }

    // for (int i = 0; i < tokens.size(); i++) {
    //     cout << token[i] << endl;
    // }
    ostringstream ss;
    ss << key;
    string s = ss.str();

    const int mulFactor = 89;
    int factor = 1;
    int idx = 0;
    for (int i = 0; i < s.size(); i++)
    {
        // cout  << idx << endl;
        idx = (idx + (s[i] * factor)) % TABLE_SIZE;
        factor = (factor * mulFactor) % 100000007;
    }
    // idx %= TABLE_SIZE;
    // cout << s[i] << " " << factor << " " << idx << endl;
    // factor = (factor * 10) % TABLE_SIZE;
    // cout << factor << endl;
    // cout << "HI" << endl;
    // cout << idx << endl;
    // cout << "BYE" << endl;

    // for (int i = 0; i < s.size(); i++)
    // {
    //     cout << s[i] << endl;
    // }

    return idx;
}

template <class X, class Y>
Y unorderedMap<X, Y>::operator[](X data)
{
    if (!hash[hashFunc(data)])
    {
        // cout << "Key doesn't exist" << endl;
        // flag = true;
        static Y temp;
        insert(data, temp);

        return temp;
        // cout << typeid(data).name() << endl;
        // if (typeid(Y).name() == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE") {
        //     insert(data, "");
        // }
        // insert(data, 0);
        // cout << isString << endl;
        // isString = false;
        // if (isString) {
        //     insert(data, "");
        //     return "";
        // }
        // else {
        //     insert(data, 0);
        //     return 0;
        // }
        // return 0;
    }
    else
    {
        HashNode *exstingHashNode = hash[hashFunc(data)];
        while (exstingHashNode != NULL)
        {
            if (exstingHashNode->key == data)
            {
                return exstingHashNode->value;
            }
            exstingHashNode = exstingHashNode->next;
        }
    }
    exit(0);
}

template <class X, class Y>
void unorderedMap<X, Y>::insert(X key, Y data)
{

    if (!hash[hashFunc(key)])
    {
        HashNode *temp = createHashNode(key, data);
        hash[hashFunc(key)] = temp;
    }

    else
    {

        HashNode *exstingHashNode = hash[hashFunc(key)];

        while (exstingHashNode->next != NULL)
        {

            if (exstingHashNode->key == key)
            {
                if (exstingHashNode->value != data)
                {
                    exstingHashNode->value = data;
                    return;
                }
                else
                {
                    return;
                }
            }
            exstingHashNode = exstingHashNode->next;
        }

        if (exstingHashNode->key == key)
        {
            if (exstingHashNode->value != data)
            {
                exstingHashNode->value = data;
                return;
            }
            return;
        }

        HashNode *temp = createHashNode(key, data);
        exstingHashNode->next = temp;
    }
}

template <class X, class Y>
void unorderedMap<X, Y>::erase(X key)
{
    if (!hash[hashFunc(key)])
    {
        return;
    }

    if (hash[hashFunc(key)]->key != key)
    {
        HashNode *exstingHashNode = hash[hashFunc(key)];

        while (exstingHashNode->next != NULL)
        {

            if (exstingHashNode->next->key == key)
            {
                HashNode *temp = exstingHashNode->next;
                exstingHashNode->next = temp->next;
                delete (temp);
                break;
            }

            exstingHashNode = exstingHashNode->next;
        }
    }
    else
    {
        cout << "Delete successful" << endl;
        HashNode *exstingHashNode = hash[hashFunc(key)];
        hash[hashFunc(key)] = hash[hashFunc(key)]->next;
        delete (exstingHashNode);
    }
}

template <class X, class Y>
bool unorderedMap<X, Y>::find(X data)
{
    if (!hash[hashFunc(data)])
    {
        return false;
    }
    else
    {
        HashNode *exstingHashNode = hash[hashFunc(data)];
        while (exstingHashNode != NULL)
        {
            if (exstingHashNode->key == data)
                return true;
            exstingHashNode = exstingHashNode->next;
        }
    }

    return false;
}

void solve(vector<string> arr, int k)
{
    unorderedMap<string, int> mp;

    // for (int i = 0; i < arr.size(); i++) {
    //     mp.insert(arr[i], 0);
    // }

    int count = 0;

    for (int i = 0; i < k; i++)
    {
        if (mp[arr[i]] == 0)
        {
            count++;
        }
        int oldVal = mp[arr[i]];
        oldVal++;
        mp.insert(arr[i], oldVal);
    }

    // for (int i = 0; i < k; i++) {
    //     cout << mp[arr[i]] << endl;
    // }
    cout << count << " ";

    for (int i = k; i < arr.size(); i++)
    {

        // cout << i << endl;

        if (mp[arr[i - k]] == 1)
        {
            count--;
        }

        int oldVal = mp[arr[i - k]];
        oldVal--;
        mp.insert(arr[i - k], oldVal);

        if (mp[arr[i]] == 0)
        {
            count++;
        }

        int oldVal2 = mp[arr[i]];
        oldVal2++;
        mp.insert(arr[i], oldVal2);

        cout << count << " ";
    }
}

void findCount()
{
    vector<int> nums = {1, 2, 3, 4, 5, 5, 6, 7, 8};
    vector<string> nums2 = {"Blue", "Blue", "Red", "Orange", "Yellow"};
    solve(nums2, 3);
}

int main()
{

    // unorderedMap<string, int> a;
    // a.insert("abc", 10);
    // a.insert("cde", 20);
    // a.insert("def", 30);
    // a.insert("cba", 40);
    // a.insert("cbac", 50);

    // // a.insert("cde", 20);
    // cout << a.hashFunc("abc") << endl;
    // cout << a.hashFunc("cde") << endl;
    // cout << a.hashFunc("def") << endl;
    // cout << a.hashFunc("cba") << endl;
    // cout << a.hashFunc2("cbac") << endl;
    // // // cout << a.hash[979]->value << endl;
    // cout << a["abc"] << endl;
    // cout << a["cde"] << endl;
    // cout << a["def"] << endl;
    // cout << a["cba"] << endl;
    // cout << a["cbac"] << endl;
    // cout << a.find("cbac") << endl;
    // // cout << a.hash[6]->value << endl;
    // a.erase("cbac");
    // cout << a.find("cbac") << endl;
    // // cout << a["cde"] << endl;
    // findCount();
    // cout << a["dgc"] << endl;

    // while (1) {

    //     cout << "1) Insert into map" << endl;
    //     cout << "2) Erase a key" << endl;
    //     cout << "3) Find a key value" << endl;
    //     cout << "4) Use map[key]" << endl;

    //     int choice;
    //     cin >> choice;

    //     if (choice == 1) {
    //         string key;
    //         int value;

    //         cin >> key >> value;
    //         a.insert(key, value);
    //     }
    //     else if (choice == 2) {
    //         string key;
    //         cin >> key;
    //         a.erase(key);
    //     }
    //     else if (choice == 3) {
    //         string key;
    //         cin >> key;
    //         cout << a.find(key) << endl;
    //     }
    //     else if (choice == 4) {
    //         string key;
    //         cin >> key;

    //         cout << a[key] << endl;
    //     }
    //     else {
    //         cout << "INVALID" << endl;
    //     }
    // }

    unorderedMap<int, string> a;
    a.insert(1, "abc");
    a.insert(2, "def");
    // a.insert(30, "def");
    // a.insert(40, "cba");
    // a.insert(50, "cbac");
    cout << a[1] << endl;
    a.erase(1);
    cout << a[1] << endl;
    cout << a.find(1) << endl;
    cout << a[2] << endl;
    a.erase(1);
    a.erase(1);

    // isString = true;

    // cout << a[10] << endl;
    // cout << a[20] << endl;
    // cout << a[30] << endl;
    // cout << a[40] << endl;
    // cout << a[60] << endl;
    // cout << a[50] << endl;

    // int n;
    // cin >> n;
    // if (n == 1) {
    //     findCount();
    // }

    // cout << a.hash[6]->value << endl;
    // cout << "----------------" << endl;
    // cout << a["abc"] << endl;
    // cout << a["cba"] << endl;
    // cout << a["cde"] << endl;
    // cout << "asfkasf" << endl;
    // cout << a["def"] << endl;

    // unorderedMap<float, string> b;
    // b.insert(4.2, "Manu");
    // b.insert(5.6, "Chicken");
    // cout << b.hashFunc(4.2) << endl;
    // cout << b[4.2] << endl;

    // cout << a.hashFunc(42) << endl;

    return 0;
}