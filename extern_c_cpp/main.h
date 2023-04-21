
#ifndef MAIN_H_
#define MAIN_H_

#include "wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void callback(int x);

void* InitWrapperPtr(const char* str);
const char* GetWrapperData(void* ptr);
void DeleteWrapperPtr(void* ptr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MAIN_H_
