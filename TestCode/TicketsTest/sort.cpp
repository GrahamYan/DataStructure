#include <bits/stdc++.h>
using namespace std;

inline void sort(int *a, int l, int r) {
	int i = l, j = r;
	int mid = a[i + j >> 1];
	do {
		while (a[i] < mid) ++i;
		while (a[j] > mid) --j;
		if (i <= j) {
			swap(a[i], a[j]);
			++i;
			--j;
		}
	} while (i <= j);
	if (i < r) sort(a, i, r);
	if (j > l) sort(a, l, j);
}

int main() {
	int n = 100;
	int a[111];
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	sort(a, 0, n - 1);
	for (int i = 0; i < n; ++i) {
		cout << a[i] << " ";	
	}
	cout << endl;
}  
