#ifndef SJTU_PAIR_HPP
#define SJTU_PAIR_HPP

namespace sjtu {

	template <class T1, class T2>
	class pair {
		//typedef T1 first_type;
		//typedef T2 second_type;
	public:
		T1 first;
		T2 second;
		constexpr pair () : first(), second() {}
		pair(const T1 &a, const T2 &b) : first(a), second(b) {}
		template <class U1, class U2>
		pair(const U1 &a, const U2 &b): first(a), second(b) {}
		
		pair(const pair &p): first(p.first),second(p.second) {}
		pair(pair &&p): first(p.first),second(p.second) {}
		template <class U1, class U2>
		pair(const pair<U1, U2> &p): first(p.first),second(p.second) {}
		template <class U1, class U2>
		pair(pair<U1, U2> &&p): first(p.first),second(p.second) {}
		
		inline pair& operator = (const pair &x) {
			if (this != &x) {
				first = x.first;
				second = x.second;
			}
			return *this;
		}
		inline pair& operator = (pair &&x) {
			if (this != &x) {
				first = x.first;
				second = x.second;
			}
			return *this;
		}

		inline bool operator ==(const pair &x) {
			return x.first == first && x.second == second;
		}
		
		inline bool operator !=(const pair &x) {
			return x.first != first || x.second != second;
		}
		
		inline bool operator < (const pair &x) {
			return first < x.first || first == x.first && second < x.second;//|| (x.first <= y.first) && x.second < y.second;		
		}
		
		inline bool operator <= (const pair &x) {
			return first < x.first || first == x.first && second <= x.second;//|| (x.first <= y.first) && x.second < y.second;		
		}
		
		inline bool operator > (const pair &x) {
			return first > x.first || first == x.first && second > x.second;//|| (x.first <= y.first) && x.second < y.second;		
		}
		
		inline bool operator >= (const pair &x) {
			return first > x.first || first == x.first && second >= x.second;//|| (x.first <= y.first) && x.second < y.second;		
		}
		
	};
	
	template <class T1, class T2>
	inline pair<T1, T2> make_pair(const T1 &x, const T2 &y) {
		return pair<T1,T2>(x,y);
	}
	
}
#endif
