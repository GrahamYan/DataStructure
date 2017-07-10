#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "../Exceptions.hpp"

#include <climits>
#include <cstddef>

//using sjtu::Exception;

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template<typename T>
class vector {
	T *vec;
	size_t sz;
	size_t cap;
	
	void resize() {
		if (sz == cap) {
			T *tmp = vec;
			if (cap == 0) cap = 1;
			else {
				cap *= 2;
			}
			vec = reinterpret_cast<T*> (operator new (sizeof(T) * cap));
			for (int i = 0; i < sz; ++i) {
				new (static_cast<void*> (&vec[i])) T(tmp[i]);
				tmp[i].~T();
			}
			operator delete (tmp);
		}
	} 
	
public:
	/**
	 * TODO
	 * a type for actions of the elements of a vector, and you should write
	 *   a class named const_iterator with same interfaces.
	 */
	/**
	 * you can see RandomAccessIterator at CppReference for help.
	 */
	friend class iterator;
	class const_iterator;
	class iterator {
	private:
		T **p;
		size_t ptr;
		iterator(T ** _c , size_t _pos) : p(_c) , ptr(_pos) {}
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		friend iterator vector::begin();
		friend iterator vector::end();
		friend iterator vector::insert(iterator pos, const T &value);
		friend iterator vector::insert(const size_t &ind, const T &value);
		friend iterator vector::erase(iterator pos);
		friend iterator vector::erase(const size_t &ind);
		friend class const_iterator;
	public:
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, just return the answer.
		 * as well as operator-
		 */
		iterator operator+(const int &n) const {
			iterator tmp (p , ptr + n);
			
			return tmp;	
			//TODO
		}
		iterator operator-(const int &n) const {
			iterator tmp (p , ptr - n);
			
			return tmp;
			//TODO
		}
		// return the distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const {
			if (p != rhs.p) throw InvalidIterator();
			else {
				int tmp;
				tmp = ptr - rhs.ptr;
				
				return ptr;
			}
			//TODO
		}
		iterator operator+=(const int &n) {
			iterator tmp(p , ptr + n);
			
			return tmp;
			//TODO
		}
		iterator operator-=(const int &n) {
			iterator tmp(p , ptr - n);
			
			return tmp;
			//TODO
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			iterator tmp(p , ptr);
			ptr += 1;
			
			return tmp;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() {
			ptr += 1;
			
			return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			iterator tmp(p , ptr);
			ptr -= 1;
			
			return tmp;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--() {
			ptr -= 1;
			
			return *this;
		}
		/**
		 * TODO *it
		 */
		T& operator*() const{
			return (*p)[ptr];
		}
		// T* operator->() { return p[ptr]; }
			
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const {
			if (rhs.ptr == ptr && rhs.p == p) return true;
			else return false;
		}
		bool operator==(const const_iterator &rhs) const {
			return rhs.ptr == ptr && rhs.p == p;
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
			if (rhs.ptr == ptr && rhs.p == p) return false;
			else return true;
		}
		bool operator!=(const const_iterator &rhs) const {
			return rhs.ptr == ptr || rhs.p == p;
		}
	};
	/**
	 * TODO
	 * has same function as iterator, just for a const object.
	 */
	class const_iterator {                /////////////////////////////////////////////////////////////////////////////
	private:
		T * const*p;
		size_t ptr;
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		friend const_iterator vector::cbegin() const;
		friend const_iterator vector::cend() const;
		friend iterator;
		const_iterator(T * const* _c , size_t _pos) : p(_c) , ptr(_pos) {}
	public:
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, just return the answer.
		 * as well as operator-
		 */
		const_iterator operator+(const int &n) const {
			const_iterator tmp(p , ptr + n);
			
			return tmp;	
			//TODO
		}
		const_iterator operator-(const int &n) const {
			const_iterator tmp(p , ptr - n);
			
			return tmp;
			//TODO
		}
		// return the distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		int operator-(const const_iterator &rhs) const {
			if (p != rhs.p) throw InvalidIterator();
			else {
				int tmp;
				tmp = ptr - rhs.ptr;
				
				return ptr;
			}
			//TODO
		}
		const_iterator operator+=(const int &n) {
			const_iterator tmp(p , ptr + n);
			
			return tmp;
			//TODO
		}
		const_iterator operator-=(const int &n) {
			const_iterator tmp(p , ptr - n);
			
			return tmp;
			//TODO
		}
		/**
		 * TODO iter++
		 */
		const_iterator operator++(int) {
			const_iterator tmp(p , ptr);
			ptr += 1;
			
			return tmp;
		}
		/**
		 * TODO ++iter
		 */
		const_iterator& operator++() {
			ptr += 1;
			
			return *this;
		}
		/**
		 * TODO iter--
		 */
		const_iterator operator--(int) {
			const_iterator tmp(p , ptr);
			ptr -= 1;
			
			return tmp;
		}
		/**
		 * TODO --iter
		 */
		const_iterator& operator--() {
			ptr += 1;
			
			return *this;
		}
		/**
		 * TODO *it
		 */
		T& operator*() const{
			return (*p)[ptr];
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		// T* operator->() { return p[ptr]; }
		bool operator==(const iterator &rhs) const {
			return rhs.ptr == ptr && rhs.p == p;
		}
		bool operator==(const const_iterator &rhs) const {
			return rhs.ptr == ptr && rhs.p == p;
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
			if(rhs.ptr == ptr && rhs.p == p) return false;
			else return true;
		}
		bool operator!=(const const_iterator &rhs) const {
			return rhs.ptr != ptr || rhs.p != p;
		}
	};
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	/**
	 * TODO Constructs
	 * Atleast three: default constructor, copy constructor and a constructor for std::vector
	 */
	vector() : sz(0) , cap(0) , vec(NULL) {}
	vector(const vector &other) {
		cap = other.capacity();
		sz = other.size();
		vec = reinterpret_cast<T*> (operator new (sizeof(T) * cap));
		for (int i = 0; i < sz; ++i) {
			new (static_cast<void*> (&vec[i])) T(other[i]);
		}
	}
	template<typename A>
	vector(const A &other) {
		cap = other.capacity();
		sz = other.sz;
		vec = reinterpret_cast<T*> (operator new (sizeof(T) * cap));
		for (int i = 0; i < sz; ++i) {
			new (static_cast<void*> (&vec[i])) T(other[i]);
		}
	}
	/**
	 * TODO Destructor
	 */
	~vector() {
		int n = sz;
		for (int i = 0; i < sz; ++i) {
			vec[i].~T(); 
		} 
		operator delete (vec);
	}
	/**
	 * TODO Assignment operator
	 */
	vector &operator=(const vector &other) {
		for (int i = 0; i < sz; ++i) {
			vec[i].~T();
		}
		operator delete(vec);
		cap = other.capacity();
		sz = other.size();
		vec = reinterpret_cast<T*> (operator new (sizeof(T) * (other.capacity())));
		for (int i = 0; i < other.size(); ++i) {
			new (static_cast<void*> (&vec[i])) T(other[i]);
		}
		
		return *this;
	}
	/**
	 * assigns specified element with bounds checking
	 * throw IndexOutOfBound if pos is not in [0, size)
	 */
	T & at(const size_t &pos) {
		if (pos >= sz || pos < 0) throw IndexOutOfBound();
		
		return vec[pos];
	}
	const T & at(const size_t &pos) const {
		if (pos >= sz || pos < 0) throw IndexOutOfBound();
		
		return vec[pos];
	}
	/**
	 * assigns specified element with bounds checking
	 * throw IndexOutOfBound if pos is not in [0, size)
	 * !!! Pay attentions
	 *   In STL this operator does not check the boundary but I want you to do.
	 */
	T & operator[](const size_t &pos) {
        if (pos >= sz || pos < 0) throw IndexOutOfBound("");
		
		return vec[pos];
	}
	const T & operator[](const size_t &pos) const {
        if (pos >= sz || pos < 0) throw IndexOutOfBound("");

		return vec[pos];
	}
	/**
	 * access the first element.
	 * throw ContainerIsEmpty if size == 0
	 */
	const T & front() const {
		if (sz == 0) throw ContainerIsEmpty();
		else return vec[0];
	}
	/**
	 * access the last element.
	 * throw ContainerIsEmpty if size == 0
	 */
	const T & back() const {
		if (sz == 0) throw ContainerIsEmpty();
		else return vec[sz - 1];
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() {
		return iterator(&vec , 0);
	}
	const_iterator cbegin() const {
		return const_iterator(&vec , 0);
	}
	/**
	 * returns an iterator to the end.
	 */
	iterator end() {
		return iterator(&vec , sz);
	}
	const_iterator cend() const {
		return const_iterator(&vec , sz);
	}
	/**
	 * checks whether the container is empty
	 */
	bool empty() const {
		return sz == 0;
	}
	/**
	 * returns the number of elements
	 */
	size_t size() const {
		return sz;
	}
	/**
	 * returns the number of elements that can be held in currently allocated storage.
	 */
	size_t capacity() const {
		return cap;
	}
	/**
	 * clears the contents
	 */
	void clear() {
		for (int i = 0; i < sz; ++i) {
			vec[i].~T();
		}
		operator delete(vec);
		vec = NULL;
		cap = 0;
		sz = 0;
	}
	/**
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value.
	 */
	iterator insert(iterator pos, const T &value) {
		resize();
		new (static_cast<void*> (&vec[sz])) T(vec[sz - 1]);
		for (int i = sz - 1; i >= pos.ptr + 1; --i) {
			vec[i].~T();
			new (static_cast<void*> (&vec[i])) T(vec[i - 1]);
		} 
		sz += 1;
		(*pos.p)[pos.ptr].~T();
		new (static_cast<void*> (&vec[pos.ptr])) T(value);
		iterator tmp(pos.p , pos.ptr);
		
		return tmp;
	}
	/**
	 * inserts value at index ind.
	 * after inserting, this->at(ind) == value is true
	 * returns an iterator pointing to the inserted value.
	 * throw IndexOutOfBound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
	 */
	iterator insert(const size_t &ind, const T &value) {
		if (ind > sz || ind < 0) throw IndexOutOfBound();
		return insert(iterator(&vec , ind), value);
	}
	/**
	 * removes the element at pos.
	 * return an iterator pointing to the following element.
	 * If the iterator pos refers the last element, the end() iterator is returned.
	 */
	iterator erase(iterator pos) {
		for (int i = pos.ptr; i <= sz - 2; ++i) {
			vec[i].~T();
			new (static_cast<void*> (&(vec[i]))) T(vec[i + 1]);
		} 
		sz -= 1;
		vec[sz - 1].~T();
		iterator tmp(pos.p , pos.ptr);
		
		return tmp;
	}
	/**
	 * removes the element with index ind.
	 * return an iterator pointing to the following element.
	 * throw IndexOutOfBound if ind >= size
	 */
	iterator erase(const size_t &ind) {
		if (ind >= sz || ind < 0) throw IndexOutOfBound();
		return erase(iterator(&vec , ind));
	}
	/**
	 * adds an element to the end.
	 */
	void push_back(const T &value) {
		resize();
		new (static_cast<void*> (&vec[sz])) T(value);
		++sz;
	}
	/**
	 * remove the last element from the end.
	 * throw ContainerIsEmpty if size() == 0
	 */
	void pop_back() {
		if (sz == 0) throw ContainerIsEmpty();
		else {
			vec[sz - 1].~T();
			--sz;
			if (sz == 0) {
				operator delete (vec);
				vec = NULL;
				cap = 0; 
			}	
		}
	}
};


}

#endif
