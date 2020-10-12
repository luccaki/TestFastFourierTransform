#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <fftw3.h>
using namespace std;

int main() {
	vector<float> x;
	vector<float> y;
	vector<float> z;
	ifstream myfile("1602245833-2715-NAO7856.txt");
	if (myfile.is_open()) {
		std::string line;
		while (std::getline(myfile, line)) {

			std::stringstream ss(line);
			string sx, sy, sz;
			getline(ss, sx, ',');
			if (sx == "x") //exclui a primeira linha do arquivo .txt
				continue;
			getline(ss, sy, ',');
			getline(ss, sz, ',');
			x.push_back(stof(sx));
			y.push_back(stof(sy));
			z.push_back(stof(sz));
		}
		myfile.close();

	}
	int N;
	fftw_complex* in, * out;
	fftw_plan p;
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p); /* repeat as needed */
	fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);

	return 0;
}