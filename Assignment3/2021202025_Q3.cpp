#include <iostream>
#include <string>

using namespace std;

int r;
int c;

struct Trie
{
    Trie *children[26];
    string word;
    bool isleaf;

    Trie()
    {

        word = "";
        isleaf = false;

        for (int i = 0; i < 26; i++)
        {
            children[i] = NULL;
        }
    }
};

void insert(Trie *root, string word)
{
    Trie *temp = root;
    // cout << "AAAAAAAAA" << endl;

    for (char ch : word)
    {
        // cout << "AAAAAAAAA" << endl;

        if (!temp->children[ch - 'a'])
        {
            // cout << "BBBBBBBBBBBBB" << endl;
            temp->children[ch - 'a'] = new Trie();
        }

        // cout << "BBBBBBBBBBBBB" << endl;

        temp = temp->children[ch - 'a'];
    }
    temp->isleaf = true;
    temp->word = word;
}

bool search(Trie *root, string word)
{
    Trie *temp = root;
    for (char ch : word)
    {
        // cout << ch << endl;
        if (!temp->children[ch - 'a'])
        {
            return false;
        }
        temp = temp->children[ch - 'a'];
    }

    if (temp->isleaf)
    {
        return true;
    }
    return false;
}

void dfs(char **grid, int i, int j, Trie *p, string result[], int &k)
{
    // cout << "AAAAAAAa" << endl;
    char ch = grid[i][j];
    // cout << ch << endl;

    if (ch == '#' || !p->children[ch - 'a'])
        return;

    p = p->children[ch - 'a'];
    // cout << p->word << endl;

    if (p->word.size() > 0)
    {
        // cout << p->word << endl;
        result[k] = p->word;
        // cout << result[k] << " " << k << endl;
        k++;
        p->word = "";
    }

    grid[i][j] = '#';

    if (i > 0)
    {
        // cout << "asfasnf" << endl;
        dfs(grid, i - 1, j, p, result, k);
    }

    if (j > 0)
    {
        // cout << "asfasnf" << endl;
        dfs(grid, i, j - 1, p, result, k);
    }
    // cout << i << " " << r << endl;
    if (i < r - 1)
    {
        // cout << "asfasnf" << endl;
        dfs(grid, i + 1, j, p, result, k);
    }

    if (j < c - 1)
    {
        // cout << "asfasnf" << endl;
        dfs(grid, i, j + 1, p, result, k);
    }

    grid[i][j] = ch;
}

int partition(string arr[], int low, int high)
{
    string pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (arr[j] < pivot)
        {
            i++;
            // cout << arr[i] << endl;
            string t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
            // cout << arr[i] << endl;
        }
    }
    string t = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = t;
    return (i + 1);
}

void quickSort(string arr[], int low, int high)
{
    if (low < high)
    {

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{

    // Trie* root  = new Trie();

    // string dictionary[] = { "oath", "pea", "eat", "rain" };
    // int n = sizeof(dictionary) / sizeof(dictionary[0]);

    // for (int i = 0; i < n; i++) {
    //     insert(root, dictionary[i]);
    // }

    // char board[4][4] = {
    //     {'o', 'a', 'a', 'n'},
    //     {'e', 't', 'a', 'e'},
    //     {'i', 'h', 'k', 'r'},
    //     {'i', 'f', 'l', 'v'}
    // };

    // int X = 100;
    // string result[X];
    // int k = 0;

    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         dfs(board, i, j, root, result, k);
    //     }
    // }

    // // sort(result.begin(), result.end());
    // sort(result, result + k);

    // for (int i = 0; i < k; i++) {
    //     cout << result[i] << " ";
    // }

    // int r, c;
    cin >> r >> c;

    // char grid[r][c];

    char **grid = (char **)malloc(r * sizeof(char *));

    // dynamically allocate memory of size `n` for each row
    for (int i = 0; i < r; i++)
    {
        grid[i] = (char *)malloc(c * sizeof(char));
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            char element;
            cin >> element;
            grid[i][j] = element;
        }
    }

    int X;
    cin >> X;
    string dictionary[X];

    for (int i = 0; i < X; i++)
    {
        string word;
        cin >> word;
        dictionary[i] = word;
    }

    Trie *root = new Trie();

    int n = sizeof(dictionary) / sizeof(dictionary[0]);

    for (int i = 0; i < n; i++)
    {
        insert(root, dictionary[i]);
    }

    int k = 0;
    string result[X];

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            dfs(grid, i, j, root, result, k);
        }
    }

    // sort(result, result + k);
    quickSort(result, 0, k - 1);

    for (int i = 0; i < k; i++)
    {
        cout << result[i] << " ";
    }
    // cout << endl;
    // cout << search(root, "rain");
}
