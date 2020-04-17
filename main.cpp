#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <chrono>
#include <ctime>
using namespace std;

typedef vector<vector<int>> matv;

void multmat3(matv &a, matv &b, matv &rpta){

	int fA = a.size() , cA= a[0].size();
	int fB = b.size(), cB = b[0].size();

	//if (cA != fB) return;

	//cout << (rpta).size() << "-" << (rpta)[0].size() << endl;

	for (int i = 0; i < fA; i++) {
		for (int j = 0; j < cB; j++) {
			for (int k = 0; k < cA; k++) {
				rpta[i][j] = rpta[i][j] + a[i][k] * b[k][j];
			}
		}
	}

}


void multmat6(matv& a, matv& b, matv& rpta) {

	int fA = a.size(), cA = a[0].size();
	int fB = b.size(), cB = b[0].size();

	int tam_bloq = fA / 10;

	int MAX = fA;

	for (int x = 0; x < MAX; x += tam_bloq)
	{
		for (int y = 0; y < MAX; y += tam_bloq)
		{
			for (int z = 0; z < MAX; z += tam_bloq)
			{
				for (int i = x; i < x + tam_bloq; i++)
				{
					for (int j = y; j < y + tam_bloq; j++)
					{
						for (int k = z; k < z + tam_bloq; k++)
						{
							rpta[i][j] += a[i][k] * b[k][j];
						}
					}
				}
			}
		}
	}
}

void llenar(matv &m) {

	srand(time(NULL));

	for (int i = 0; i < m.size(); i++) {
		
		for (int j = 0; j < m[0].size(); j++) {
			m[i][j]=(rand() % 100);
		}
	}
}

void print(matv& m) {
	cout << m.size() << "-" << m[0].size() << endl;
	for (int i = 0; i < m.size(); i++) {

		for (int j = 0; j < m[0].size(); j++) {
			cout << m[i][j] << "-";
		}

		cout << endl;
	}
}


int main() {
	int size = 100;
	matv p = matv(size, vector<int>(size, 0));
	matv q = matv(size, vector<int>(size, 0));


	llenar(p);
	llenar(q);

	//print(p);
	//print(q);

	cout << "1" << endl;
	matv rpta = matv(size, vector<int>(size, 0));

	using namespace std::chrono;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	multmat3(p,q,rpta);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Tiempo" << time_span.count() << " segundos." << endl;

	//print(rpta);
	
	matv rpta2 = matv(size, vector<int>(size, 0));

	t1 = high_resolution_clock::now();

	multmat6(p, q, rpta2);

	t2 = high_resolution_clock::now();

	time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Tiempo" << time_span.count() << " segundos." << endl;

	//print(rpta2);

	


	system("pause");
	return 0;
}