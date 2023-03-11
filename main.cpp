#include <iostream>

int sub(int x, int y)
{
    return x - y;
}

int main(int argc, char* argv[])
{
    std::cout << "test!" << std::endl;
    std::cout << "test!" << std::endl;
    std::cout << "test!" << std::endl;
    std::cout << "sub: " << sub(9, 19) << std::endl;
    std::cout << "sub: " << sub(19, 44) << std::endl;
    
    return 0;
}
