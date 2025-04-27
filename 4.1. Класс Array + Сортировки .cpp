#include <iostream>
#include <ctime>

using namespace std;


struct ST{
	string name;
	float time;
};


class Array {
	int* a;
	int n;

	public:
		Array(int len = 1, int t = 1, int d = 10) {
			n = len;
			a = new int[n];
			
			if (t == 1) {

				for(int i = 0; i < n; i++) a[i] = rand() % d;
			}	
			else if (t == 2){ 
				a[0] = rand() %d;
				for(int i = 1; i < n; i++) a[i] = a[i-1]+ rand() %d;
			}
			else if (t == 3){ 
				//int value = n;
				a[n-1] = rand() %d;
				for(int i = n-1 ; i>0 ; i--) {
					a[i-1] = a[i] + rand() %d;
					//value--;
				}
			}
		}

		Array(int* values, int size) {
			n = size;
			a = new int[n];
			for(int i = 0; i < n; i++) a[i] = values[i];
		}

		Array(const Array& other) {
			n = other.n; 
			a = new int[n];
			for(int i = 0; i < n; i++) {
			    a[i] = other.a[i];
			}
		}

		~Array() {
			delete [] a;
		}
		
		Array& operator=(const Array& other) {
			if (this != &other) { 
				delete [] a;
				n = other.n;
				a = new int[n];
				for(int i = 0; i < n; i++) {
					a[i] = other.a[i];
				}
			}
			return *this;
		}


		int& operator[](int index) {
			if (index>=0 && index<n) return a[index]; 
			cout << "index net";
			exit(0);
		}

	    
		bool Test() {
			for(int i = 0; i < n-1; i++)
				if(a[i] > a[i+1]) return false; 
			return true;
		}


		bool operator==(const Array& other) {
			
			/*
			if (n != other.n) return false;
			int bigest = a[0];
			for(int i = 0; i < n; i++) if (a[i]>bigest) bigest = a[i];
			
			int x[bigest+1] = {0};
			
			for(int i = 0; i < n; i++) x[a[i]]++;
			for(int i = 0; i < n; i++){ 
				if (other.a[i]>bigest) return false;
				else x[other.a[i]]--;
			}
			for(int i = 0; i < n; i++) if (x[i] != 0) return false;
			return true;
			*/
			
			bool flagArr [n] = {0}, flag;
			for (int i=0; i<n; i++){
				flag = false;
				for (int j=0; j<n && !(flag); j++){
					if (a[i] == a[j] && !(flagArr[j])) flagArr[j] = flag = true;
				}
				if (!(flag)) return false;
			}
			return true;
			
		}


		friend istream& operator>>(istream& is, Array& arr) {
			cout << "length: ";
			cin >> arr.n;
			delete [] arr.a;
			arr.a = new int [arr.n];
			cout << "arr: ";
			for(int i = 0; i < arr.n; i++) is >> arr.a[i];
			return is;
		}


		friend ostream& operator<<(ostream& os, const Array& arr) {
			for(int i = 0; i < arr.n; i++) os << arr.a[i] << " ";
			return os;
		}

	    
		// Shell sort:
		void Shell_sort() {
			int h = n/2;

			while(h > 0) {
				for(int i = h; i < n; i++) {
					int j = i;
					int temp = a[i];
				    
					while(j >= h && a[j-h] > temp) {
						a[j] = a[j-h];
						j -= h;
					}
				    
					a[j] = temp;
				}

				h = h/2;
			}
		}


		// Heap sort:
		void shiftDown(int i, int size) {
			int j = 2 * i + 1, x = a[i], f = 1;
			while (j < size && f) {
				if (j + 1 < size)
					if (a[j + 1] > a[j]) j++;
				if (a[j] > x) {
					a[i] = a[j];
					i = j;
					j = 2 * i + 1;
				}
				else f = 0;
			}
			a[i] = x;
		}
		void Heapsort() {
			// b نقوم ببناء الهرم
			for (int i = n / 2 - 1; i >= 0; i--)
				shiftDown(i, n);
			// sort 
			for (int i = n - 1; i > 0; i--) {
				swap(a[0], a[i]);
				shiftDown(0, i);
			}
		}


		// BIT SORT
		void bitSort() {bitSort_alg(0, n - 1, 31);}
		void bitSort_alg(int l, int r, int k) {
			if (l >= r || k < 0) return;

			int i = l, j = r, tmp;
			int mask = 1 << k; // Маска для k-ого бита

			while (i <= j) {
				while (i <= j && !(a[i] & mask)) i++;
				while (i <= j && (a[j] & mask)) j--;
				if (i < j) {
					//swap(a[i], a[j]);
					tmp = a[i];
					a[i] = a[j];
					a[j] = tmp;
					i++;
					j--;
				}
			}

			bitSort_alg(l, j, k - 1);
			bitSort_alg(i, r, k - 1);
		}
		

