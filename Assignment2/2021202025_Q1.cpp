#include <iostream>
#include <string>
using namespace std;

template <class T>
class TreeNode
{
public:
    T key;

    int height;
    int count;

    TreeNode<T> *parent;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode()
    {
        count = 0;
        height = 0;
        parent = NULL;
        left = NULL;
        right = NULL;
    }

    TreeNode(T k)
    {
        height = 0;
        count = 1;
        key = k;
        parent = NULL;
        left = NULL;
        right = NULL;
    }
};

template <typename T>
class AVL
{
public:
    AVL();
    AVL(T &key);
    void print();
    // void display(bool detailFlag = false);
    void searchKey(T data);
    void insert(T key);
    void deleteVal(T key);
    void countOccurences(T data);
    void lower_bound(T data);
    void upper_bound(T data);
    void closestValue(T data);
    void KthLargest(int data);
    void kthLargestUtil(TreeNode<T> *root, int k, int &c);
    void elementsInRange(T lowerLimit, T upperLimit);
    int elementsInRangeUtil(TreeNode<T> *node, int &count,
                            T &lowerLimit, T &upperLimit);
    // TreeNode<T>* deleteNode_util(TreeNode<T>* root, T key);
    void moveSubTree(TreeNode<T> *x, TreeNode<T> *y);
    void countSmaller(TreeNode<T> *node, T key, int &c, bool &found);
    int countINRange_util(TreeNode<T> *root, T key, TreeNode<T> *&tmp);

    // TreeNode<T>* kthLargestUtil(TreeNode<T>* root, int& k) {
    //     if (!root or !root->right or !k) {
    //         return root;
    //     }

    //     if (k - 1 == root->right->height) {
    //         return root;
    //     }

    //     if (k > root->right->height) {
    //         k = k - 1 - root->right->height;
    //         return kthLargestUtil(root->left, k);
    //     }

    //     else if (k == root->right->height) {
    //         k -= root->right->height;
    //         return kthLargestUtil(root->right, k);
    //     }

    //     else {
    //         return kthLargestUtil(root->right, k);
    //     }
    // }

protected:
    TreeNode<T> *root;

    TreeNode<T> *getMinNode(TreeNode<T> *node);
    TreeNode<T> *getMaxNode(TreeNode<T> *node);

    void insertionBalance(TreeNode<T> *node);
    void deletionBalance(TreeNode<T> *node);

    void InOrder(TreeNode<T> *node);

    void LLRotation(TreeNode<T> *x);
    void RRRotation(TreeNode<T> *x);

    inline int findMax(int x, int y)
    {
        return (x > y) ? x : y;
    };

    inline int getBalanceFactor(const TreeNode<T> *node)
    {
        if (node != NULL)
        {
            return getHeight(node->left) - getHeight(node->right);
        }
        return 0;
    };

    inline int getHeight(const TreeNode<T> *node)
    {
        if (node != NULL)
        {
            return node->height;
        }
        return -1;
    };
};

template <class T>
AVL<T>::AVL()
{
    root = NULL;
}

template <class T>
AVL<T>::AVL(T &key)
{
    root = new TreeNode<T>(key);
}

template <class T>
void AVL<T>::print()
{
    InOrder(root);
    cout << endl;
}

