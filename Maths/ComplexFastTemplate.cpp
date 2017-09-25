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

    T get_real() {
        return this->x;
    }

    T get_img() {
        return this->y;
    }

    Complex conj() {
        return Complex(this->x, -(this->y));
    }

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
        return Complex(this->x/num, this->x/num);
    }
};





int main() {

    return 0;
}
