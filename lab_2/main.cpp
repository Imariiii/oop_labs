#include "include/decarray.h"

int main() {
    Decimal a("123");
    Decimal b("456243");
    Decimal c = a;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;

    std::cout << std::endl;


    std::cout << "a + c = " << a + c << std::endl;
    std::cout << "b - a = " << b - a << std::endl;

    std::cout << std::endl;

    std::cout << "b > a = " << (b > a) << std::endl;
    std::cout << "b < a = " << (b < a) << std::endl;
    std::cout << "a <= b = " << (a <= b) << std::endl;
    std::cout << "b >= a = " << (b >= a) << std::endl;
    std::cout << "c == a = " << (c == a) << std::endl;
    std::cout << "c != a = " << (c != a) << std::endl;

    std::cout << std::endl;

    ++a;
    std::cout << "++a = " << a << std::endl;
    --a;
    std::cout << "--a = " << a << std::endl;
    a++;
    std::cout << "++a = " << a << std::endl;
    a--;
    std::cout << "++a = " << a << std::endl;

    std::cout << std::endl;

    a.print();
    b.print();
    c.print();

    return 0;
}