template <class T>
void AVL<T>::insert(T data)
{

    TreeNode<T> *prev = NULL;
    TreeNode<T> *temp = root;

    bool flag = false;

    while (temp != NULL)
    {

        prev = temp;

        if (data < temp->key)
        {
            temp = temp->left;
        }

        else if (data > temp->key)
        {
            temp = temp->right;
        }

        else
        {
            flag = true;
            break;
        }
    }

    if (!flag)
    {

        TreeNode<T> *node = new TreeNode<T>(data);
        node->parent = prev;

        if (!prev)
        {
            root = node;
        }
        else if (node->key < prev->key)
        {
            prev->left = node;
        }
        else
        {
            prev->right = node;
        }

        TreeNode<T> *temp = node->parent;
        TreeNode<T> *currNode = node;

        while (temp != NULL)
        {
            temp->height = 1;
            int leftH = getHeight(temp->left);
            int rightH = getHeight(temp->right);
            temp->height += findMax(leftH, rightH);

            TreeNode<T> *tempParent = temp->parent;
            if (getBalanceFactor(tempParent) > 1 or getBalanceFactor(tempParent) < -1)
            {
                if (temp == tempParent->right)
                {

                    if (currNode == tempParent->right->left)
                    {
                        RRRotation(temp);
                        LLRotation(tempParent);
                    }

                    else if (currNode == tempParent->right->right)
                    {
                        LLRotation(tempParent);
                    }
                }

                else if (temp == tempParent->left)
                {

                    if (currNode == tempParent->left->right)
                    {
                        LLRotation(temp);
                        RRRotation(tempParent);
                    }

                    else if (currNode == tempParent->left->left)
                    {
                        RRRotation(tempParent);
                    }
                }

                break;
            }

            currNode = currNode->parent;
            temp = temp->parent;
        }
    }
    else
    {
        // cout << "PrevCount" << endl;
        // cout << data << endl;
        prev->count++;
        // cout  << prev->count << endl;
    }
}

template <class T>
void AVL<T>::deleteVal(T data)
{
    // cout << "In Delete" << endl;
    TreeNode<T> *temp = root;

    while (temp != NULL)
    {
        if (temp->key > data)
        {
            temp = temp->left;
        }
        else if (temp->key < data)
        {
            temp = temp->right;
        }
        else
        {
            break;
        }
    }

    if (!temp)
    {
        cout << "Node not found";
    }

    else
    {
        // cout << "In Delete" << endl;

        // if (temp->count > 1) {
        //     temp->count -= 1;
        // }

        if (!temp->left)
        {
            moveSubTree(temp, temp->right);
            deletionBalance(temp->right);
            delete (temp);
        }

        else if (!temp->right)
        {
            moveSubTree(temp, temp->left);
            deletionBalance(temp->left);
            delete (temp);
        }

        else
        {
            // cout << "In Delete" << endl;

            TreeNode<T> *temp2 = getMinNode(temp->right);
            TreeNode<T> *temp2Parent = temp2->parent;
            TreeNode<T> *temp2Right = temp2->right;
            TreeNode<T> *temp2Left = temp2->left;

            if (temp2Parent != temp)
            {
                moveSubTree(temp2, temp2->right);
                temp2->right = temp->right;
                temp2->right->parent = temp2;
            }

            moveSubTree(temp, temp2);

            temp2->left = temp->left;
            temp2->left->parent = temp2;

            deletionBalance(temp2);

            // cout << "In Delete" << endl;

            delete (temp);
        }
    }
}

template <class T>
void AVL<T>::moveSubTree(TreeNode<T> *a, TreeNode<T> *b)
{
    // cout << "move Sub" << endl;
    auto temp = a->parent;

    if (!a->parent)
    {
        root = b;
    }
    else if (a == temp->right)
    {
        a->parent->right = b;
    }
    else if (a == temp->left)
    {
        a->parent->left = b;
    }

    if (b != NULL)
        b->parent = a->parent;
    // cout << "move Sub" << endl;
}

