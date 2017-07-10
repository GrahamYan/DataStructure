/**
  *implement a container like std::set
 */
#ifndef SJTU_SET_HPP
#define SJTU_SET_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include <iostream>
//#include "utility.hpp"
#include "./pair.hpp"
#include "../Exceptions.hpp"
#include "../File.hpp"
#include <cassert>

using std::cin;
using std::cout;
using std::endl;

namespace sjtu {

template<
	class Key,
	class Compare = std::less<Key>
> class set {
public:
	enum Color{RED, BLACK};
	
private:
class Node;
	size_t cnt;
	Node *root, *nil, *max_p, *min_p;
	
	friend class iterator;
	friend class const_iterator;
	
public:
	/**
	  *the internal type of data.
	  *it should have a default constructor, a copy constructor.
	  *You can use sjtu::set as value_type by typedef.
	 */
//typedef pair<Key, T> value_type;
	/**
	  *see BidirectionalIterator at CppReference for help.
	 *
	  *if there is anything wrong throw InvalidIterator.
	  *    like it = set.begin(); --it;
	  *      or it = set.end(); ++end();
	 */
	class const_iterator;
	class iterator {
		friend class set;
		friend class const_iterator;
	//private:
	public:
		Node *p;
		const set *which;
		/**
		  *TODO add data members
		  *  just add whatever you want.
		 */
	public:
		iterator(): p(nullptr), which(nullptr) {
			// TODO
		}
		iterator(Node *_p, const set *_which): p(_p), which(_which) {
		}
		iterator(const iterator &other): p(other.p), which(other.which) {
			// TODO
		}
		/**
		  *return a new iterator which pointer n-next elements
		  *  even if there are not enough elements, just return the answer.
		  *as well as operator-
		 */
		/**
		  *TODO iter++
		 */
		iterator operator++(int) {
			if (!p) {
				throw InvalidIterator();
			}
			iterator temp = *this;
			p = p -> next;
			return temp;
		}
		/**
		  *TODO ++iter
		 */
		iterator & operator++() {
			if (!p) {
                throw InvalidIterator("");
			}
			p = p -> next;
			return *this;
		}
		/**
		  *TODO iter--
		 */
		iterator operator--(int) {
			if (which -> empty() || !which || p == which -> min_p) {
                throw InvalidIterator("");
			}
			iterator temp = *this;
			if (p) {
				p = p -> prev;
			} else {
				p = which -> max_p;
			}
			return temp;
		}
		/**
		  *TODO --iter
		 */
		iterator & operator--() {
			if (which -> empty() || !which || p == which -> min_p) {
				throw InvalidIterator();
			}
			if (p) {
				p = p -> prev;
			} else {
				p = which -> max_p;
			}
			return *this;
		}
		
		iterator & operator =(const iterator &rhs) {
			if (this != &rhs) {
				p = rhs.p;
				which = rhs.which;
			}
			return *this;
		}
		/**
		  *a operator to check whether two iterators are same (pointing to the same memory).
		 */
/*inline value_type & operator*() const {
	return *(p -> value);
}*/
		inline Key & operator*() const {
			return *(p -> value);
		}
		inline bool operator==(const iterator &rhs) const {
			return p == rhs.p && which == rhs.which;
		}
		inline bool operator==(const const_iterator &rhs) const {
			return p == rhs.p && which == rhs.which;
		}
		/**
		  *some other operator for iterator.
		 */
		inline bool operator!=(const iterator &rhs) const {
			return p != rhs.p || which != rhs.which;
		}
		inline bool operator!=(const const_iterator &rhs) const {
			return p != rhs.p || which != rhs.which;
		}
		Key *operator->() const noexcept {
			return p -> value;
		}
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
	friend class set;
	friend class iterator;
	private:
		// data members.friend class set;
		Node *p;
		const set *which;
	public:
		const_iterator(): p(nullptr), which(nullptr) {
			// TODO
		}
		const_iterator(Node *_p, const set *_which): p(_p), which(_which) {
		}
		const_iterator(const const_iterator &other): p(other.p), which(other.which) {
			// TODO
		}
		const_iterator(const iterator &other): p(other.p), which(other.which) {
			// TODO
		}
		// And other methods in iterator.
		// And other methods in iterator.
		// And other methods in iterator.
		const_iterator operator++(int) {
			if (!p) {
				throw InvalidIterator();
			}
			const_iterator temp = *this;
			p = p -> next;
			return temp;
		}
		/**
		  *TODO ++iter
		 */
		const_iterator & operator++() {
			if (!p) {
				throw InvalidIterator();
			}
			p = p -> next;
			return *this;
		}
		const_iterator & operator =(const iterator &rhs) {
			//if (this != &rhs) {
				p = rhs.p;
				which = rhs.which;
			//}
			return *this;
		}
		/**
		  *TODO iter--
		 */
		const_iterator operator--(int) {
			if (which -> empty() || !which || p == which -> min_p) {
				throw InvalidIterator();
			}
			const_iterator temp = *this;
			if (p) {
				p = p -> prev;
			} else {
				p = which -> max_p;
			}
			return temp;
		}
		/**
		  *TODO --iter
		 */
		const_iterator & operator--() {
			if (which -> empty() || !which || p == which -> min_p) {
				throw InvalidIterator();
			}
			if (p) {
				p = p -> prev;
			} else {
				p = which -> max_p;
			}
			return *this;
		}
		/**
		  *a operator to check whether two iterators are same (pointing to the same memory).
		 */
/*inline value_type & operator*() const {
	return *(p -> value);
}*/
		inline Key & operator*() const {
			return *(p -> value);
		}
		inline bool operator==(const const_iterator &rhs) const {
			return p == rhs.p && which == rhs.which;
		}
		inline bool operator==(const iterator &rhs) const {
			return p == rhs.p && which == rhs.which;
		}
		/**
		  *some other operator for iterator.
		 */
		inline bool operator!=(const const_iterator &rhs) const {
			return p != rhs.p || which != rhs.which;
		}
		inline bool operator!=(const iterator &rhs) const {
			return p != rhs.p || which != rhs.which;
		}
/*inline value_type *operator->() const noexcept {
	return p -> value;
}*/
	};
	
	friend BinaryOutput &print_tree(BinaryOutput &out, const set &obj, Node *now) {
		/*out << now -> value -> first;
		out << now -> value -> second;*/
		out << *(now -> value);
//std::cerr << *(now -> value) << std::endl;
		out << now -> col;
//std::cerr << now -> col << std::endl;
//cout << now -> value -> first << " " << now -> value -> second << " " << now -> col << endl;
		if (now -> child[0] != obj.nil) {
			out << string("left_exist");
//std::cerr << "left exist" << std::endl;
//cout << "left exist" << endl;
			print_tree(out, obj, now -> child[0]);
		} else {
			out << string("left_not_exist");
//std::cerr << "left not exist" << std::endl;
//cout << "left not exist" << endl;
		}
		if (now -> child[1] != obj.nil) {
			out << string("right_exist");
//std::cerr << "right exist" << std::endl;
//cout << "right exist" << endl;
			print_tree(out, obj, now -> child[1]);
		} else {
			out << string("right_not_exist");
//std::cerr << "right not exist" << std::endl;
//cout << "right not exist" << endl;
		}
		if (now != obj.root) {
			out << string("up");
//std::cerr << "up" << std::endl;
//cout << "up" << endl;
		}
        return out;
	}
	
	friend BinaryOutput &operator << (BinaryOutput &out, const set &obj) {
		out << (int)obj.cnt;
//std::cerr << obj.cnt << std::endl;
		if (obj.cnt) {
			print_tree(out, obj, obj.root);
		}
		out << string("end_tree");
//std::cerr << "end tree" << std::endl;
		return out;
	}
	
	friend BinaryInput &operator >> (BinaryInput &in, set &obj) {
		int temp_cnt, temp_col;
		in >> temp_cnt;
		obj.cnt = temp_cnt;
		if (!temp_cnt) {
			return in;
		}
		//value_type temp_value;
		Key temp_value;
		/*in >> temp_value.first;
		in >> temp_value.second;*/
		in >> temp_value;
		in >> temp_col;
		obj.root = new Node(temp_value, temp_col == RED ? RED : BLACK);
		obj.root -> child[0] = obj.root -> child[1] = obj.nil;
		Node *now = obj.root;
		string str;
		while (1) {
			in >> str;
			if (str == string("end_tree")) {
				break;
			}
			if (str == string("up")) {
				now = now -> father;
				continue;
			}
			if (str[0] == 'l') {
				if (str[5] == 'e') {
					/*in >> temp_value.first;
					in >> temp_value.second;*/
					in >> temp_value;
					in >> temp_col;
					now -> child[0] = new Node(temp_value, temp_col == RED ? RED : BLACK);
					now -> child[0] -> child[0] = obj.nil;
					now -> child[0] -> child[1] = obj.nil;
					now -> child[0] -> father = now;
					now = now -> child[0];
				} else {
					continue;
				}
			} else {
				if (str[6] == 'e') {
					/*in >> temp_value.first;
					in >> temp_value.second;*/
					in >> temp_value;
					in >> temp_col;
					now -> child[1] = new Node(temp_value, temp_col == RED ? RED : BLACK);
					now -> child[1] -> child[0] = obj.nil;
					now -> child[1] -> child[1] = obj.nil;
					now -> child[1] -> father = now;
					now = now -> child[1];
				} else {
					continue;
				}
			}
		}
		obj.get_prev_next();
	}
	
	/**
	  *TODO two constructors
	 */
	set(): cnt(0), root(nullptr), max_p(nullptr), min_p(nullptr), nil(new Node()) {
	}
	set(const set &other): cnt(other.cnt), nil(new Node()) {
		copy(root, other.root);
		get_prev_next();
	}
	inline void copy(Node *&lhs, Node *rhs) {
		if (!rhs) {
			lhs = nullptr;
			return;
		}
		lhs = new Node(rhs -> value, rhs -> col);
		for (int k = 0; k < 2; ++k) {
			if (rhs -> child[k] && rhs -> child[k] -> value) {
				copy(lhs -> child[k], rhs -> child[k]);
				lhs -> child[k] -> father = lhs;
			} else {
				lhs -> child[k] = nil;
			}
		}
	}
	inline void dfs_prev_next(Node *u, Node *a[], int &ind) {
		if (u == nil) {
			return;
		}
		dfs_prev_next(u -> child[0], a, ind);
		a[++ind] = u;
		dfs_prev_next(u -> child[1], a, ind);
		return;
	}
	inline void get_prev_next() {
		Node **a = new Node *[cnt + 10];
		int ind = 0;
		if (!cnt) {
			root = min_p = max_p = nullptr;
			delete [] a;
			return;
		}
		dfs_prev_next(root, a, ind);
		a[0] = a[++ind] = nullptr;
		min_p = a[1];
		max_p = a[ind - 1];
		for (int i = 1; i < ind; ++i) {
			a[i] -> prev = a[i - 1];
			a[i] -> next = a[i + 1];
		}
		delete [] a;
	}
	/**
	  *TODO assignment operator
	 */
	set & operator=(const set &other) {
		if (this != &other) {
			deconstruct();
			nil = new Node();
			cnt = other.cnt;
			copy(root, other.root);
			get_prev_next();
		}
		return *this;
	}
	/**
	  *TODO Destructors
	 */
	~set() {
		deconstruct();
	}
	inline void destroy_node(Node *u) {
		if (!u || u == nil) {
			return;
		}
		destroy_node(u -> child[0]);
		destroy_node(u -> child[1]);
		delete u;
	}
	inline void deconstruct() {
		destroy_node(root);
		if (nil) delete nil;
		root = nullptr;
		min_p = nullptr;
		max_p = nullptr;
		cnt = 0u;
	}
	/**
	  *TODO
	  *access specified element with bounds checking
	  *Returns a reference to the setped value of the element with key equivalent to key.
	  *If no such element exists, an exception of type `IndexOutOfBound'
	 */
	 
	/*inline T & at(const Key &key) {
		Node *ret = find_node(root, key);
		if (ret) {
			return ret -> value -> second;
		} else {
			throw IndexOutOfBound();
		}
	}
	inline const T & at(const Key &key) const {
		Node *ret = find_node(root, key);
		if (ret) {
			return ret -> value -> second;
		} else {
			throw IndexOutOfBound();
		}
	}*/
	/**
	  *TODO
	  *access specified element 
	  *Returns a reference to the value that is setped to a key equivalent to key,
	  *  performing an insertion if such key does not already exist.
	 */
	/*inline T & operator[](const Key &key) {
		Node *ret = find_node(root, key);
		if (ret) {
			return ret -> value -> second;
		} else {
			value_type temp = value_type(key, T());
			iterator iter = insert(temp).first;
			return iter -> second;
		}
	}*/
	/**
	  *behave like at() throw IndexOutOfBound if such key does not exist.
	 */
	/*inline const T & operator[](const Key &key) const {
		Node *ret = find_node(root, key);
		if (ret) {
			return ret -> value -> second;
		} else {
			throw IndexOutOfBound();
		}
	}*/
	/**
	  *return a iterator to the beginning
	 */
	inline iterator begin() {
		return iterator(min_p, this);
	}
	inline const_iterator cbegin() const {
		return const_iterator(min_p, this);
	}
	/**
	  *return a iterator to the end
	  *in fact, it returns past-the-end.
	 */
	inline iterator end() {
		return iterator(nullptr, this);
	}
	inline const_iterator cend() const {
		return const_iterator(nullptr, this);
	}
	/**
	  *checks whether the container is empty
	  *return true if empty, otherwise false.
	 */
	inline bool empty() const {
		return cnt == 0;
	}
	/**
	  *returns the number of elements.
	 */
	inline size_t size() const {
		return cnt;
	}
	/**
	  *clears the contents
	 */
	inline void clear() {
		deconstruct();
		nil = new Node();
	}
	/**
	  *insert an element.
	  *return a pair, the first of the pair is
	  *  the iterator to the new element (or the element that prevented the insertion), 
	  *  the second one is true if insert successfully, or false.
	 */
	inline pair<iterator, bool> insert(const Key &value) {
		Node *nownode = find_node(root, value);
		if (nownode) {
			return pair<iterator, bool>(iterator(nownode, this), false);
		}
		Node *newnode = insert_node(root, value);
		insert_rebalance(newnode);
		return pair<iterator, bool>(iterator(newnode, this), true);
	}
	/**
	  *erase the element at pos.
	 *
	  *throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	inline void erase(iterator pos) {
		if (!pos.p || pos.which != this) {
            throw InvalidIterator("");
		}
		delete_node(pos.p);
	}
	/**
	  *Returns the number of elements with key 
	  *  that compares equivalent to the specified argument,
	  *  which is either 1 or 0 
	  *    since this container does not allow duplicates.
	  *The default method of check the equivalence is !(a < b || b > a)
	 */
	inline size_t count(const Key &key) const {
		if (find_node(root, key)) {
			return 1;
		} else {
			return 0;
		}
	}
	/**
	  *Finds an element with key equivalent to key.
	  *key value of the element to search for.
	  *Iterator to an element with key equivalent to key.
	  *  If no such element is found, past-the-end (see end()) iterator is returned.
	 */
	inline iterator find(const Key &key) {
		Node *p = find_node(root, key);
		iterator temp(p, this);
		return temp;
	}
	inline const_iterator find(const Key &key) const {
		Node *p = find_node(root, key);
		const_iterator temp(p, this);
		return temp;
	}

private:
	
	struct Node {
		//value_type *value;
		Key *value;
		Color col;
		Node *child[2], *father, *prev, *next;
		Node():
			value(nullptr), father(nullptr), child{nullptr, nullptr}, prev(nullptr), next(nullptr), col(BLACK) {
		}
		Node(const Key &val, const Color& _col):
			value(new Key(val)), father(nullptr), child{nullptr, nullptr}, prev(nullptr), next(nullptr), col(_col) {
		}
		Node(Key *val, const Color& _col):
			value(new Key(*val)), father(nullptr), child{nullptr, nullptr}, prev(nullptr), next(nullptr), col(_col) {
		}
		/*Node(Key *_key, T *_val, Color _col):
			value(new value_type(*_key, *_val)), father(nullptr), child{nullptr, nullptr}, prev(nullptr), next(nullptr), col(_col) {
		}
		Node(Key *_key, T *_val, Node *fa = nullptr, Node *lc = nullptr, Node *rc = nullptr, Node *_prv = nullptr, Node *_nxt = nullptr, Color _col = BLACK):
			value(new value_type(*_key, *_val)), father(fa), child{lc, rc}, prev(_prv), next(_nxt), col(_col) {
		}*/
		~Node() {
			if (value) {
				delete value;
			}
		}
		//dangerous
		Node(const Node& rhs):
			value(rhs.value), father(rhs.father), child{rhs.child[0], rhs.child[1]}, prev(rhs.prev), next(rhs.next), col(rhs.col) {
		}
		Node(Node&& rhs):
			value(rhs.value), father(rhs.father), child{rhs.child[0], rhs.child[1]}, prev(rhs.prev), next(rhs.next), col(rhs.col) {
			rhs.value = nullptr;
			rhs.father = rhs.child[0] = rhs.child[1] = prev = next = nullptr;
		}
		//dangerous
		Node& operator = (const Node& rhs) {
			if (this != &rhs) {
				if (value) {
					delete value;
				}
				value = rhs.value;
				father = rhs.father;
				prev = rhs.prev;
				next = rhs.next;
				col = rhs.col;
				for (int i = 0; i < 2; ++i) {
					child[i] = rhs.child[i];
				}
			}
			return *this;
		}
		Node& operator = (Node&& rhs) {
			if (this != &rhs) {
				value = rhs.value;
				prev = rhs.prev;
				next = rhs.next;
				father = rhs.father;
				col = rhs.col;
				for (int i = 0; i < 2; ++i) {
					child[i] = rhs.child[i];
				}
				rhs.value = nullptr;
				rhs.father = rhs.prev = rhs.next = rhs.child[0] = rhs.child[1] = nullptr;
			}	
			return *this;
		}
	};
	
	inline Node *find_node(Node *u, const Key &_key) const {
		if (u == nil || !u) {
			return nullptr;
		}
		if (Compare()(*(u -> value), _key)) {
			return find_node(u -> child[1], _key);
		}
		if (Compare()(_key, *(u -> value))) {
			return find_node(u -> child[0], _key);
		}
		return u;
	}
	inline Node *find_smaller_node(Node *u, const Key& _key) {
		if (u == nil || !u) {
			return nullptr;
		}
		if (Compare()(*(u -> value), _key)) {
			Node *temp = find_smaller_node(u -> child[1], _key);
			return temp ? temp : u;
		}
		return find_smaller_node(u -> child[0], _key);
	}
	inline Node *find_bigger_node(Node *u, const Key& _key) {
		if (u == nil || !u) {
			return nullptr;
		}
		if (Compare()(_key, *(u -> value))) {
			Node *temp = find_bigger_node(u -> child[0], _key);
			return temp ? temp : u;
		}
		return find_bigger_node(u -> child[1], _key);
	}
	
	inline void link(Node *fa, Node *c, int k) {
		c -> father = fa;
		if (fa) {
			fa -> child[k] = c;
		}
	}
	inline void rotate(Node *x) {
		Node *y = x -> father;
		Node *z = y -> father;
		int k_x = (y -> child[1]) == x;
		link(y, x -> child[k_x ^ 1], k_x);
		link(x, y, k_x ^ 1);
		if (z) {
			link(z, x, (z -> child[1]) == y);
		} else {
			root = x;
			x -> father = nullptr;
		}
	}
	inline Node *sibling(const Node *u) {
		if (u -> father) {
			return u -> father -> child[(u -> father -> child[0]) == u];
		} else {
			return nullptr;
		}
	}
	inline void replace_node(Node *u, Node *v) {
		Node *t_u, *t_v;
		t_u = u -> father, t_v = v -> father;
		int k_u, k_v;
		if (!t_v) {
			swap(t_u, t_v);
		}
		if (!t_u) {
			k_v = (t_v -> child[1]) == v;
			link(t_v, u, k_v);
			root = v;
			v -> father = nullptr;
		} else {
			k_u = (t_u -> child[1]) == u, k_v = (t_v -> child[1]) == v;
			link(t_u, v, k_u);
			link(t_v, u, k_v);
		}
		for (int k = 0; k < 2; ++k) {
			t_u = u -> child[k];
			t_v = v -> child[k];
			link(u, t_v, k);
			link(v, t_u, k);
		}
	}
	
	inline Node *insert_node(Node *u, const Key &value) {
		Node *newnode(new Node(value, RED));
		newnode -> child[0] = newnode -> child[1] = nil;
		++cnt;
		if (!u) {
			root = min_p = max_p = newnode;
			newnode -> col = BLACK;
			return newnode;
		}
		Node *pre = nullptr;
		while (u != nil) {
			pre = u;
			if (Compare()(*(u -> value), *(newnode -> value))) {
				u = u -> child[1];
			} else {
				u = u -> child[0];
			}
		}
		int k = Compare()(*(pre -> value), *(newnode -> value));
		pre -> child[k] = newnode;
		newnode -> father = pre;
		newnode -> child[0] = newnode -> child[1] = nil;
		newnode -> prev = find_smaller_node(root, *(newnode -> value));
		newnode -> next = find_bigger_node(root, *(newnode -> value));
		if (newnode -> prev) {
			newnode -> prev -> next = newnode;
		} else {
			min_p = newnode;
		}
		if (newnode -> next) {
			newnode -> next -> prev = newnode;
		} else {
			max_p = newnode;
		}
		return newnode;
	}
	
	inline void insert_rebalance(Node *u) {
		while (u) {
			if (!(u -> father)) {
				root = u;
				u -> col = BLACK;
				return;
			} // case 1
			Node *par = u -> father;
			if (par -> col == BLACK) {
				return;
			} // case 2
			Node *parpar = par -> father;
			int k_u = (par -> child[1]) == u;
			int k_p = (parpar -> child[1]) == par;
			Node *uncle = parpar -> child[k_p ^ 1];
			if (par -> col == uncle -> col) {
				parpar -> col = RED;
				par -> col = uncle -> col = BLACK;
				u = parpar;
				continue;
			} // case 3
			if (k_u != k_p) {
				rotate(u);
				k_u = k_p;
				swap(u, par);
			} // case 4
			u -> father -> col = BLACK;
			parpar -> col = RED;
			rotate(u -> father);
			// case 5
		}
	}
	
	inline void delete_node(Node *u) {
		--cnt;
		if (u -> child[0] != nil && u -> child[1] != nil) {
			Node *v = u -> child[1];
			while (v -> child[0] != nil) {
				v = v -> child[0];
			}
			replace_node(u, v);
			swap(u -> col, v -> col);
			if (root == u) {
				root = v;
			}
		}
		
		if (cnt == 0u) {
			min_p = max_p = root = nullptr;
			delete u;
			return;
		}
		Node *prv = u -> prev, *nxt = u -> next;
		if (prv) {
			prv -> next = nxt;
		} else {
			min_p = nxt;
		}
		if (nxt) {
			nxt -> prev = prv;
		} else {
			max_p = prv;
		}
		Node *par = u -> father;
		int k_c = (u -> child[0]) == nil;
		if (!par) {
			root = u -> child[k_c];
			u -> child[k_c] -> father = nullptr;
			root -> col = BLACK;
			delete u;
			return;
		}
		int k_u = (par -> child[1]) == u;
		link(par, u -> child[k_c], k_u);
		
		if (u -> col == RED) {
			delete u;
			return;
		}
		if (u -> child[k_c] -> col == RED) {
			u -> child[k_c] -> col = BLACK;
			delete u;
			return;
		}
		delete_case(u -> child[k_c]);
		delete u;
	}
	inline void delete_case(Node *n) {
		while (1) {
			Node *p = n -> father;
			if (!p) {
				n -> col = BLACK;
				root = n;
				return;
			} // case 1
			Node *s = sibling(n);
			Node *s_c[2] = {s -> child[0], s -> child[1]};
			
			if (s -> col == RED) {
				p -> col = RED;
				s -> col = BLACK;
				rotate(s);
				if (n == nil) {
					n -> father = p;
				}
				s = sibling(n);
				s_c[0] = s -> child[0];
				s_c[1] = s -> child[1];
			} // case 2
			if (p -> col == BLACK && s -> col == BLACK && s_c[0] -> col == BLACK && s_c[1] -> col == BLACK) {
				s -> col = RED;
				n = n -> father;
				continue;
			} // case 3
			if (p -> col == RED && s -> col == BLACK && s_c[0] -> col == BLACK && s_c[1] -> col == BLACK) {
				s -> col = RED;
				n -> father -> col = BLACK;
				return;
			} // case 4
			int k_n = (n -> father -> child[1]) == n;
			if (s -> col == BLACK && s_c[k_n] -> col == RED && s_c[k_n ^ 1] -> col == BLACK) {
				s -> col = RED;
				s_c[k_n] -> col = BLACK;
				rotate(s_c[k_n]);
				s = s_c[k_n];
				s_c[0] = s -> child[0];
				s_c[1] = s -> child[1];
			} // case 5
			s -> col = p -> col;
			p -> col = BLACK;
			s_c[k_n ^ 1] -> col = BLACK;
			rotate(s);
			return;
			//case 6
		}
	}
	
/*public:
	void print_tree() {
		if (!cnt) {
			cout << "empty tree" << endl;
			return;
		}
assert(root -> father == nullptr);
assert(min_p && max_p);
		cout << "----------here is the tree---------" << endl;
		print(root);
		cout << "---------end of tree---------" << endl;
	}
	void print(Node *u) {
		if (u == nil) return;
		cout << "pair < " << u -> value -> first << " , " << u -> value -> second << ">";
		cout << " color = " << ((u -> col) == RED ? "RED  " : "BLACK");
		if (u -> child[0] != nil) cout << " lc = " << u -> child[0] -> value -> first;
		if (u -> child[1] != nil) cout << " rc = " << u -> child[1] -> value -> first;
		cout << " " << endl;
		print(u -> child[0]);
		print(u -> child[1]);
assert(u -> child[0] == nil || u -> child[0] -> father == u);
assert(u -> child[1] == nil || u -> child[1] -> father == u);
	}*/
};

}

#endif