		// quickSort
		void quickSort() {quickSort_alg(0, n - 1);}
		void quickSort_alg(int l, int r) {
			if (l >= r) return;

			int i = l, j = r, tmp;
			int pivot = a[(l + r) / 2]; // выбор опорного элемента

			while (i <= j) {
				while (a[i] < pivot) i++;
				while (a[j] > pivot) j--;
				if (i <= j) {
					//swap(a[i], a[j]);
					tmp = a[i];
					a[i] = a[j];
					a[j] = tmp;
					i++;
					j--;
				}
			}

			quickSort_alg(l, j); // рекурсивная сортировка левой части
			quickSort_alg(i, r); // рекурсивная сортировка правой части
		}
	
	
};





int main() {
	srand(time(NULL));
	// Test default constructor
	//Array a1; 
	//cout << "Default Array: " << a1 << endl;

	// Test parameterized constructor 
	//Array a2(5, 2, 10); 
	//cout << "Ascending order (a2): " << a2 << endl;

	//Array a3(20, 3, 10);
	//cout << "Descending order (a3): " << a3 << endl;

	// Test HEAP SORT
	//a3.Heapsort();
	//cout << "Heapsort: " << a3 << endl;
	
	// SHELL SORT
	//a3.Shell_sort();
	//cout << "Shell sort: " << a3 << endl;
	
	// Test BIT SORT
	//a3.bitSort();
	//cout << "bitSort: " << a3 << endl;
	
	// Test quickSort
	//a3.quickSort();
	//cout << "quickSort: " << a3 << endl;
	
	// Test copy constructor
	//Array a4 = a3;
	//cout << "a4 Copy of a3: " << a4 << endl;

	//Array a5(10); 
	//a5 = a2;
	//cout << "a5 : " << a5 << endl;

	// Test array access
	//a5[0] = 100;
	//cout << "New a5: " << a5 << endl;

	// Test equality operator 
	//Array a6 = a5;
	//if(a5 == a6) cout << "a5 and a6 are equal" << endl;

	// Test ordering test
	//if(a2.Test()) cout << "a2 is sorted in ascending order" << endl; 

	// Test input/output
	//cin >> a2;
	//cout << "User entered a2: " << a2 << endl;

	Array a1(100000000, 1, 100000);
	Array a2 = a1;
	Array a3 = a1;
	Array a4 = a1;
	double start, end;
	
	//cout << "random arr: " << a1 << endl;
	
	struct ST arr[4];
	// Heapsort:
		start = clock();
		//a1.Heapsort();
		end = clock();
		if (a1.Test()) cout << "a1 sorted using Heapsort \t time = " << (end - start) / CLOCKS_PER_SEC << endl;
		arr[0].name = "heapsort";
		arr[0].time = 0;
	
	// Shell_sort:
		start = clock();
		//a2.Shell_sort();
		end = clock();
		if (a2.Test()) cout << "a2 sorted using Shellsrt \t time = " << (end - start) / CLOCKS_PER_SEC << endl;
		arr[1].name = "Shell_sort";
		arr[1].time = 0;

	// quickSort:
		start = clock();
		a3.quickSort();
		end = clock();
		if (a3.Test()) cout << "a3 sorted using quicksrt \t time = " << (end - start) / CLOCKS_PER_SEC << endl;
		arr[2].name = "quickSort";
		arr[2].time = (end - start) / CLOCKS_PER_SEC;

	// bitSort:
		start = clock();
		a4.bitSort();
		end = clock();
		if (a4.Test()) cout << "a4 sorted using bitSort  \t time = " << (end - start) / CLOCKS_PER_SEC << endl;
		arr[3].name = "bitSort";
		arr[3].time = (end - start) / CLOCKS_PER_SEC;
	

	
	int h = 2;
	while(h > 0) {
		for(int i = h; i < 4; i++) {
			int j = i;
			struct ST temp = arr[i];
		    
			while(j >= h && arr[j-h].time > temp.time) {
				arr[j] = arr[j-h];
				j -= h;
			}
		    
			arr[j] = temp;
		}

		h = h/2;
	}
	for (int i=0; i<4; i++) cout << arr[i].name << " -> ";
	//if (a1 == a2 && a2 == a3 && a3 == a4) cout << "a1 == a2 == a3 == a4" << endl;
	
	return 0;
}
