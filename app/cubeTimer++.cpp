#include "fmt/format.h"
#include <iostream>
void sayHello();
int main() {
    try{
        fmt::print("Hello World!\n");
        sayHello();
    } catch (...) {
        std::cout << "An exception occurred" <<std::endl;
    }
    return 0;
}
