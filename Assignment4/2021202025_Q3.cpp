#include <iostream>
using namespace std;

typedef long long ll;

ll maximumXOR;

class Node
{
public:
	Node *children[2];
};

class trie
{
	Node *root;

public:
	void insert(Node *root, ll n)
	{
		Node *temp = root;
		for (ll i = 63; i >= 0; i--)
		{
			ll bit = (n >> i) & 1;
			if (!temp->children[bit])
			{
				temp->children[bit] = new Node();
			}
			temp = temp->children[bit];
		}
	}

	void max_xor(Node *root, ll toFind)
	{

		Node *temp = root;
		for (ll i = 63; i >= 0; i--)
		{
			ll bit = ~(toFind >> i) & 1;
			if (temp->children[bit] == NULL)
			{
				bit ^= 1;
			}
			maximumXOR = maximumXOR << 1 | bit;
			temp = temp->children[bit];
		}
	}
};

int main()
{

	ll n, q;
	cin >> n >> q;

	Node *root = new Node();
	trie t;
	for (ll i = 0; i < n; i++)
	{
		ll x;
		cin >> x;
		t.insert(root, x);
	}

	for (ll i = 0; i < q; i++)
	{
		ll test;
		cin >> test;
		maximumXOR = 0;
		t.max_xor(root, test);
		cout << (maximumXOR ^ test) << endl;
	}

	return 0;
};