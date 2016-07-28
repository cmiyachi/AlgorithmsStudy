#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>


#include <iostream>
#include <vector>
#include <map>

using namespace std;


typedef map<char, int> edges;
typedef vector<edges> trie;



struct node
{
	int prefix_count;
	bool isEnd;
	struct node *child[26];
}*head;

void init()
{
//	head = (node*)malloc(sizeof(node));
	head = new node();
	head->isEnd = false;
	head->prefix_count = 0;
}

void print_trie()
{
    node *current = head;
    while (current->isEnd != true)
    {
        int j = 0;
        for (int i = 0; i < 26; i++)
        {
            if (current->child[i] != NULL)
            {
                cout <<" j " << j << " letter " << (char )(i+(int)'a') << endl;
                current = current->child[i];
            }
            else{
                cout << " moving on \n";
            }
        }
        
        j++;
    }
    
}

void insert(string word)
{
	node *current = head;
	current->prefix_count++;
	
	for(int i = 0 ; i < word.length(); ++i)
	{
		int letter = (int)word[i] - (int)'a';	//extrct first character of word
		if(current->child[letter] == NULL)
			current->child[letter] = new node();

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
		int letter = (int)word[i] - (int)'a';
		if(current->child[letter] == NULL)
			return false;		//not found
		current = current->child[letter];
	}
	return current->isEnd;
}

int words_with_prefix(string prefix)
{
	node *current = head;
	for(int i = 0; i < prefix.length() ; ++i)
	{
		int letter = (int)prefix[i] - (int)'a';
		if(current->child[letter] == NULL)
			return 0;
		else
			current = current->child[letter];
	}
	return current->prefix_count;
}
trie build_trie(vector<string> & patterns) {
  trie t;
   for (int i = 0; i < patterns.size(); i++)
  {
      string currentPattern = patterns[i];
      int current_node = 0;
      t.resize(t.size()+1);
      edges ne;
      t[current_node] = ne;
      
      insert(currentPattern);
  }
  return t;
}

int main()
{
    
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }
    init();
  trie t = build_trie(patterns);
  print_trie();
  /* for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

	
	string s = "chandan";
	insert(s);
	s = "mittal";
	insert(s);
	s = "chirag";
	insert(s);
	s = "shashank";
	insert(s);
	s = "abhinav";
	insert(s);
	s = "arun";
	insert(s);
	s = "abhishek";
	insert(s);
	

	if(search("chandan"))
		printf("found chandan\n");
	if(search("arun"))
		printf("found arun\n");
	if(search("abhi"))
		printf("found abhi\n");
	else
		printf("not found abhi\n");
	
	printf("no of words with prefix abhi are %d\n",words_with_prefix("abhi"));
	printf("no of words with prefix ch are %d\n",words_with_prefix("ch"));
	printf("no of words with prefix k are %d\n ",words_with_prefix("k"));
	 */
	

	return 0;
}