#include <iostream>
#include <vector>
#include <forward_list>
#include <tuple>
#include <map>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <fstream>
#include <regex>
#include <set>
#include <sstream>
using namespace std;

template<typename T>
int getSizeList(forward_list<T>& list) {
	int size = 0;
	for (auto n : list) {
		size++;
	}
	return size;
}

template<typename T>
void printList(forward_list<T>& list) {
	for (auto n : list) {
		cout << n << " -> ";
	} cout << "nullptr\n";
}

template<typename T>
void eraseListByIndexes(forward_list<T>& list, int left, int right) {
	auto leftIt = list.before_begin(); // итератор перед началом
	auto rightIt = list.begin(); // итератор на начало
	int size = getSizeList(list);

	if (left > right || left > size - 1) {
		return;
	}

	if (right > size - 1) { // если правая граница дальше конца
		right = size - 1; // ставим правую границу на конец
	}

	for (int i = 0; i < left; i++) {
		leftIt++; // левую границу сдвигаем
	}

	for (int i = 0; i <= right; i++) {
		rightIt++; // правую границу сдвигаем
	}

	list.erase_after(leftIt, rightIt);
}

void printTuple(tuple<double, int, char> triplet) {
	cout << get<0>(triplet) << " ";
	cout << get<1>(triplet) << " ";
	cout << get<2>(triplet) << endl;
}

tuple<double, int, char> foo(double x) {
	return make_tuple(x + 0.5, x, x);
}

template<typename Func>
Func myFor_each(forward_list<int>& list, Func f) {
	for (auto& e : list) {
		f(e);
	}
	return f;
}

template<typename T>
T getSumVector(vector<T>& v) {
	T sum = {};
	for (const auto &e : v) {
		sum += e;
	}
	return sum;
}

template<typename T>
void printVector(vector<T>& v) {
	for (const auto& e : v) {
		cout << e << '\t';
	} cout << endl;
}

int getSumDigits(int num) {
	int sum = 0;
	while (num != 0) {
		sum += (num % 10);
		num /= 10;
	}
	return sum;
}

bool checkNums(int n1, int n2) {
	return getSumDigits(n1) < getSumDigits(n2);
}

class EvenSummator {
public:
	int sum = 0;
	void operator()(int x) {
		if (x % 2 == 0) {
			this->sum += x;
		}
	}
};

float getDistance(const tuple<float, float, float, float>& t) {
	float x0 = get<0>(t);
	float y0 = get<1>(t);
	float x1 = get<2>(t);
	float y1 = get<3>(t);
	return sqrt(pow(x0 + y0, 2) + pow(x1 + y1, 2));
}

/*template<typename T>
ostream& operator<<(ostream& os, const tuple<T, T, T, T>& t) {
	for (int i = 0; i < 4; i++) {
		os << get<0>(t) << '\t';
	}
	os << endl;
	return os;
}*/

template<typename K, typename V>
ostream& operator<<(ostream& os, const map<K, V>& m) {
	for (const auto& e : m) {
		os << e.first << " : ";
		os << e.second << endl;
	}
	return os;
}

int f(const string& s, const string& sub) {
	int i = 0, j = 0;
	while (i < s.size()) {
		while (j < sub.size()) {
			if (s[i] == sub[j]) {
				i++; j++;
			}
			else {
				i++; j = 0;
			}
			if (i > sub.size()) {
				return i - j;
			}
		}
		i++;
	}
	return -1;
}



set<float> getSet(string& s) {
	set<float> numbers;
	stringstream ss(s);
	while (getline(ss, s, ' ')) {
		if (s.size() > 0) numbers.insert(stof(s));
	}
	return numbers;
}

map<char, int> getDictFromString(const string& s) {
	map<char, int> d;
	for (auto& c : s) {
		d.count(c) ? d[c]++ : d[c] = 1;
	}
	return d;
}

bool checkAnagramms(const string& s1, const string& s2) {
	if (s1.size() != s2.size()) return false;
	map<char, int> m1 = getDictFromString(s1);
	map<char, int> m2 = getDictFromString(s2);
	for (auto e : m1) {
		char k = e.first;
		if (m2.count(k) == 0 || m1[k] != m2[k]) return false;
	}
	return true;
}

string getContent(const string& filename) {
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) {
		return "";
	}
	string text((istreambuf_iterator<char>(fin)), (istreambuf_iterator<char>()));
	return text;
}

int main() {
	regex rgx("[a-zA-Z_][a-zA-Z0-9_]*@[a-z]+\.[a-z]+");
	string text = getContent("text.txt");
	smatch m;
	while (regex_search(text, m, rgx)) {
		cout << m.str() << endl;
		text = m.suffix().str();
	}
}
