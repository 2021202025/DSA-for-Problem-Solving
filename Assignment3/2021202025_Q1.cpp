#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <unordered_map>
#include <vector>

using namespace std;

class Node
{
public:
    unordered_map<char, Node *> children;
    int isTerminal;
    string word;

    Node()
    {
        // char i;
        isTerminal = 0;
        word = "";

        for (char i = 'a'; i <= 'z'; i++)
        {
            children[i] = NULL;
        }
    }
};

void insert(Node *root, string word)
{
    Node *temp = root;
    for (int i = 0; i < word.size(); i++)
    {
        if (!temp->children[word[i]])
        {
            temp->children[word[i]] = new Node();
        }
        temp = temp->children[word[i]];
    }
    temp->isTerminal = 1;
    temp->word = word;
}

void autoCompleteUtil(Node *temp, string prefix)
{
    if (temp->isTerminal)
    {
        cout << prefix << endl;
    }

    for (char i = 'a'; i <= 'z'; i++)
    {
        if (temp->children[i] != NULL)
        {
            autoCompleteUtil(temp->children[i], prefix + (char)i);
        }
    }
}

void autoComplete(Node *root, string prefix)
{
    Node *temp = root;

    if (prefix == "")
    {
        return;
    }
    // cout << "AAAAAAAAAAAa" << endl;
    for (int i = 0; i < prefix.size(); i++)
    {
        if (!temp->children[prefix[i]])
        {
            return;
        }
        temp = temp->children[prefix[i]];
    }
    // cout << prefix << endl;
    autoCompleteUtil(temp, prefix);
}

bool spellCheck(Node *root, string s)
{
    Node *temp = root;

    for (char ch : s)
    {
        // cout << ch << endl;
        if (!temp->children[ch])
        {
            return false;
        }
        temp = temp->children[ch];
    }

    if (temp->isTerminal)
    {
        return true;
    }
    return false;
}

//finding minimum of three numbers
int smallestDistance(int x, int y, int z)
{
    return min(min(x, y), z);
}

int lavenshteinDistance(string a, string b)
{
    vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, 0));

    for (int i = 0; i <= a.size(); i++)
        dp[i][0] = i;

    for (int i = 0; i <= b.size(); i++)
        dp[0][i] = i;

    for (int i = 1; i <= a.size(); i++)
    {
        for (int j = 1; j <= b.size(); j++)
        {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
            {
                int minDistance = smallestDistance(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]);
                dp[i][j] = 1 + minDistance;
            }
        }
    }
    return dp[a.size()][b.size()];
}

void traverse(Node *node, string const &prefix, string givenword, int &level)
{
    int sizeDiff = prefix.size() - givenword.size();
    if (node->isTerminal)
    {
        // allWords.push_back(prefix);
        // cout << abs(sizeDiff) << endl;
        if (abs(sizeDiff) <= 4)
        {
            if (lavenshteinDistance(prefix, givenword) <= 3)
            {
                cout << prefix << endl;
            }
            else
            {
                return;
            }
        }
    }

    if (sizeDiff > 4)
    {
        return;
    }

    for (char i = 'a'; i <= 'z'; i++)
        if (node->children[i])
            traverse(node->children[i], prefix + i, givenword, level);
}

void searchRecursive(Node *node, char letter, string word, vector<int> &previousRow, vector<string> &results)
{
    // int colums = word.size() + 1;
    vector<int> currentRow;
    currentRow.push_back(previousRow[0] + 1);

    for (int i = 1; i <= word.size(); i++)
    {

        int insertCost = currentRow[i - 1] + 1;
        int deleteCost = previousRow[i] + 1;
        int replaceCost = 0;

        if (word[i - 1] != letter)
        {
            replaceCost = previousRow[i - 1] + 1;
        }
        else
        {
            replaceCost = previousRow[i - 1];
        }

        currentRow.push_back(smallestDistance(insertCost, deleteCost, replaceCost));
    }

    if (currentRow[currentRow.size() - 1] <= 3 and node->word != "")
    {
        // results.push_back(node->word);
        cout << node->word << endl;
    }

    int minVal = INT_MAX;
    for (int i = 0; i < currentRow.size(); i++)
    {
        if (currentRow[i] < minVal)
        {
            minVal = currentRow[i];
        }
    }

    if (minVal <= 3)
    {
        for (char i = 'a'; i <= 'z'; i++)
            if (node->children[i] != NULL)
                searchRecursive(node->children[i], i, word, currentRow, results);
    }
}

void search(Node *node, string word)
{
    vector<int> currentRow;
    for (int i = 0; i < word.size() + 1; i++)
    {
        currentRow.push_back(i);
    }

    vector<string> results;

    for (char i = 'a'; i <= 'z'; i++)
        if (node->children[i] != NULL)
            searchRecursive(node->children[i], i, word, currentRow, results);

    // for (int i = 0; i < results.size(); i++) {
    //     cout << results[i] << endl;
    // }
}

int main()
{
    // system("cls");
    // ifstream in("wordlist.txt");
    // string word, current = "", key;
    // Node *root;
    // root = new Node();
    // while (in) {
    //     in >> word;
    //     insertword(word, 0, root);
    // }
    // in.close();
    // cout << endl << "Trie Construction Successful" << endl;

    // Node* root = new Node();

    // ifstream in("wordlist.txt");
    // string word, current = "", key;

    // // vector<string> contacts = {"purvasingh" , "purvakumar", "purvatribbiani"};
    // // vector<string> dictWords;
    // while (in) {
    //     in >> word;
    //     insert(root, word);
    //     // dictWords.push_back(word);
    // }

    // string query = "apple";

    // // cout << spellCheck(root, query);
    // // cout << endl;
    // // displaycontacts(root, query);

    // vector<string> allStrings;

    // traverse(root, "", allStrings);

    // for (string s : allStrings) {
    //     int distance = editdist(query, s);
    //     if (distance <= 3) {
    //         cout << s << endl;
    //     }
    // }

    // int n;
    // cin >> n;

    // while (n--) {
    //     string s;
    //     cin >> s;

    //     insert(root, s);

    Node *root = new Node();

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        insert(root, s);
    }

    int ai;
    string ti;

    cin >> ai >> ti;

    if (ai == 1)
    {
        cout << spellCheck(root, ti);
    }

    else if (ai == 2)
    {
        autoComplete(root, ti);
    }

    else if (ai == 3)
    {
        // vector<string> allStrings;
        int level = 0;
        // traverse(root, "", ti, level);
        search(root, ti);

        // for (string s : allStrings) {
        //     int distance = lavenshteinDistance(ti, s);
        //     if (distance <= 3) {
        //         cout << s << endl;
        //     }
        // }
    }

    return 0;
}