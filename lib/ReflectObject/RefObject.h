#pragma once

class RefObject
{
public:
	virtual ~RefObject() {}
	virtual const char* objectName() = 0;
};