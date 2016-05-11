#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <chrono>
#include <ctime>
#include <memory>
#include <iostream>
using namespace std;
using namespace std::chrono;

#define MNL 5
#define ulong unsigned long

class Rope {
public:
    Rope(string);
    void Insert(string, ulong);
    void Delete(ulong, ulong);
    string Split(ulong, ulong);
    void Concat(Rope);
    string Stringify();
    char Index(ulong);
    void Adjust();
    void Rebuild();
    void Balance();
    void process(int i, int j, int k);
    std::string result(void);
private:
    shared_ptr<Rope> Left;
    shared_ptr<Rope> Right;
    string Value;
    ulong Weight;
};


Rope::Rope(string str) {
    Value = str;
    Adjust();
}

void Rope::Adjust() {
    Weight = Value.length();
    if (Weight > MNL) {
        string leftval = Value.substr(0,Weight/2);
        string rightval = Value.substr(Weight/2, Weight);
        if (leftval != "") Left = make_shared<Rope>(leftval);
        if (rightval != "") Right = make_shared<Rope>(rightval);
        Weight /= 2;
        Value = "";
    }
}

void Rope::Insert(string str, ulong pos) {
    if (pos > Weight) Right->Insert(str, pos - Weight);
    else {
        if (Left) Left->Insert(str, pos);
        else Value.insert(pos, str.c_str());
    }
}

void Rope::Delete(ulong s, ulong e) {
  //  if (s < e) swap(s,e);
    Value = this->Stringify().erase(s, e);
    Rebuild();
}

char Rope::Index(ulong pos) {
    if (pos > Weight) return Right->Index(pos - Weight);
    else {
        if (Left) return Left->Index(pos);
        else return Value[pos];
    }
}

void Rope::Rebuild() {
    Left.reset();
    Right.reset();
    Weight = 0;
    Adjust();
}

void Rope::Balance() {
    Value = this->Stringify();
    Rebuild();
}

string Rope::Split(ulong s, ulong e) {
    if (s < e) swap(s,e);
    return this->Stringify().substr(s, e-s);
}

void Rope::Concat(Rope R) {
    Value = this->Stringify() + R.Stringify();
    Rebuild();
}

string Rope::Stringify() {
    if (Value != "") return Value;
    else return Left->Stringify() + Right->Stringify();
}




void Rope::process(int i, int j, int k)
{
    // get string being stored
    string ss = Stringify();
    
    // find the substring
    string subs = ss.substr(i,j-i+1);
    // cout << " string to remove " << subs << std::endl;
    
    // remove it
    Delete(i,j-i+1);
    // insert it
    Insert(subs, k);
  //   consolidate();
}

std::string Rope::result()
{
    string s = Stringify();
   
    return s; 
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::string s;
	std::cin >> s;
	Rope rope(s);
	int actions;
	std::cin >> actions;
        for (int action_index = 0; action_index < actions; ++action_index) {
                int i, j, k;
		std::cin >> i >> j >> k;
		rope.process(i, j, k);
        // std::cout << rope.result() << std::endl;
	}

    string rs = rope.result();
	std::cout << rs << std::endl;
}

int test() {

    std::ifstream t("/home/gagan/data/big.txt");
    string S((std::istreambuf_iterator<char>(t)),
             std::istreambuf_iterator<char>());
    time_t tt;
    system_clock::time_point today = system_clock::now();

    tt = system_clock::to_time_t ( today );
    std::cout << "today is: " << ctime(&tt);

    Rope R ("abcdefg jjfdafkjdakfjdaeiwaorueagnkfanbldafkheaoitueaiognrabnflkajfeia");
    Rope G("gagan");
    Rope J("jyot");
    R.Concat(G);
    R.Concat(J);
    cout << G.Index(1);
    cout << G.Index(2);
    cout << G.Index(3);
    cout << G.Index(G.Stringify().length()-1) << std::endl;
    cout << G.Stringify();
    cout << R.Index(50);
    R.Insert("gagan", 0);
    cout << R.Index(0);
    cout << R.Index(1);
    cout << R.Index(2);
    cout << R.Index(3);
    cout << R.Index(4);
    string a = R.Stringify();
    cout << a.length();
    cout << R.Stringify().length()<< "\n\n";
    R.Balance();
    cout << R.Index(R.Stringify().length()-4);
    cout << R.Index(R.Stringify().length()-3);
    cout << R.Index(R.Stringify().length()-2);
    cout << R.Index(R.Stringify().length()-1);
    today = system_clock::now();
    G.Delete(1,3);
    cout << std::endl << G.Stringify() << std::endl; 

    tt = system_clock::to_time_t ( today );
    std::cout << "today is: " << ctime(&tt);
}
