#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

struct suffixString
{
    int idx;
    int first;
    int second;
};

int compare(struct suffixString a, struct suffixString b)
{
    if (a.first == b.first)
    {
        int temp = 0;
        if (a.second < b.second)
        {
            temp = 1;
        }
        else
        {
            temp = 0;
        }
        return temp;
    }
    int temp = 0;
    if (a.first < b.first)
    {
        temp = 1;
    }
    else
    {
        temp = 0;
    }
    return temp;
}

void buildSuffixArray(string text, vector<int> &suffixArray)
{
    int n = text.size();
    struct suffixString suffixes[n];

    for (int i = 0; i < n; i++)
    {
        suffixes[i].idx = i;
        suffixes[i].first = text[i] - '0';
        if ((i + 1) < n)
        {
            suffixes[i].second = text[i + 1] - '0';
        }
        else
        {
            suffixes[i].second = -1;
        }
    }

    sort(suffixes, suffixes + n, compare);

    vector<int> indices(n);
    int start = 4;
    int end = 2 * n;
    for (int k = start; k < end; k *= 2)
    {
        int rank = 0;
        int prevRank = suffixes[0].first;
        suffixes[0].first = rank;
        // int outArr[] = {1};
        // int check = outArr[0];
        indices[suffixes[0].idx] = 0;
        for (int i = 1; i < n; i++)
        {
            if (suffixes[i].first != prevRank or suffixes[i].second != suffixes[i - 1].second)
            {
                prevRank = suffixes[i].first;
                rank++;
                suffixes[i].first = rank;
            }
            else
            {
                prevRank = suffixes[i].first;
                suffixes[i].first = rank;
            }
            indices[suffixes[i].idx] = i;
        }

        for (int i = 0; i < n; i++)
        {

            int nextindex = suffixes[i].idx + k / 2;
            int newRank = 0;
            if (nextindex < n)
                newRank = suffixes[indices[nextindex]].first;
            else
                newRank = -1;

            suffixes[i].second = newRank;
        }
        // }
        sort(suffixes, suffixes + n, compare);
    }

    int i = 0;
    while (i < n)
    {
        suffixArray[i] = suffixes[i].idx;
        i++;
    }
}

int main()
{

    string s;
    cin >> s;

    int k;
    cin >> k;

    vector<int> suffixArray(s.size());
    buildSuffixArray(s, suffixArray);

    int start = 0;
    int end = s.size() - k;
    string result = "";
    for (int i = 0; i < 1 + end; i++)
    {
        string tempResult = "";
        int l = i + k - 1;
        int p = suffixArray[i];
        int q = suffixArray[l];
        while (s[p] == s[q] and p < s.size() and q < s.size())
        {
            tempResult += s[p++];
            q++;
        }
        if (tempResult.size() > result.size())
        {
            result = tempResult;
        }
        else
        {
            continue;
        }
    }

    if (result == "")
    {
        cout << -1 << endl;
    }
    else
    {
        // cout << result << endl;
        cout << result.size() << endl;
    }
}