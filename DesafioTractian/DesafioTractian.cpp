#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <fftw3.h>
#include <math.h>
using namespace std;

#define N 5000

/*void fft(double* in, fftw_complex* out, int sum)
{
	fftw_plan plan = fftw_plan_dft_r2c_1d(sum, in, out, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);
	fftw_cleanup();
}*/
void fft(double* in, double* out, int sum)
{
	fftw_plan plan = fftw_plan_r2r_1d(sum, in, out, FFTW_REDFT00, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);
	fftw_cleanup();
}

int main() {
	double* x;
	double* y;
	double* z;
	x = (double*)malloc(sizeof(double) * N);
	y = (double*)malloc(sizeof(double) * N);
	z = (double*)malloc(sizeof(double) * N);
	double* outx;
	double* outy;
	double* outz;
	outx = (double*)malloc(sizeof(double) * N);
	outy = (double*)malloc(sizeof(double) * N);
	outz = (double*)malloc(sizeof(double) * N);
	/*fftw_complex* outx;
	outx = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	fftw_complex* outy;
	outy = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	fftw_complex* outz;
	outz = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);*/
	ifstream myfile("1602245833-2715-NAO7856.txt");
	int sum = 0;
	if (myfile.is_open()) {
		std::string line;
		while (getline(myfile, line)) {
			std::stringstream ss(line);
			string sx, sy, sz;
			getline(ss, sx, ',');
			if (sx == "x") //exclui a primeira linha do arquivo .txt
				continue;
			getline(ss, sy, ',');
			getline(ss, sz, ',');
			x[sum] = stod(sx);
			y[sum] = stod(sy);
			z[sum] = stod(sz);
			sum++;
		}
		myfile.close();
	}
	fft(x, outx, sum);
	fft(y, outy, sum);
	fft(z, outz, sum);
	ofstream ofs("output.txt", ofstream::out);
	double freq = 0.368324125;
	/*for (int i = 1; i < 2069; i++) {
		ofs << sqrt((outx[i][0] * outx[i][0]) + (outx[i][1] * outx[i][1])) << ","
			<< sqrt((outy[i][0] * outy[i][0]) + (outy[i][1] * outy[i][1])) << "," 
			<< sqrt((outz[i][0] * outz[i][0]) + (outz[i][1] * outz[i][1])) << "," 
			<< freq << endl;
		freq += 0.736826270;
	}*/
	for (int i = 1; i < sum; i++) {
		ofs << sqrt((outx[i] * outx[i]) + (outx[i] * outx[i])) << ","
			<< sqrt((outy[i] * outy[i]) + (outy[i] * outy[i])) << ","
			<< sqrt((outz[i] * outz[i]) + (outz[i] * outz[i])) << ","
			<< freq << endl;
		freq += 0.368324125;
	}
	return 0;
}