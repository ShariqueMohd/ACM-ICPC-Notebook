#include <bits/stdc++.h>

#define lli long long int
#define ld long double
using namespace std;

const int MAX = 263005;

template<typename T>
class Complex {
private:
    T x, y;
public:
    Complex() : x(0.0), y(0.0) {}
    Complex(T a) : x(a), y(0.0) {}
    Complex(T a, T b) : x(a), y(b) {}

    T get_real() {  return this->x; }
    T get_img() {   return this->y; }
    Complex conj() {    return Complex(this->x, -(this->y));}

    Complex operator = (const Complex &a) {
        this->x = a.x; this->y = a.y;
        return *this;
    }
    Complex operator + (const Complex &b) {
        return Complex(this->x + b.x, this->y + b.y);
    }
    Complex operator - (const Complex &b) {
        return Complex(this->x - b.x, this->y - b.y);
    }
    Complex operator * (const Complex &b) {
        return Complex( (this->x * b.x - this->y * b.y), (this->y * b.x + this->x * b.y) );
    }
    Complex operator / (const Complex &b) {
        Complex temp(b.x, -b.y);
        Complex res = (*this) * temp;
        return res / (b.x*b.x + b.y*b.y);
    }
    Complex operator * (const T &num) {
        return Complex(this->x*num, this->y*num);
    }
    Complex operator / (const T &num) {
        return Complex(this->x/num, this->y/num);
    }
};

// T = int/long long as per polynomial coefficients
// S = double/long double as per precision required
template<typename T, typename S>
struct FFT {
    S PI;
    int n, L, *rev, Last;
    Complex<S> ONE, ZERO;
    Complex<S> *omega_powers;

    FFT() {
        PI = acos(-1.0);
        ONE = Complex<S>(1.0, 0.0);
        ZERO = Complex<S>(0.0, 0.0);
        Last = -1;
        int req = 1 << (32 - __builtin_clz(MAX));
        rev = new int[req];
        omega_powers = new Complex<S>[req];
    }

    ~FFT() {
        delete rev;
        delete omega_powers;
    }

    void ReverseBits() {
        if(n != Last) {
            for(int i=1,j=0; i<n; i++) {
                int bit = n>>1;
                for(; j>=bit; bit>>=1)
                    j -= bit;
                j += bit;
                rev[i] = j;
            }
        }
    }

    void DFT(vector<Complex<S>> &A, bool inverse=false) {
        for(int i=0; i<n; i++) {
            if(rev[i]>i)
                swap(A[i], A[rev[i]]);
        }
        for(int s=1; s<=L; s++) {
            int m = 1<<s;
            int half = m>>1;
            Complex<S> wm(cos(2.0*PI/m), sin(2.0*PI/m));
            if(inverse) {
                wm = ONE / wm;
            }
            omega_powers[0] = ONE;
            for(int k=1; k<half; k++) {
                omega_powers[k] = omega_powers[k-1] * wm;
            }
            for(int k=0; k<n; k+=m) {
                for(int j=0; j<half; j++) {
                    Complex<S> t = omega_powers[j] * A[k+j+half];
                    Complex<S> u = A[k+j];
                    A[k+j] = u + t;
                    A[k+j+half] = u - t;
                }
            }
        }
        if(inverse) {
            for(int i=0; i<n; i++) {
                A[i] = A[i] / n;
            }
        }
    }

    vector<T> Multiply(const vector<T> &a, const vector<T> &b) {
        L = 0;
        int sa = a.size(), sb = b.size(), sc = sa + sb - 1;
        while((1<<L)<sc)
            L += 1;
        n = 1<<L;
        ReverseBits();
        Last = n;
        vector<Complex<S>> aa(n,ZERO), bb(n, ZERO), cc;
        for(int i=0; i<sa; i++) {
            aa[i] = Complex<S>(a[i], 0);
        }
        for(int i=0; i<sb; i++) {
            bb[i] = Complex<S>(b[i], 0);
        }
        DFT(aa, false); DFT(bb,false);
        for(int i=0; i<n; i++) {
            cc.push_back(aa[i]*bb[i]);
        }
        DFT(cc, true);
        vector<T> ans(sc);
        for(int i=0; i<sc; i++) {
            ans[i] = cc[i].get_real() + 0.5;
        }
        return ans;
    }

    vector<T> Multiply(const vector<T> &a) {
        L = 0;
        int sa = a.size(), sc = sa + sa - 1;
        while((1<<L)<sc)
            L += 1;
        n = 1<<L;
        ReverseBits();
        Last = n;
        vector<Complex<S>> aa(n, ZERO), cc;
        for(int i=0; i<sa; i++) {
            aa[i] = Complex<S>(a[i],0);
        }
        DFT(aa, false);
        for(int i=0; i<n; i++) {
            cc.push_back(aa[i]*aa[i]);
        }
        DFT(cc, true);
        vector<T> ans(sc);
        for(int i=0;i<sc;i++) {
            ans[i] = cc[i].get_real() + 0.5;
        }
        return ans;
    }


};

// Check for  ans[i] = cc[i].get_real() + 0.5;
// in both the Multiply functions

int main() {


    return 0;
}
