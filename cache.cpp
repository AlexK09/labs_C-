

#include	<stdio.h>

#include	<stdlib.h> 
#include	<string.h> 
#include	<time.h> 
#include	<iostream> 
#include	<Windows.h> 
#include <chrono>
#include <vector>




using namespace std;

#define		T	char 
#define		MAX_S	0x1000000 
#define		L	101 
volatile T A[MAX_S];
int m_rand[0xFFFFFF];


void functionback() {
	for (size_t j = 0; j < 10; j++) {
		size_t N = (128 / 4) * pow(2, j) * 1024;
		int* A = new int[N];

		for (int k = N - 1; k > 0; k--) {
			A[k] = (k - 64) % N;
		}
		A[0] = N - 1;

		size_t f = 0;

		auto start = std::chrono::system_clock::now();


		for (size_t k = 0; k < 100000; k++) {
			f = A[f];
		}



		auto end = std::chrono::system_clock::now();

		auto res = end - start;
		cout << res.count() << "    " << N * 4 / 1024 << endl;

		delete[] A;

	}
}



void functionFront() {
	for (size_t j = 0; j < 10; j++) {
		size_t N = (128 / 4) * pow(2, j) * 1024;


		int* A = new int[N];

		for (size_t i = 0; i < N; i++) {
			A[i] = (i + 64) % N;

		}
		size_t f = 0;
		auto start = std::chrono::system_clock::now();
		for (size_t t = 0; t < 10000; t++) {


			f = A[f];

		}

		auto end = std::chrono::system_clock::now();

		auto res = end - start;
		cout << res.count() << "    " << N * 4 / 1024 << endl;

		delete[] A;
	}
}



void functionRandomZapolnenie() {

	LARGE_INTEGER freq; LARGE_INTEGER time1; 	LARGE_INTEGER time2;
	QueryPerformanceFrequency(&freq);

	memset((void*)A, 0, sizeof(A));

	srand(time(NULL));

	int v, M;
	register int i, j, k, m, x;

	for (size_t r = 0; r < 12; r++) {
		size_t k = (128 / 4) * pow(2, r) * 1024;
		M = k / L;

		//printf("%g\t", (k + M * 4) / (1024. * 1024));

		for (i = 0; i < M; i++) m_rand[i] = L * i;
		for (i = 0; i < M / 4; i++) {
			j = rand() % M;
			x = rand() % M;

			m = m_rand[j];
			m_rand[j] = m_rand[i];
			m_rand[i] = m;

		}

		if (k < 100 * 1024) j = 1024;
		else if (k < 300 * 1024) j = 128;
		else j = 32;

		auto start = chrono::system_clock::now();
		for (i = 0; i < j; i++) {

			for (m = 0; m < L; m++) {
				for (x = 0; x < M; x++) {
					v = A[m_rand[x] + m];
				}
			}

		}


		auto end = std::chrono::system_clock::now();

		auto res = end - start;
		cout << res.count() << "    " << k * 4 / 1024 << endl;

		//	if (k > 100 * 1024)	k += k / 16;
			//else			k += 4 * 1024;
	}

}





int main() {
	srand(time(NULL));
	//size_t L = pow(2, 2) * 1024;


	functionFront();
	cout << endl;
	functionback();
	cout << endl;
	functionRandomZapolnenie();



	return 0;
}
