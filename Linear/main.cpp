#include "linearalloc.hpp"

struct Foo {
    int x;
    int y;
    Foo(int a, int b) : x{a}, y{b} { std::cout << "C" << std::endl; }
    ~Foo() { std::cout << "D" << std::endl; }
};

int main() {
    LinearAlloc<Foo> allocator(100);
    Foo* arr = allocator.allocate(10 * sizeof(Foo));
    assert(arr != nullptr);
    for (int i = 0; i < 10; i++) {
        allocator.construct(&arr[i], i * i, i + 10);
    }
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i].x << ", " << arr[i].y << std::endl;
    }
    for (int i = 0; i < 10; i++) {
        allocator.destroy(&arr[i]);
    }
}   