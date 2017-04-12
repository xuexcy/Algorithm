//
// 离散傅里叶变换（discrete fourier transform）
// Created by Xue,Chengyun on 2017/4/11.
//

#include <iostream>
#include <algorithm>
#include <complex>

using namespace std;

//struct complex {
//    double real;
//    double imag;
//};


vector<complex<double>> dft(const vector<double>& x, int N) {
    vector<std::complex<double>> X;
    for (int n = 0; n < N; ++n) {
        std::complex<double> sum(0.0, 0.0);
        for (int k = 0; k < x.size(); ++k) {
            complex<double> exponent = std::complex<double>(0.0, -2 * M_PI / N * n * k);
            sum += x[k] * exp(exponent);
        }
        X.push_back(sum);
    }
    return X;
}

vector<std::complex<double>> idft(const vector<complex<double>>& X, int M) {
    int N = X.size();
    vector<complex<double>> x;
    for (int k = 0; k < M; ++k) {
        std::complex<double> sum(0.0, 0.0);
        for (int n = 0; n < X.size(); ++n) {
            complex<double> exponent = std::complex<double>(0.0, 2 * M_PI / N * n * k);
            sum += X[n] * exp(exponent);
        }
        sum /= complex<double>(1.0 * N, 0.0);
        x.push_back(sum);
    }
    return x;
}

//vector<double> fft(const vector<double>& info, int N) {
//
//}

int main() {
    vector<double> x{1,1,1,1};
    int M = x.size();
    int N;

    // dft
    N = 8;
    vector<complex<double>> X1 = dft(x, N);
    for (int i = 0; i < X1.size(); ++i) {
        cout << X1[i] << endl;
    }

    // idft
    cout << endl;
    vector<complex<double>> x1 = idft(X1, M);
    for (int i = 0; i < x1.size(); ++i) {
        cout << x1[i] << endl;
    }

    // dtf
    cout << endl;
    N = 16;
    vector<complex<double>> X2 = dft(x, N);
    for (int i = 0; i < X2.size(); ++i) {
        cout << X2[i] << endl;
    }

    // idft
    cout << endl;
    vector<complex<double>> x2 = idft(X2, M);
    for (int i = 0; i < x2.size(); ++i) {
        cout << x2[i] << endl;
    }
    return 0;
}