template <class T>
void AVL<T>::deletionBalance(TreeNode<T> *node)
{

    // cout << "deletion Balance" << endl;
    TreeNode<T> *temp = node;

    while (temp != NULL)
    {
        temp->height = 1;
        int leftH = getHeight(temp->left);
        int rightH = getHeight(temp->right);
        temp->height += findMax(leftH, rightH);

        if (getBalanceFactor(temp) > 1 || getBalanceFactor(temp) < -1)
        {
            // cout << "deletion Balance" << endl;

            TreeNode<T> *a;
            TreeNode<T> *b;
            TreeNode<T> *c;

            a = temp;

            bool flag = 0;

            if (a->right == 0)
            {
                flag = 1;
                b = a->left;
            }

            else if (a->left == 0)
            {
                flag = 1;
                b = a->right;
            }

            if (!flag)
            {
                int alHeight = a->left->height;
                // cout << "deletion Balance" << endl;

                // cout << a->right->height << endl;

                int arHeight = a->right->height;
                // cout << "deletion Balance" << endl;
                if (alHeight < arHeight)
                {
                    b = a->right;
                }
                else
                {
                    b = a->left;
                }
            }

            // cout << "deletion Balance" << endl;

            flag = 0;

            if (b->right == 0)
            {
                flag = 1;
                c = b->left;
            }

            else if (b->left == 0)
            {
                flag = 1;
                c = b->right;
            }

            // cout << "deletion Balance" << endl;

            if (!flag)
            {
                int blHeight = b->left->height;
                int brHeight = b->right->height;

                if (blHeight < brHeight)
                {
                    c = b->right;
                }
                else if (blHeight > brHeight)
                {
                    c = b->left;
                }
                else
                {
                    if (b == a->left)
                    {
                        c = b->left;
                    }
                    else
                    {
                        c = b->right;
                    }
                }
            }

            if (b == a->right)
            {
                if (c == a->right->left)
                {
                    RRRotation(b);
                    LLRotation(a);
                }
                else if (c == a->right->right)
                {
                    LLRotation(a);
                }
            }

            else if (b == a->left)
            {
                if (c == a->left->right)
                {
                    LLRotation(b);
                    RRRotation(a);
                }
                else if (c == a->left->left)
                {
                    RRRotation(a);
                }
            }
        }

        temp = temp->parent;
    }
    // cout << "deletion Balance" << endl;
}

template <class T>
void AVL<T>::LLRotation(TreeNode<T> *rotateOver)
{
    TreeNode<T> *temp = rotateOver->right;

    temp->parent = rotateOver->parent;

    if (!rotateOver->parent)
    {
        root = temp;
    }

    else if (rotateOver == rotateOver->parent->left)
    {
        rotateOver->parent->left = temp;
    }

    else
    {
        rotateOver->parent->right = temp;
    }

    rotateOver->right = temp->left;
    if (temp->left != NULL)
    {
        temp->left->parent = rotateOver;
    }

    temp->left = rotateOver;
    rotateOver->parent = temp;

    temp->height = 1;
    int leftH = getHeight(temp->left);
    int rightH = getHeight(temp->right);
    temp->height += findMax(leftH, rightH);

    rotateOver->height = 1;
    int leftH2 = getHeight(rotateOver->left);
    int rightH2 = getHeight(rotateOver->right);
    rotateOver->height += findMax(leftH2, rightH2);
    // cout << "__________________________" << endl;
    // cout << getHeight(temp->left) << " " << leftH  << endl;
    // cout << getHeight(temp->right) << " " << rightH << endl;
    // cout << (1 + findMax(getHeight(temp->left), getHeight(temp->right))) << " " << 1 + findMax(leftH, rightH) << endl;
    // cout << "___________________________" << endl;
}

template <class T>
void AVL<T>::RRRotation(TreeNode<T> *rotateOver)
{
    TreeNode<T> *temp = rotateOver->left;

    temp->parent = rotateOver->parent;

    if (!rotateOver->parent)
    {
        root = temp;
    }

    else if (rotateOver == rotateOver->parent->right)
    {
        rotateOver->parent->right = temp;
    }

    else
    {
        rotateOver->parent->left = temp;
    }

    rotateOver->left = temp->right;
    if (temp->right != NULL)
    {
        temp->right->parent = rotateOver;
    }

    temp->right = rotateOver;
    rotateOver->parent = temp;

    temp->height = 1;
    int leftH = getHeight(temp->left);
    int rightH = getHeight(temp->right);
    temp->height += findMax(leftH, rightH);

    rotateOver->height = 1;
    int leftH2 = getHeight(rotateOver->left);
    int rightH2 = getHeight(rotateOver->right);
    rotateOver->height += findMax(leftH2, rightH2);
}

