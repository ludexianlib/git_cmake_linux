#ifndef ADD_H
#define ADD_H

#ifdef WIN32
#ifdef Add_EXPORTS
	#define ADD_API __declspec(dllexport)
#else
	#define ADD_API __declspec(dllimport)
#endif
#else
	#define ADD_API
#endif

extern "C" ADD_API int sum(int x, int y);

#endif