#include <iostream>
#include <iomanip>
#include <string>
#include "complex.hpp"

using sjtu::complex;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  if (!(std::cin >> q)) {
    return 0;
  }
  complex cur; // default 0
  for (int i = 0; i < q; ++i) {
    std::string op;
    std::cin >> op;
    if (op == "set") {
      double a, b;
      std::cin >> a >> b;
      cur = complex(a, b);
    } else if (op == "add") {
      double a, b;
      std::cin >> a >> b;
      cur += complex(a, b);
    } else if (op == "sub") {
      double a, b;
      std::cin >> a >> b;
      cur -= complex(a, b);
    } else if (op == "mul") {
      double a, b;
      std::cin >> a >> b;
      cur *= complex(a, b);
    } else if (op == "div") {
      double a, b;
      std::cin >> a >> b;
      try {
        cur /= complex(a, b);
      } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
      }
    } else if (op == "neg") {
      cur = -cur;
    } else if (op == "conj") {
      cur = ~cur;
    } else if (op == "eq") {
      double a, b;
      std::cin >> a >> b;
      std::cout << int(cur == complex(a, b)) << '\n';
    } else if (op == "bool") {
      std::cout << (cur ? 1 : 0) << '\n';
    } else if (op == "print") {
      std::cout << cur << '\n';
    } else if (op == "real") {
      std::cout.setf(std::ios::fixed);
      std::cout << std::setprecision(6) << cur.real() << '\n';
    } else if (op == "imag") {
      std::cout.setf(std::ios::fixed);
      std::cout << std::setprecision(6) << cur.imag() << '\n';
    }
  }
  return 0;
}
