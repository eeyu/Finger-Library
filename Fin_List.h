#ifndef __LIST__
#define __LIST__

#include <assert.h>

// IMPORTANT: Case where pointers are stored...need to delete the pointers first before the list

template <T>
class List {
	T* buffer;
	unsigned int capacity = 0;
	unsigned int size = 0;
	const int default_capacity = 1;
	const int expansion_amount = 10;

	List() {
		buffer = new T[default_capacity];
	}

	~List() {
		delete[] buffer;
	}

	void expandBy(int extra_capacity) {
		new_capacity = default_capacity + extra_capacity;
		T* new_buffer = new T[new_capacity];
		for (int i = 0; i < capacity; i++) {
			new_buffer[i] = buffer[i];
		}

		capacity = new_capacity;
		delete[] buffer;
		buffer = new_buffer;
	}

	void addToEnd(T item) {
		size++;
		if (size > capacity) {
			expandBy(expansion_amount);
		}
		set(size-1, T);
	}

	void set(unsigned int idx, T item) {
		if (idx < size) {
			buffer[idx] = T;
		}
	}

	void remove(int idx) {
		if (idx < size) {
			for (int i = idx; i < size - 1; i++) {
				buffer[i] = buffer[i+1];
			}
			size--;
		}
	}

	T get(int idx) {
		assert(idx < size);
		return buffer[idx];
	} 

	unsigned int size() {
		return size;
	}


};

#endif