template <class T>
TreeNode<T> *AVL<T>::getMaxNode(TreeNode<T> *tempNode)
{
    while (tempNode->right != NULL)
    {
        tempNode = tempNode->right;
    }
    return tempNode;
}

template <class T>
TreeNode<T> *AVL<T>::getMinNode(TreeNode<T> *tempNode)
{
    while (tempNode->left != NULL)
    {
        tempNode = tempNode->left;
    }
    return tempNode;
}

template <class T>
void AVL<T>::searchKey(T data)
{
    TreeNode<T> *temp = root;

    while (temp != NULL)
    {
        if (temp->key > data)
        {
            temp = temp->left;
        }
        else if (temp->key < data)
        {
            temp = temp->right;
        }
        else
        {
            cout << "Found";
            return;
        }
    }

    cout << "Not Found";
}

template <class T>
void AVL<T>::countOccurences(T data)
{
    // cout << data << endl;
    TreeNode<T> *temp = root;
    while (temp != NULL)
    {
        // cout << temp->key << endl;
        if (temp->key > data)
        {
            temp = temp->left;
        }
        else if (temp->key < data)
        {
            temp = temp->right;
        }
        else
        {
            cout << "Found"
                 << " " << temp->count;
            return;
        }
    }

    cout << "Not Found";
}

template <class T>
void AVL<T>::lower_bound(T data)
{
    // cout << "HERE" << endl;
    TreeNode<T> *temp = root;

    if (!temp)
        return;

    auto minNode = getMinNode(temp);
    // if (data < minNode->key) {
    //     cout << "Out of bounds";
    //     return;
    // }

    auto maxNode = getMaxNode(temp);
    if (data > maxNode->key)
    {
        cout << "Out of bounds";
        return;
    }

    T ans;
    while (temp != NULL)
    {
        if (data < temp->key)
        {
            ans = temp->key;
            temp = temp->left;
        }
        else if (data > temp->key)
        {
            temp = temp->right;
        }
        else
        {
            ans = temp->key;
            break;
        }
    }

    cout << "Lower Bound: " << ans;
}

template <class T>
void AVL<T>::upper_bound(T data)
{
    TreeNode<T> *temp = root;

    if (!root)
        return;

    // auto minNode = getMinNode(temp);
    // if (data < minNode->key) {
    //     cout << "Out of bounds";
    //     return;
    // }

    auto maxNode = getMaxNode(temp);
    if (data >= maxNode->key)
    {
        cout << "Out of bounds";
        return;
    }

    T ans;
    while (temp != NULL)
    {
        if (data < temp->key)
        {
            ans = temp->key;
            temp = temp->left;
        }
        else if (data >= temp->key)
        {
            temp = temp->right;
        }
    }

    cout << "Upper Bound: " << ans;
}

template <class T>
void AVL<T>::closestValue(T data)
{

    TreeNode<T> *temp = root;

    if (!temp)
        return;

    auto minNode = getMinNode(temp);
    if (data < minNode->key)
    {
        cout << "Closest: " << minNode->key;
        return;
    }

    auto maxNode = getMaxNode(temp);
    if (data > maxNode->key)
    {
        cout << "Closest: " << maxNode->key;
        return;
    }

    T leftData = minNode->key;
    T rightData = maxNode->key;

    while (temp != NULL)
    {

        if (data < temp->key)
        {
            rightData = temp->key;
            temp = temp->left;
        }
        else if (data > temp->key)
        {
            leftData = temp->key;
            temp = temp->right;
        }
        else
        {
            rightData = temp->key;
            break;
        }
    }

    if ((data + data) > (leftData + rightData))
    {
        cout << "Closest: " << rightData;
        return;
    }
    else
    {
        cout << "Closest: " << leftData;
        return;
    }
}

