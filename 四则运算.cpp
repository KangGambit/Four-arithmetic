#include <iostream>
#include <stack>
#include <string>
#include <map>
using namespace std;


void calculation(stack<int>& num, stack<char>& symbol) {
	int b = num.top();
	num.pop();
	int a = num.top();
	num.pop();
	char sym = symbol.top();
	symbol.pop();
	int res = 0;
	switch (sym){
	case '+': {res = a + b; break; }
	case '-': {res = a - b; break; }
	case '*': {res = a * b; break; }
	case '/': {res = a / b; break; }
	}
	num.push(res);
}

bool isdigital(char s) {
	return (s >= '0' && s <= '9') ? true : false;
}

int main() {
	string str;
	cin >> str;
	for(int i = 0; i < str.length(); i++) {
		if (str[i] == '[' || str[i] == '{') str[i] = '(';
		else if (str[i] == ']' || str[i] == '}') str[i] = ')';
	}
	map<char, int> level;
	level['('] = 0; level[')'] = 0; level['+'] = 1; level['-'] = 1; level['*'] = 2; level['/'] = 2;
	stack<int> num;
	stack<char> symbol;
	if (!isdigital(str[0])) num.push(0);
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(') {
			symbol.push(str[i]);
			if (!isdigital(str[i + 1])) num.push(0);
		}
		else if (str[i] == ')') {
			while (symbol.top()!= '(') calculation(num, symbol);
			symbol.pop();
		}
		else if (isdigital(str[i])) {
			int start = i;
			while(i<str.length()&&isdigital(str[i+1])) i++;
			num.push(stoi(str.substr(start, i - start + 1)));
		}
		else {
			while (!symbol.empty() && level[str[i]] <= level[symbol.top()]) calculation(num, symbol);
			symbol.push(str[i]);
		}
	}
	while (!symbol.empty()) calculation(num, symbol);
	cout << num.top() << endl;
	return 0;
}