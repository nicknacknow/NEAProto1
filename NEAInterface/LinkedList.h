#pragma once

template<class T>
class LinkedList {
public:
	LinkedList() {}

	struct element {
		element() {}
		element(T v) : val(v) {}
		element* next = nullptr;
		T val;
	}*start = nullptr;

	/**
	 * @brief adds value to end of list
	*/
	void AddValue(T val) {
		if (start == nullptr) { this->start = new element(val); return; }

		element* i = start;
		while (i != nullptr) { // somewhat un-needed but just incase :P
			if (i->next == nullptr) break;
			i = i->next;
		}
		i->next = new element(val);
	}

	/**
	 * @brief removes value at given index
	*/
	void RemoveValue(int index) {
		element* i = start;
		while (i->next && index != 0) {
			index--;
			i = i->next;
		}
		if (i == nullptr || i->next == nullptr) return;
		i->next = i->next->next;
	}

	/**
	 * @return returns value at given index
	*/
	T getValue(int index) {
		element* i = start;
		while (i != nullptr) {
			if (index == 0) { // at the correct value
				return i->val;
			}
			if (i->next == nullptr) break;
			i = i->next;
			index--;
		}
		return i->val;
	}

	/**
	 * @brief pops value off of linked list and returns it.
	*/
	T popValue() {
		element* i = start;
		element* prev = i; // give it a value so when set ->next it isn't null and cause an error.. when prev is start, ->next will be nullptr anyway so no damage done

		while (i->next) {
			prev = i;
			i = i->next;
		}

		T val = i->val;
		prev->next = nullptr;
		return val;
	}

	/**
	 * @return returns number of elements in linked table
	*/
	int count() {
		int ret = (start == nullptr) ? 0 : 1;

		element* i = start;
		while (i != nullptr) {
			if (i->next == nullptr) break;
			i = i->next;
			ret++;
		}

		return ret;
	}
};