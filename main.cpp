#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
using namespace std;

#Повертає наступне просте число після заданного
int nextPrime(int num) {
	for (int i = num + 1; i <= 97; i++) {
		int counter = 0;
		for (int j = 2; j <= i / 2; ++j) {
			if (i % j == 0) {
				counter++;
			}
		}
		if (counter == 0) {
			return i;
		}
	}
	return 97;
}

class HashTable {
private:
	int hashGroups{};
	vector<vector<string>> table;
public:
	int hashFunction(string str, int rowLength, int randA, int prime);
	void printTable();
#Прибирає чистить однакові дані
	HashTable(vector<string> args) {
		for (int i{}; i < args.size(); i++) {
			for (int j = i + 1; j < args.size(); j++) {
				if (args[i] == args[j]) {
					args.erase(next(args.begin(), j));
				}
			}
		}

		hashGroups = args.size();
#Задаємо випадкові числа та створюємо хеш - таблицю за допомогою написаної хеш - функції
		srand(time(0));
		int a = rand() % 100 + 1;
		//int b = rand() % 100 + 1;
		int a1 = rand() % 100 + 1;
		int b1 = rand() % 100 + 1;
		const int p = nextPrime(args.size());
		cout << "k = " << a << endl;
		cout << "p = " << p << endl;
		vector<vector<string>> arr;
		for (int i{}; i < hashGroups; i++) {
			arr.push_back(vector<string>{});
		}
#Створюємо підмасиви для комірок з колізіями розміру(кількість колізій) ^ 2
		for (int i{}; i < args.size(); i++) {
			int pos = hashFunction(args[i], args.size(), a, p);
			arr[pos].push_back(args[i]);
		}

		for (int i{}; i < hashGroups; i++) {
			table.push_back(vector<string>{});
		}

		for (int i{}; i < table.size(); i++) {
			if (arr[i].size() >= 2) {
				for (int j{}; j < pow(arr[i].size(), 2); j++) {  //(int j = 0) == int{}
					table[i].push_back(" ");
				}
			}
			else {
				table[i].push_back(" ");
			}
		}
#Повторюємо хешування для комірок з колізіями
		for (int i{}; i < arr.size(); i++) {
			a1 = rand() % 10;
			b1 = rand() % 10;

			for (int j{}; j < arr[i].size(); j++) {
				int firstPos = hashFunction(arr[i][j], args.size(), a, p);
				if (table[firstPos].size() == 1) {
					table[firstPos][0] = arr[i][0];
				}
				else if (table[firstPos].size() > 1) {
					int secondaryPos = hashFunction(arr[i][j], table[firstPos].size(), a1, p);
					if (table[firstPos][secondaryPos] != " ") {
						i--;
						j = 0;
						for (int k{}; k < table[firstPos].size(); k++) {
							table[firstPos][k] = " ";
						}
						break;
					}
					table[firstPos][secondaryPos] = arr[i][j];
				}
			}
		}
	}
};
#Хеш - функція для даних типу string
int HashTable::hashFunction(string str, int rowLength, int randA, int prime) {
	unsigned int value{};
	int retVal{};
	for (int i{}; i < str.length(); i++) {
		value += (int)str[i] * pow(randA, i);
	}
	return ((value % prime) % rowLength);	
}
#Вивести таблицю в консоль
void HashTable::printTable() {
	for (int i{}; i < table.size(); i++) {
		cout << " x" << i << ":\t";
		for (int j{}; j < table[i].size(); j++) {
			if(table[i][j] != " ")
				cout << table[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	vector<string> A{ "Marty", "Bob", "Zoe", "Bob", "Den", "Sandy", "Helen","Max", "Tom", "Deb", "Cole", "Hue", "Rick", "Dendy", "Bernard", "Kayla", "Layla", "Ted"};
	HashTable hs(A);
	hs.printTable();
	cout << (int)'M' << endl << (int)'a' << endl << (int)'r' << endl << (int)'t' << endl << (int)'y';
}