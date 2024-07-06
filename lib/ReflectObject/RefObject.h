#pragma once

/*
 * 基类对象
 */
class RefObject
{
public:
	virtual ~RefObject() {}
	virtual const char* objectName() = 0;
};