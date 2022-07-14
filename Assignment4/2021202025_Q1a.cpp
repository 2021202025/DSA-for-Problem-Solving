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
    s.append(s);

    vector<int> sufArray(s.size());

    buildSuffixArray(s, sufArray);

    int neededHalf = s.size() / 2;
    int idx;
    for (int i = 0; i < s.size(); ++i)
    {
        // cout << sufArray[i] << endl;
        if (sufArray[i] < neededHalf)
        {
            idx = sufArray[i];
            break;
        }
    }

    // cout << idx << endl;

    // for (int i = 0; i < sufArray.size(); i++)
    // {
    //     cout << sufArray[i] << " ";
    // }

    for (int i = idx; i < idx + neededHalf; i++)
        cout << s[i] << "";
    cout << endl;
}