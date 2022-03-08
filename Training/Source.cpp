#include "SortAlg.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <chrono>
#include <functional>

using namespace std;

// Generate random int array consists of the N elements
// init - initialize number for random generator
vector<int> randGen(size_t N, size_t init = 123456) {
	vector<int> res;
	srand(init);
	for (size_t i = 0; i < N; i++) {
		res.push_back(rand() % N);
	}
	return res;
}

// The function prints data to console, with prefix 'pref'
void printVect(vector<int> const& data, string pref = "") {
	cout << pref << endl;
	cout << "Data print. Size: " << data.size() << endl;
	for (auto const& it : data) {
		cout << it << ' ';
	}
	cout << "\nEnd print.\n";
}

// Returns true if data is sorted, and false otherwise
bool is_sorted(vector<int> const& data) {
	for (auto it0 = data.begin(), it1 = data.begin() + 1; it1 < data.end(); it0++, it1++) {
		if (*it0 > *it1)
			return false;
	}
	return true;
}

// Calculates execution time of the sort algorithm. 
// beg - initial array size, N - steps number, step - increment array size step
vector<int> getTimes(size_t beg, size_t N, size_t step, std::function<void(int*,int*)> sort, size_t init=10) {
	vector<int> res;
	for (size_t i = 0; i < N; ++i) {

		cout << "iteration " << i << "...\n";

		size_t size = beg + i * step;
		auto data = randGen(size, init);
		auto data_src = vector<int>(data);
		auto begTime = chrono::steady_clock::now();

		sort(data.begin()._Ptr, data.end()._Ptr);

		auto endTime = chrono::steady_clock::now();
		auto elapsTime = chrono::duration_cast<chrono::milliseconds>(endTime - begTime);
		res.push_back(elapsTime.count());

		if (!is_sorted(data)) {
			cout << "Sort error!!!\n";
			printVect(data_src, "Source array:");
			printVect(data, "\nSorted array:");
			system("pause");
		}

	}
	return res;
}

int main() {
	auto times = getTimes(10000, 45, 2000, [](int* a, int* b) { SortAlg::heap_sort(a, b); });
	cout << "Ok!\nTime table:\n";
	for (int i = 0; i < times.size(); i++) {
		printf("(%d;%d) ", i, times.at(i));
	}


	//int a[] = { 13, 3, 8, 1, 15, 2, 3, 7, 4};
	//SortAlg::heap_sort(a, a + 9);

	return 0;
}