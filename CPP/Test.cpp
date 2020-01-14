#include <iostream>

int main() {
    int x = 5;
    int y = 0;
    x > 5 ? 2 : (y = 5, x = y + 8);
    std::cout << y << ',' << x << '\n';
    return 0;
}