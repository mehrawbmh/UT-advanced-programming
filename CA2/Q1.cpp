#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

bool isPalindrome(const string& str, int i , int j)
{
    int n = str.size();

    if (i > j) {
        return true;
    }

    char start = str[i];
    char end = str[j];

    if (!isalpha(start)) {
        return isPalindrome(str, i + 1, j);
    }

    if (!isalpha(end)) {
        return isPalindrome(str, i, j-1);
    }    

    if (tolower(start) != tolower(end)) {
        return false;
    }

    return isPalindrome(str, i + 1, j - 1);
}

void test()
{
    assert(isPalindrome("pap", 0, 3));
    assert(isPalindrome("paap", 0, 4));
    assert(isPalindrome("pap!", 0, 4));
    assert(isPalindrome("paP", 0, 3));
    assert(isPalindrome("p!aP", 0, 4));
    assert(isPalindrome("!paP", 0, 4));
    assert(isPalindrome("p-a.P",0, 5));
    assert(isPalindrome("toolani inaloot <> ", 0, 19));
    assert(isPalindrome("!@$", 0, 3));
    assert(isPalindrome("a@^A", 0, 4));
    assert(isPalindrome("Vv##%", 0, 5));
    assert(isPalindrome("!aa!!!!!!!!!!!!!!!", 0, 18));
    assert(isPalindrome("!aa!!!!!!!!!$!!!!!", 0, 18));
    assert(isPalindrome("ggG01", 0, 5));

    assert(!isPalindrome("pa", 0, 2));
    assert(!isPalindrome("pasP", 0, 4));
    assert(!isPalindrome("!ae!!!!!!!!!!!!!!!", 0, 18));
    assert(!isPalindrome("GxgG01", 0, 6));
}


int main()
{
    test();
    exit(0);
    string inputString;
    vector<bool> answers;
    
    while(getline(cin, inputString)) {
        bool isPal = isPalindrome(inputString, 0, inputString.size() - 1);
        answers.push_back(isPal);
    }

    for(auto ans: answers) {
        string result = ans ? "true" : "false";
        cout << result << endl;
    }

    return 0;
}
