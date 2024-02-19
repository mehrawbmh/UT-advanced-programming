#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool canFindMathExpression(const vector<int>& numbers, int temp, int index, vector<char>& signs)
{
    int current = numbers[index];

    if (index + 1 == numbers.size()) {
        signs[index - 1] = '=';
        return current == temp; 
    }


    if (canFindMathExpression(numbers, temp + current, index + 1, signs)) {
        signs[index-1] = '+';
        return true;
    }

    if (canFindMathExpression(numbers, temp - current, index + 1, signs)) {
        signs[index-1] = '-';
        return true;
    }

    if (canFindMathExpression(numbers, temp * current, index + 1, signs)) {
        signs[index-1] = '*';
        return true;
    }


    return false;

}

string prepareAnswer(const vector<int>& numbers, const vector<char>& signs)
{
    string result = "";
    for (int i = 0; i < numbers.size(); i++) {
        result += to_string(numbers[i]);
        result += signs[i];
    }

    return result;
}


int main()
{
    int n;
    cin >> n;

    vector<int> numbers(n);
    vector<char> resultSigns (n);

    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
    
    bool res = canFindMathExpression(numbers, numbers[0], 1, resultSigns);

    cout << (res ? prepareAnswer(numbers, resultSigns) : "No Solution!");

    return 0;
}

