#include <cstdio>
#include <string>
#include <iostream>
# include <string>
# include <iostream>
# include <list>
# include <cstring>
# include <algorithm>

using std::string;
using std::cout; 

class Rope
{
    public:

        Rope(const string&);
        Rope(const char*);
        Rope(const Rope&);
        Rope(Rope&&);
        ~Rope(void);

        typedef string::value_type CharT;

        CharT at(unsigned int);
        CharT removeChar(unsigned int);
        void insert(unsigned int, const char*);
        void insert(unsigned int, const string&);
        unsigned int length(void) const;

        void print_tree(std::ostream&);

        void copy(char*, unsigned int) const;
        void consolidate(void); // make one contiguous node.
        void process(int i, int j, int k);
        std::string result(void);
    private:

        struct RopeNode
        {
            ~RopeNode(void);
            RopeNode(void);
            void print_tree(std::ostream&, unsigned int);

            /*const */ char* fragment;
            RopeNode *left, *right;
            unsigned int weight;
        };
    
        // Management
        void update_weights(RopeNode*) const;
        unsigned int internal_copy(RopeNode*, char*, unsigned int) const;
        unsigned int weight_sum(RopeNode*) const;

        // Data.
        RopeNode* root;

        std::list<const char*> to_delete;
};

Rope::Rope(const char* s)
    : Rope(string(s))
{}

Rope::Rope(const string& s)
{
    char* permanent_buffer = new char[s.length()+1];
    std::strncpy(permanent_buffer,s.c_str(),s.length()+1);
    to_delete.push_back(permanent_buffer);

    root = new RopeNode;

    root->fragment = nullptr;
    root->left = root->right = nullptr;
    root->weight = s.length();;

    root->left = new RopeNode;
    root->left->fragment = permanent_buffer;
    root->left->left = root->left->right = nullptr;
    root->left->weight = s.length();
}

Rope::Rope(const Rope& other)
{
    char* buffer = new char[other.length()];
    other.copy(buffer,other.length());

    to_delete.push_back(buffer);
    
    root = new RopeNode;
    root->left = new RopeNode;

    root->weight = root->left->weight = other.length();
    root->left->fragment = buffer;
}

Rope::Rope(Rope&& other)
    : root(other.root),
    to_delete(other.to_delete)
{
    other.root = nullptr;
    other.to_delete.clear();
}

Rope::~Rope(void)
{
    if ( root )
        delete root;

    for ( auto it = to_delete.begin(); it != to_delete.end(); it++ )
        delete[] *it;
}


Rope::RopeNode::RopeNode(void)
    : fragment(nullptr), left(nullptr), right(nullptr)
{
}

Rope::RopeNode::~RopeNode(void)
{
    if ( left )
        delete left;
    if ( right )
        delete right;
}

Rope::CharT Rope::at(unsigned int ix) // zero-based index
{
    unsigned int current_ix = ix + 1; // We deal with length values, 1-based index
    RopeNode* current = root->left; // root has only a left child

    while ( ! current->fragment )
    {
        if ( current_ix > current->weight )
        {
            current_ix -= current->weight;
            current = current->right;
        } else if ( current_ix <= current->weight )
        {
            current = current->left;
        }
    }
    current_ix--; // address array, 0-based index

    if ( current_ix < current->weight )
        return current->fragment[current_ix];
    else
        throw "Shouldn't happen";
}

Rope::CharT Rope::removeChar(unsigned int ix) // zero-based index
{
    unsigned int current_ix = ix + 1; // We deal with length values, 1-based index
    RopeNode* current = root->left; // root has only a left child

    while ( ! current->fragment )
    {
        if ( current_ix > current->weight )
        {
            current_ix -= current->weight;
            current = current->right;
        } else if ( current_ix <= current->weight )
        {
            current = current->left;
        }
    }
    current_ix--; // address array, 0-based index

    if ( current_ix < current->weight )
    {
        current->weight = current->weight - 1; 
        cout << " frag " << current->fragment << std::endl; 
        CharT curr_char =  current->fragment[current_ix];
        string curr_string(current->fragment);
        curr_string.erase(current_ix,1);
        int curr_string_len = curr_string.length();
        cout << " after erase " << curr_string << std::endl; 
        int len = curr_string.copy(current->fragment,curr_string_len);
        current->fragment[len] = '\0';
        
       // current->fragment = curr_string.c_str();
        cout << " frag after " << current->fragment << std::endl; 
        update_weights(root);
        return curr_char;
    }
    else
        throw "Shouldn't happen";
}

void Rope::insert(unsigned int ix, const string& s)
{
    insert(ix,s.c_str());
}


