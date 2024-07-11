#pragma once

/*
 * 基类对象
 */
class RegisterObject
{
public:
	virtual ~RegisterObject() {}
	virtual bool execute(void* p) { return false; }
	virtual const char* objectName() { return "RegisterObject"; }
};