#pragma once
#include <vector>


class SortAlg {
public:

	// Bubble sort sucks!

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
};