template <class T>
void AVL<T>::kthLargestUtil(TreeNode<T> *root, int k, int &count)
{
    if (root == NULL || count >= k)
        return;

    kthLargestUtil(root->right, k, count);

    count++;
    if (count == k)
    {
        cout << "K'th largest element " << root->key << endl;
        return;
    }

    kthLargestUtil(root->left, k, count);
}

template <class T>
void AVL<T>::KthLargest(int data)
{
    int count = 0;
    kthLargestUtil(root, data, count);
    // auto result = kthLargestUtil(root, data);
    // cout << "K'th largest element " << result->key << endl;
}

// template <class T>
// int AVL<T>::countINRange_util(TreeNode<T> *root, T key, TreeNode<T> *&tmp) {
//     if (!root)
//         return 0;
//     if (root->val == key)
//         return root->count;
//     else if (root->val > key) {
//         //tmp=root;
//         return countINRange_util(root->left, key, tmp);
//     }
//     else {
//         tmp = root;
//         return countINRange_util(root->right, key, tmp);
//     }
// }

// template <class T>
// void AVL<T>::countSmaller(TreeNode<T> *root, T key, int &c, bool &found) {
//     if (root) {
//         countSmaller(root->left, key, c, found);
//         if (root->key <= key) {
//             c++;
//         }
//         if (root->key == key) {
//             found = true;
//         }
//         countSmaller(root->right, key, c, found);
//     }
// }

// template <class T>
// int AVL<T>::elementsInRange(T low, T high) {
//     int a, b;
//     a = b = 0;
//     bool lowFound = false, highFound = false;
//     countSmaller(root, low, a, lowFound);
//     countSmaller(root, high, b, highFound);
//     if (!lowFound && !highFound)
//         return b - a;
//     else if (lowFound && highFound)
//         return b - a + 1;
//     else if (!lowFound && highFound)
//         return b - a;
//     else
//         return b - a + 1;
// }

template <class T>
int AVL<T>::elementsInRangeUtil(TreeNode<T> *node, int &count, T &lowerLimit, T &upperLimit)
{

    if (!node)
        return 0;

    if (node->key == lowerLimit and node->key == upperLimit)
        return node->count;

    if (node->key >= lowerLimit && node->key <= upperLimit)
    {
        count = elementsInRangeUtil(node->left, count, lowerLimit, upperLimit) + node->count + elementsInRangeUtil(node->right, count, lowerLimit, upperLimit);
    }

    else if (node->key > lowerLimit)
    {
        count = elementsInRangeUtil(node->right, count, lowerLimit, upperLimit);
    }

    else
    {
        count = elementsInRangeUtil(node->right, count, lowerLimit, upperLimit);
    }

    return count;
}

template <class T>
void AVL<T>::elementsInRange(T lowerLimit, T upperLimit)
{
    TreeNode<T> *node = root;
    int count = 0;
    auto result = elementsInRangeUtil(node, count, lowerLimit, upperLimit);

    cout << "Number of elements in given range: " << result;
}

class tempObj
{
public:
    int id;
    string name;

    tempObj()
    {
        id = 0;
        name = "";
    }

    tempObj(int newId, string newName)
    {
        id = newId;
        name = newName;
    }

    bool operator<=(const tempObj &o)
    {
        return this->id <= o.id;
    }

    bool operator>=(const tempObj &o)
    {
        return this->id >= o.id;
    }

    bool operator==(const tempObj &o)
    {
        return this->id == o.id;
    }

    bool operator!=(const tempObj &o)
    {
        return this->id != o.id;
    }

    bool operator>(const tempObj &o)
    {
        return this->id > o.id;
    }

    bool operator<(const tempObj &o)
    {
        return this->id < o.id;
    }

    int operator+(const tempObj &o)
    {
        return this->id + o.id;
    }

    // void print() {
    //     cout << this->id << " " << this->name;
    // }
};

ostream &operator<<(ostream &os, const tempObj &o)
{
    os << o.id << ":" << o.name;
    return os;
}

