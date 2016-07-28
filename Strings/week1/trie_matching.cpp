#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
    int prefix_count;
	bool isEnd;
    struct Node *child[Letters];
	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
}*head;

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}



vector <int> solve (string text, int n, vector <string> patterns)
{
	vector <int> result;
    init();
    
    for (int i = 0; i < patterns.size(); i++)
    {
        insert(patterns[i]);
    }


	return result;
}

void init()
{

	head = new Node();
	head->isEnd = false;
	head->prefix_count = 0;
}

void insert(string word)
{
	Node *current = head;
	current->prefix_count++;
	
	for(int i = 0 ; i < word.length(); ++i)
	{
		int letter = letterToIndex (word[i]); //(int)word[i] - (int)'a';	//extrct first character of word
		if(current->child[letter] == NULL)
			current->child[letter] = new Node();

		current->child[letter]->prefix_count++;
		current = current->child[letter];		
	}
	current->isEnd = true;
}

bool search(string word)
{
	node *current = head;
	for(int i = 0 ; i < word.length(); ++i)
	{
		int letter = letterToIndex(word[i]); //(int)word[i] - (int)'a';
		if(current->child[letter] == NULL)
			return false;		//not found
		current = current->child[letter];
	}
	return current->isEnd;
}
int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
    
    
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
