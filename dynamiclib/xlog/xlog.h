#ifndef XLOG_H
#define XLOG_H

#ifdef WIN32
#ifdef xlog_EXPORTS
	#define XLOG_API __declspec(dllexport)
#else
	#define XLOG_API __declspec(dllimport)
#else
	#define XLOG_API
#endif

class XLOG_API XLog
{
public:
	XLog();
};

#endif

