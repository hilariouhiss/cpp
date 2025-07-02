#include <iostream>
int main(int, char**)
{
    int        a{10};
    // 指向常量的指针
    const int* p1 = &a;  // 等价 int const* ptr;
    // *p1 = 100; 报错
    // 常量指针
    int* const p2 = &a;
    *p2 = 100;
    int              b{1};
    // p2 = &b; 报错

    // constexpr if 语句
    constexpr double gravity{9.8};

    if constexpr (gravity == 9.8) {
        std::cout << "gravity is normal\n";
    }
}
