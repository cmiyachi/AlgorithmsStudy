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
		default: /* assert (false); */ return -1;
	}
}

char indexToLetter (int n)
{
	switch (n)
	{
		case 0: return 'A'; break;
		case 1: return 'C'; break;
		case 2: return 'G'; break;
		case 3: return 'T'; break;
		default: return '*';
	}
}

vector<Node> trie; 

void print_trie()
{
     cout << endl;
    for (int i = 0; i < trie.size(); i++)
    {
        for (int j = 0; j < Letters;j++)
        {
            cout << (trie[i].next[j]) ;
        }
        cout << endl;
    }
}

int prefixTrieMatch(string text)
{
    Node v = trie[0];
    int current_index = 0;
    char symbol = text[0];
    int text_index = 0;
    
    // cout << "new string "+text << " " << text.size() << endl;
    
    while (text_index <= text.size())
    {
        // cout << "symbol " << symbol << endl;
        
        // is the current node a leaf?
        if (v.isLeaf())
        {
            // cout << "i am a leaf \n";
            return text_index;
        }
        else if (letterToIndex(symbol) == -1)
            return -1;
        else if (v.next[letterToIndex(symbol)] != NA)
        {
            int ti = letterToIndex(symbol);
            text_index++;
            symbol = text[text_index];
            v = trie[v.next[ti]]; 
            // cout << " ti " << text_index << " " << symbol << endl;
        }
        else
            return -1; 
            
    }
    
    return -1;

}


void init()
{

	Node *n = new Node();
    trie.push_back(*n);

}

void insert(string word)
{
	Node current = trie[0];
    int current_index = 0;
	
    // cout << "word " << word << endl; 
	for(int i = 0 ; i < word.length(); ++i)
	{
        
		int letter = letterToIndex (word[i]); //extrct first character of word
        // cout << "letter " << letter << endl;
		if(current.next[letter] == NA)
        {
            Node *n = new Node();
            trie.push_back(*n);
            
            size_t pos = trie.size() - 1;
			current.next[letter] = pos;
            trie[current_index] = current; 
            // cout << "index letter " << current_index << " " << word[i] << endl;
        }

		
        int next_pos = current.next[letter];	
        // cout << "next pos " << next_pos;
        current = trie[next_pos];
        current_index = next_pos; 
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
    
    // print_trie();

   
    int loc_index  = 0;
    while (text.size() != 0)
    {
        
        int match_index = prefixTrieMatch(text);
        if (match_index != -1)
            result.push_back(loc_index);
        text.erase(0,1);
        loc_index++;
        
    }
    
	return result;
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
