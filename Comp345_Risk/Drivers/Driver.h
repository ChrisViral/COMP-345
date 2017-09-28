#pragma once

class Driver
{
public:
	Driver() { }
	virtual ~Driver() = 0;
	virtual void run() = 0;
};