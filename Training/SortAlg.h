#pragma once
#include <vector>
#include <algorithm>
#include <iostream>


class SortAlg {
public:

	// Bubble sort sucks!
	// Merge sort - the best here. It's need to optimize heap sort.

	template <class T>
	static void bubble_sort(T* begin, T* end) {
		size_t size = end - begin;
		for (size_t i = 0; i < size - 1; i++) {
			for (size_t j = 0; j < size - i - 1; j++) {
				if (begin[j] > begin[j + 1]) {
					std::swap(begin[j], begin[j + 1]);
				}
			}
		}
	}

	template <class T>
	static void merge_sort(T* begin, T* end) {
		size_t size = end - begin;
		T* buffer = new T[size];
		for (size_t i = 1; i < size; i *= 2) {
			for (T* j = begin; j + i < end; j += 2 * i) {
				merge(j, j + i, min(j + 2 * i, end), buffer);
			}
		}
		delete [] buffer;
	}

	template <class T>
	static void heap_sort(T* begin, T* end) {
		Heap_p<T> heap(begin, end - begin);
		heap.sort();
	}

private:

	template <class T>
	static void merge(T* begin, T* mid, T* end, T* buffer) {
		T* p0, * p1, *pb;
		p0 = begin;
		p1 = mid;
		pb = buffer;
		while (true) {
			if (*p0 < *p1) {
				*(pb++) = *(p0++);
				if (p0 == mid) {
					for (; p1 != end; p1++, pb++)
						*pb = *p1;
					T* d, *s;
					for (d = begin, s = buffer; s != pb; s++, d++)
						*d = *s;
					return;
				}
			}
			else {
				*(pb++) = *(p1++);
				if (p1 == end) {
					for (; p0 != mid; p0++, pb++)
						*pb = *p0;
					T* d, * s;
					for (d = begin, s = buffer; s != pb; s++, d++)
						*d = *s;
					return;
				}
			}
		}
	}

	template <class T>
	static T min(T a, T b) {
		return a < b ? a : b;
	}
	
	// The heap don't allocate own memory! Only pointers
	template <class T>
	class Heap_p {
	public:
		Heap_p(T* a, size_t N) : a(a), N(N) {
			for (size_t i = N / 2; i != 0; i--) {
				size_t cur_i = i - 1;
				sift(cur_i, N);
			}
		}

		void sort() {
			for (size_t i = N-1; i > 0; i--) {
				std::swap(a[i], a[0]);
				sift(0, i);
			}
		}

	private:

		void sift(size_t cur_i, size_t size) {

			bool loop_out = true;
			while (loop_out) {
				size_t me_i;
				if (cur_i * 2 + 2 < size)
					me_i = a[cur_i * 2 + 1] > a[cur_i * 2 + 2] ? 2 * cur_i + 1 : 2 * cur_i + 2;
				else if (cur_i * 2 + 2 == size)
					me_i = cur_i * 2 + 1;
				else
					break;
				if (a[me_i] > a[cur_i]) {
					std::swap(a[me_i], a[cur_i]);
					cur_i = me_i;
				}
				else {
					loop_out = false;
				}
			}
		}

		T* a;
		size_t N;

	};

};