void Rope::insert(unsigned int ix, const char* s)
{
    unsigned int new_cont_length = std::strlen(s);
    char* new_s = new char[new_cont_length];
    std::strncpy(new_s,s,new_cont_length);

    to_delete.push_back(new_s);

    if ( ix >= root->weight ) // append
    {
        RopeNode* new_root = new RopeNode;
        RopeNode* new_cont = new RopeNode;

        new_cont->fragment = new_s;
        new_cont->weight = new_cont_length;

        new_root->left = root;
        root->right = new_cont;

        new_root->weight = new_cont->weight + root->weight;

        root = new_root;

        // No weights update necessary
    } else if ( ix < root->weight )
    {
        unsigned int current_ix = ix + 1;
        RopeNode* current = root;

        while (  ! current->fragment )
        {
            if ( current_ix > current->weight )
            {
                current_ix -= current->weight;
                current = current->right;
            } else
            {
                current->weight += new_cont_length; // already update tree
                current = current->left;
            }
        }

        // Those nodes are attached to current.
        RopeNode* new_left = new RopeNode;
        RopeNode* new_right = new RopeNode;
        RopeNode* new_content = new RopeNode;

        new_left->fragment = nullptr;
        new_left->weight = current_ix;
        new_left->right = new_content;
        new_left->left = new RopeNode;
        new_left->left->fragment = current->fragment;
        new_left->left->weight = current_ix;

        new_right->fragment = current->fragment + current_ix;
        new_right->weight = current->weight - current_ix;

        new_content->fragment = new_s;
        new_content->weight = std::strlen(new_s);

        current->fragment = nullptr;
        current->left = new_left;
        current->right = new_right;
        update_weights(root);

        // no weights update necessary.
    } else
        throw 42;
}

unsigned int Rope::length(void) const
{
    return root->weight;
}

void Rope::consolidate(void)
{
    char* new_contiguous_string = new char[length()];
    unsigned int original_length = length();
    copy(new_contiguous_string,length());

    // Free memory.
    delete root;

    std::for_each(to_delete.begin(),to_delete.end(),[](const char* p) { delete[] p; });
    to_delete.clear();
    
    // New tree
    RopeNode* root = new RopeNode, *left = new RopeNode;

    root->left = left;
    left->weight = root->weight = original_length;
    left->fragment = new_contiguous_string;

    to_delete.push_back(new_contiguous_string);
}

void Rope::copy(char* buffer, unsigned int length) const
{
    internal_copy(root,buffer,length);
    buffer[length-1] = '\0';
}

void Rope::print_tree(std::ostream& out)
{
    out << root->weight << " characters in rope.\n";
    root->left->print_tree(out,0);

}

void Rope::RopeNode::print_tree(std::ostream& out,unsigned int level)
{
    if ( ! this )
        return;

    for ( unsigned int i = 0; i < level; i++ )
        out << "│Lv   " << i;

    if ( left )
        out << "├──L " << string(fragment ? fragment : "<node>" ,fragment ? weight : 6) << " (" << weight << ")\n";
    else
        out << "└──R " << string(fragment ? fragment : "<node>" ,fragment ? weight : 6) << " (" << weight << ")\n";
    
    right->print_tree(out,level+1);
    
    left->print_tree(out,level);

}

void Rope::update_weights(RopeNode* n) const
{
    if ( n->left )
    {
        update_weights(n->left);
        n->weight = weight_sum(n->left);
    }
    if ( n->right )
    {
        update_weights(n->right);
    }

}

unsigned int Rope::weight_sum(RopeNode* n) const
{
    if ( n->fragment )
        return n->weight;
    else
    {
        unsigned int sum = 0;
        if ( n->left )
            sum += weight_sum(n->left);
        if ( n->right )
            sum += weight_sum(n->right);

        return sum;
    }

}

unsigned int Rope::internal_copy(RopeNode* n, char* buffer, unsigned int length) const
{
    if ( length == 0 || ! n )
        return 0;

    if ( ! n->fragment )
    {
        unsigned int copied = internal_copy(n->left,buffer,length);
        unsigned int copied2 = internal_copy(n->right,buffer+copied,length-copied);
        
        return copied + copied2;
    } else
    {
        unsigned int to_copy = n->weight < length ? n->weight : length;
        std::strncpy(buffer,n->fragment,to_copy);
        return to_copy;
    }
}

void Rope::process(int i, int j, int k)
{
    string ss;
    for (int m = i; m <= j; m++)
    {
        print_tree(std::cout); 
        cout << "******\n";
        char this_char = removeChar(m);
        ss += this_char;
        m = m -1;
        if (ss.length() >= (j -i + 1)) break;
    }
    cout << " string to remove " << ss << std::endl;
    print_tree(std::cout); 
    std::cout << result() << std::endl;
    insert(k-1, ss.c_str());
    std::cout << result() << std::endl;
  //   consolidate();
}

std::string Rope::result()
{
    string s;
   // cout << " len " << length() << std::endl; 
    for ( unsigned int i = 0; i < length(); i++ )
    {
      //  cout << " i " << i << " " << std::endl;
        s[i] = at(i);
       cout << s[i] << " ";
    }
    cout << s << "\n";
    return s; 
}

class RopeNaive {
	std::string s;
public:
	RopeNaive(const std::string &s) : s(s) { 
	}

	void process( int i, int j, int k ) {
                // Replace this code with a faster implementation
                std::string t = s.substr(0, i) + s.substr(j + 1);
                s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
	}

	std::string result() {
		return s;
	}
};

int main() {
	std::ios_base::sync_with_stdio(0);
	std::string s;
	std::cin >> s;
	Rope rope(s.c_str());
	int actions;
	std::cin >> actions;
        for (int action_index = 0; action_index < actions; ++action_index) {
                int i, j, k;
		std::cin >> i >> j >> k;
		rope.process(i, j, k);
        std::cout << rope.result() << std::endl;
	}
    rope.print_tree(std::cout); 
    cout << "******\n";
    string rs = rope.result();
	std::cout << rs << std::endl;
}
