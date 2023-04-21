#include "main.h"
#include <stdio.h>

int main()
{
    // extern "C" 接口
    callback(30);

    // cpp 封装类指针接口
    void* wrapperPtr = InitWrapperPtr("wrapper.");
    const char* cStr = GetWrapperData(wrapperPtr);
    printf("data: %s\n", cStr);
    DeleteWrapperPtr(wrapperPtr);

    return 0;
}