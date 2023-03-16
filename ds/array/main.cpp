#include "SMatrix.h"

int main(int argc, char* argv[])
{
    int item[4][4] = {0, 1, 0, 0, 
                      1, 0, 0, 1, 
                      0, 0, 0, 0, 
                      0, 0, 1, 1};
    SMatrix(*item, 4);
    return 0;
}