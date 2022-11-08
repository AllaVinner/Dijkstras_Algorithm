#include <iostream>

class A
{
    public:
        A(){};
        int f();
};

int A::f()
{
    int* a = new int[5];
    for (int i=0; i<5; i++)
        a[i] = rand() %100;
    std::cout << a[0] << a[1] << a[2] << a[3] << a[4] << std::endl;
    return 3;
}

int main(void)
{
    std::cout << "HELO WORLS" << std::endl;
    int* arr = new int[5];
    A a = A();
    std::cout << "HELO WORLD 22" << std::endl;
    std::cout << "fun " << a.f() << std::endl;
    return 0;
}