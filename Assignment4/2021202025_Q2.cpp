#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

struct Node
{
    ll val;
    ll i;
};

class Heap
{
public:
    Node *elementsArray;
    ll heapSize;

    void MinHeapify(ll key);
    void MinHeapifyHelper(ll leftNode, ll rightNode, ll leftVal, ll rightVal, ll key);

    void replace(Node x)
    {
        elementsArray[0] = x;
        MinHeapify(0);
    }

    Heap(Node a[], ll length)
    {
        heapSize = length;
        elementsArray = a;
        ll k = (heapSize - 1) / 2;
        int i = k;
        for (i = 0; i >= 0; i--)
        {
            MinHeapify(k);
        }
    }
};

void Heap::MinHeapifyHelper(ll leftNode, ll rightNode, ll leftVal, ll rightVal, ll key)
{
    ll mini = key;
    if (rightNode < heapSize and rightVal < elementsArray[key].val)
    {
        mini = rightNode;
    }
    if (leftNode < heapSize and leftVal < elementsArray[mini].val)
    {
        mini = leftNode;
    }
    if (mini != key)
    {
        Node temp = elementsArray[key];
        elementsArray[key] = elementsArray[mini];
        elementsArray[mini] = temp;
        MinHeapify(mini);
    }
}

void Heap::MinHeapify(ll key)
{
    ll leftNode = 2 * key + 1;
    ll rightNode = 2 * key + 2;
    ll mini = key;
    ll leftVal = elementsArray[leftNode].val;
    ll rightVal = elementsArray[rightNode].val;

    MinHeapifyHelper(leftNode, rightNode, leftVal, rightVal, mini);
}

FILE *openFile(char *fileName, const char *mode)
{
    FILE *fp = fopen(fileName, mode);
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

void merge(ll arr[], ll low, ll mid, ll high)
{
    ll size1 = mid - low + 1;
    ll size2 = high - mid;
    // ll left[size1], right[size2];
    vector<ll> left(size1);
    vector<ll> right(size2);

    for (ll i = 0; i < size1; i++)
    {
        left[i] = arr[low + i];
    }
    for (ll i = 0; i < size2; i++)
    {
        right[i] = arr[mid + 1 + i];
    }
    ll i = 0, j = 0;
    ll k = low;
    while (i < size1 && j < size2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i += 1;
        }
        else
        {
            arr[k] = right[j];
            j += 1;
        }
        k += 1;
    }
    while (i < size1)
    {
        arr[k] = left[i];
        k += 1;
        i += 1;
    }
    while (j < size2)
    {
        arr[k] = right[j];
        k += 1;
        j += 1;
    }
}
void mergesort(long long int brr[], long long int l, long long int r)
{
    if (l >= r)
    {
        return;
    }

    ll mid = (l + r) / 2;

    mergesort(brr, l, mid);
    mergesort(brr, mid + 1, r);

    merge(brr, l, mid, r);
}

void mergefiles(ll runsize, ll files, char *output_file)
{
    FILE *in[files];
    ll i = 0;
    string mode = "r";

    for (i = 0; i < files; ++i)
    {
        char filename[6];
        snprintf(filename, sizeof(filename), "%lld", i);
        mode = "r";
        char outArr[] = "r";
        char *rr = outArr;
        in[i] = openFile(filename, mode.c_str());
    }

    mode = "w";
    char outArr[] = "w";
    char *wr = outArr;
    FILE *out = openFile(output_file, mode.c_str());

    Node *heap_arr = new Node[files];
    i = 0;
    while (i < files)
    {
        if (fscanf(in[i], "%lld ", &heap_arr[i].val) != 1)
            break;
        heap_arr[i].i = i;
        i++;
    }

    Heap minHeap(heap_arr, i);
    ll count = 0;
    for (; count != i;)
    {
        Node root = minHeap.elementsArray[0];
        fprintf(out, "%lld,", root.val);
        if (fscanf(in[root.i], "%lld ", &root.val) != 1)
        {
            root.val = INT_MAX;
            count += 1;
        }
        minHeap.replace(root);
    }

    ll x = 0;
    while (x < files)
    {
        fclose(in[x]);
        x++;
    }

    fclose(out);
}

void chunkcreater(ll runsize, ll files, char *inputFile)
{

    FILE *out[files];
    char filename[6];
    string mode = "r";
    char outArr[] = "r";
    char *rr = outArr;
    FILE *in = openFile(inputFile, mode.c_str());

    ll i = 0;
    ll *arr = (ll *)malloc(runsize * sizeof(ll));

    while (i < files)
    {
        snprintf(filename, sizeof(filename), "%lld", i);
        mode = "w";
        char outArr[] = "w";
        char *rw = outArr;
        out[i] = openFile(filename, mode.c_str());
        i++;
    }

    bool flag = true;
    ll nextout = 0;
    while (flag)
    {
        i = 0;
        while (i < runsize)
        {
            if (fscanf(in, "%lld,", &arr[i]) != 1)
            {

                flag = false;
                break;
            }
            i += 1;
        }

        mergesort(arr, 0, i - 1);
        ll j = 0;

        while (j < i)
        {
            fprintf(out[nextout], "%lld ", arr[j]);
            j += 1;
        }
        nextout += 1;

        if (!flag)
            break;
    }

    ll m = 0;
    while (m < files)
    {
        fclose(out[m]);
        m += 1;
    }

    fclose(in);
}

int main(int argc, char *argv[])
{

    char *inputFile = argv[1];
    char *outputFile = argv[2];

    ll ram = 5000000;
    ll partitions;

    FILE *f;
    f = fopen(inputFile, "r");
    fseek(f, 0, SEEK_END);
    long long length = (unsigned long)ftell(f);
    partitions = ceil(length / (ram * 1.0));
    fclose(f);

    chunkcreater(ram, partitions, inputFile);
    mergefiles(ram, partitions, outputFile);

    for (int i = 0; i < partitions; i++)
    {
        string temp = i + ".txt";
        remove(to_string(i).c_str());
    }

    return 0;
}