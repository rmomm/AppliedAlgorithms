#include <iostream>
#include <list>
#include <algorithm>
#include <chrono>
#include <random>


using namespace std;
using namespace std::chrono;

class Set {
private:
	list<int> elements;

public:
	void Insert(int element) {
		if (!Search(element)) {
			elements.push_back(element);
		}
	}

	void Delete(int element) {
		if (Search(element)) {
			elements.remove(element);
		}
	}

	bool Search(int element) const {
		for (const int& el : elements) {
			if (el == element) {
				return true;
			}
		}
		return false;
	}

	void Clear() {
		elements.clear();
	}

	Set Union(const Set& other) const {
		Set result = *this;
		for (int element : other.elements) {
			result.Insert(element);
		}
		return result;
	}

	Set Intersection(const Set& other) const {
		Set result;
		for (int element : elements) {
			if (other.Search(element)) {
				result.Insert(element);
			}
		}
		return result;
	}

	Set SetDifference(const Set& other) const {
		Set result;
		for (int element : elements) {
			if (!other.Search(element)) {
				result.Insert(element);
			}
		}
		return result;
	}

	Set SymDifference(const Set& other) const {
		Set result = this->SetDifference(other);
		Set otherDiff = other.SetDifference(*this);
		return result.Union(otherDiff);
	}

	bool isSubset(const Set& other) const {
		for (int element : elements) {
			if (!other.Search(element)) {
				return false;
			}
		}
		return true;
	}

	void print() const {
		cout << "{";
		for (int element : elements) {
			cout << element << " ";
		}
		cout << "}";
	}

	int Size() const {
		return elements.size();
	}

	list<int> GetElements() const {
		return elements;
	}

	void generateRandomElements(int count, int min, int max) {
		srand(static_cast<unsigned>(time(0)));

		while (elements.size() < count) {
			int random_value = min + rand() % (max - min + 1);
			Insert(random_value);
		}
	}

};


double MeasureSearchTime(const Set& s, int element, int trials = 1000) {
	auto start = high_resolution_clock::now();
	for (int i = 0; i < trials; ++i) {
		s.Search(element);
	}
	auto end = high_resolution_clock::now();
	return duration<double, micro>(end - start).count() / trials;
}

double MeasureUnionTime(const Set& a, const Set& b, int trials = 1000) {
	auto start = high_resolution_clock::now();
	for (int i = 0; i < trials; ++i) {
		Set c = a.Union(b);
	}
	auto end = high_resolution_clock::now();
	return duration<double, micro>(end - start).count() / trials;
}


int main() {

	Set A, B;
	A.generateRandomElements(8, 0, 30);
	B.generateRandomElements(10, 0, 50);

	cout << "Set A: "; A.print(); cout << endl;
	cout << "Set B: "; B.print(); cout << endl;


	A.Insert(9);
	cout << "After Insert 9 into A: "; A.print(); cout << endl;


	A.Delete(9);
	cout << "After Delete 9 from A: "; A.print(); cout << endl;


	A.Insert(9);
	cout << "After Insert 9 into A: "; A.print(); cout << endl;


	cout << "Search 9 in A: " << (A.Search(9) ? "Found" : "Not Found") << endl;



	Set unionSet = A.Union(B);
	cout << "Union: "; unionSet.print(); cout << endl;


	Set intersectionSet = A.Intersection(B);
	cout << "Intersection: "; intersectionSet.print(); cout << endl;


	Set differenceSet = A.SetDifference(B);
	cout << "Difference: "; differenceSet.print(); cout << endl;


	Set symDiffSet = A.SymDifference(B);
	cout << "SymDifference: "; symDiffSet.print(); cout << endl;


	bool isSubset = A.isSubset(unionSet);
	cout << "A is subset of Union(A,B): " << (isSubset ? "Yes" : "No") << endl;



	cout << "---------------------------\n";




	vector<int> sizes = { 100, 250, 500, 750, 1000};

	for (int n : sizes) {
		Set D;
		D.generateRandomElements(n, 0, 1000); 

		int presentElement = *D.GetElements().begin();
		int absentElement = -1;

		
		double searchPresentTime = MeasureSearchTime(D, presentElement, 1000);
		
		double searchAbsentTime = MeasureSearchTime(D, absentElement, 1000);

		Set F;
		F.generateRandomElements(n, 0, 1000);  

		double unionTime = MeasureUnionTime(D, F, 1000);

		cout << "Size: " << n << "\n";
		cout << "SEARCH (existing): " << searchPresentTime << " microseconds\n";
		cout << "SEARCH (non-existing): " << searchAbsentTime << " microseconds\n";
		cout << "UNION: " << unionTime << " microseconds\n";
		cout << "---------------------------\n";
	}

	return 0;
}