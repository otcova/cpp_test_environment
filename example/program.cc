#include <iostream>
using namespace std;

int main() {
	cout.setf(ios::fixed);
	cout.precision(4);
	
	int len;
	cin >> len;
	
	for (int i = 0; i < len; ++i) {
		int m;
		cin >> m;
		
		double min, max, sum;
		cin >> min;
		max = min;
		sum = min;
		
		for (int j = 1; j < m; ++j) {
			double n;
			cin >> n;
			if (n < min) min = n;
			if (n > max) max = n;
			sum += n;
		}
		
		cout << min << ' ' << max << ' ' << sum/m << endl;
	}
}