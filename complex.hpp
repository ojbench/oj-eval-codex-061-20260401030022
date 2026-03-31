#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace sjtu {

class divided_by_zero final : public std::exception {
public:
  divided_by_zero() = default;
  ~divided_by_zero() = default;
  const char *what() const noexcept override {
    return "complex divided by zero!";
  }
};

// 用于判断浮点数的符号.
inline int sign(double x) {
  const double eps = 1e-6;
  return (x > eps) - (x < -eps);
}

class complex {
private:
  double a, b; // a + bi

public:
  // 构造函数
  complex() : a(0.0), b(0.0) {}
  explicit complex(double ra) : a(ra), b(0.0) {}
  complex(double ra, double ib) : a(ra), b(ib) {}

  // 访问实部与虚部
  double &real() { return a; }
  double &imag() { return b; }

  // 单目运算
  complex operator-() const { return complex(-a, -b); }
  complex operator~() const { return complex(a, -b); }

  // 四则运算（返回新对象）
  complex operator+(const complex &rhs) const {
    return complex(a + rhs.a, b + rhs.b);
  }
  complex operator-(const complex &rhs) const {
    return complex(a - rhs.a, b - rhs.b);
  }
  complex operator*(const complex &rhs) const {
    return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
  }
  complex operator/(const complex &rhs) const {
    if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
      throw divided_by_zero();
    }
    const double den = rhs.a * rhs.a + rhs.b * rhs.b;
    return complex((a * rhs.a + b * rhs.b) / den,
                   (b * rhs.a - a * rhs.b) / den);
  }

  // 复合赋值运算
  complex &operator+=(const complex &rhs) {
    a += rhs.a;
    b += rhs.b;
    return *this;
    }
  complex &operator-=(const complex &rhs) {
    a -= rhs.a;
    b -= rhs.b;
    return *this;
  }
  complex &operator*=(const complex &rhs) {
    const double na = a * rhs.a - b * rhs.b;
    const double nb = a * rhs.b + b * rhs.a;
    a = na;
    b = nb;
    return *this;
  }
  complex &operator/=(const complex &rhs) {
    if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
      throw divided_by_zero();
    }
    const double den = rhs.a * rhs.a + rhs.b * rhs.b;
    const double na = (a * rhs.a + b * rhs.b) / den;
    const double nb = (b * rhs.a - a * rhs.b) / den;
    a = na;
    b = nb;
    return *this;
  }

  // 比较
  bool operator==(const complex &rhs) const {
    return std::fabs(a - rhs.a) < 1e-6 && std::fabs(b - rhs.b) < 1e-6;
  }

  // 转换到 bool
  explicit operator bool() const { return !(sign(a) == 0 && sign(b) == 0); }

  // 输出
  friend std::ostream &operator<<(std::ostream &os, const complex &x) {
    // 近零按 0 处理
    const double ra = (sign(x.a) == 0 ? 0.0 : x.a);
    const double ib = (sign(x.b) == 0 ? 0.0 : x.b);
    const char imag_sign = (sign(ib) < 0 ? '-' : '+');
    const double imag_abs = std::fabs(ib);

    os.setf(std::ios::fixed);
    os << std::setprecision(6) << ra;
    os << imag_sign << std::setprecision(6) << imag_abs << 'i';
    return os;
  }
};

} // namespace sjtu

#endif // SJTU_COMPLEX_HPP