template <class T>
void AVL<T>::InOrder(TreeNode<T> *node)
{

    if (!node)
        return;

    InOrder(node->left);

    int i = 0;
    while (i < node->count)
    {
        cout << node->key << " ";
        i++;
    }

    InOrder(node->right);
}

int main()
{
    AVL<double> t;
    t.insert(11);
    t.insert(10);
    t.insert(9);
    t.insert(8);
    t.insert(7);
    t.insert(6);
    t.insert(6);
    t.insert(6);
    t.insert(5);
    t.insert(4);
    t.insert(4);
    t.insert(0);
    t.insert(0);
    t.insert(-1);
    t.insert(-1);
    // t.insert("bcd");
    // t.insert("abc");
    t.print();

    t.countOccurences(0);
    cout << endl;
    t.searchKey(0);
    cout << endl;
    t.lower_bound(-2);
    cout << endl;
    t.upper_bound(-2);
    cout << endl;
    t.lower_bound(11);
    cout << endl;
    t.upper_bound(11);
    cout << endl;
    t.lower_bound(12);
    cout << endl;
    t.upper_bound(12);
    cout << endl;
    t.closestValue(5.6);
    cout << endl;

    t.deleteVal(6);
    t.deleteVal(7);
    t.deleteVal(8);
    t.deleteVal(-1);
    t.deleteVal(0);
    t.deleteVal(4);
    t.deleteVal(5);
    t.deleteVal(9);
    t.deleteVal(10);
    t.deleteVal(11);
    t.deleteVal(12);

    cout << endl;
    t.print();

    t.searchKey(11.5);
    cout << endl;
    t.countOccurences(10.5);
    cout << endl;
    t.lower_bound(6.3);
    cout << endl;
    t.upper_bound(6.3);
    cout << endl;
    t.closestValue(5.9);
    cout << endl;
    t.KthLargest(2);
    cout << endl;
    t.elementsInRange(0, 12);
    cout << endl;
    t.KthLargest(1);
    t.KthLargest(2);
    t.KthLargest(3);
    t.KthLargest(4);
    t.KthLargest(5);

    // Stringy testing
    cout << endl;
    cout << endl;
    AVL<string> st;
    st.insert("bcd");
    st.insert("abc");
    st.insert("defg");
    st.insert("dfp");
    st.insert("defg");

    st.print();
    st.searchKey("bced");
    cout << endl;
    st.countOccurences("dfp");
    cout << endl;
    st.lower_bound("defg");
    cout << endl;
    st.upper_bound("defg");
    cout << endl;
    st.KthLargest(4);
    st.elementsInRange("abc", "z");

    cout << endl;
    cout << "---------------------------------" << endl;

    AVL<tempObj> ot;

    tempObj obj2(2, "B");
    tempObj obj3(3, "C");
    tempObj obj1(1, "A");
    tempObj obj4(5, "D");
    tempObj obj5(6, "E");
    tempObj obj6(4, "F");
    tempObj obj7(9, "G");
    tempObj obj8(10, "H");
    tempObj obj9(12, "I");
    tempObj obj11(15, "P");
    tempObj obj10(12, "I");

    ot.insert(obj1);
    ot.insert(obj2);
    ot.insert(obj3);
    ot.insert(obj4);
    ot.insert(obj5);
    ot.insert(obj6);
    ot.insert(obj7);
    ot.insert(obj8);
    ot.insert(obj9);
    ot.insert(obj11);
    ot.insert(obj10);

    ot.print();

    ot.deleteVal(obj1);
    // ot.deleteVal(obj9);
    ot.deleteVal(obj6);
    cout << endl;
    ot.print();

    ot.searchKey(obj2);
    cout << endl;
    ot.countOccurences(obj9);
    // cout << endl;
    t.lower_bound(6.3);
    cout << endl;
    t.upper_bound(6.3);
    cout << endl;
    t.closestValue(5.9);
    cout << endl;
    t.KthLargest(8);
    // cout << endl;
    t.elementsInRange(4.1, 9);
}
