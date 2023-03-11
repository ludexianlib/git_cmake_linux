#ifndef XLOG_H
#define XLOG_H

#ifdef xlog_EXPORTS
	#define XLOG_API __declspec(dllexport)
#else
	#define XLOG_API __declspec(dllimport)

#endif

#ifdef WIN32
class XLOG_API XLog
#else __linux__
class XLog
#endif
{
public:
	XLog();
};

#endif

