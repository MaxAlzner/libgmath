#ifndef DELEGATE_H
#define DELEGATE_H

#include <list.hpp>

#if defined(_WIN32)
#include <Windows.h>
#endif

class Delegate
{
public:

	typedef unsigned int(_stdcall *funcType)(void* data);

	Delegate() : _data(0), _error(0) {}
	~Delegate() {}

	void call()
	{
		for (List<funcType>::Iterator i = this->_functions.iterator(); i.inside(); i.next())
		{
			funcType func = i.current();
			if (func != 0)
			{
				this->_error = func(this->_data);
				if (this->_error != 0)
				{
					break;
				}
			}
		}
	}

	void add(const funcType func)
	{
		*this += func;
	}
	void remove(const funcType func)
	{
		*this -= func;
	}

	void setData(void* data)
	{
		this->_data = data;
	}

	void clear()
	{
		this->_functions.clear();
	}

	const unsigned int lastError() const
	{
		return this->_error;
	}

	Delegate operator+(const Delegate& d)
	{
		Delegate result;
		for (List<funcType>::Iterator i = this->_functions.iterator(); i.inside(); i.next())
		{
			result += i.current();
		}

		for (List<funcType>::Iterator i = d._functions.iterator(); i.inside(); i.next())
		{
			result += i.current();
		}

		return result;
	}
	Delegate operator-(const Delegate& d)
	{
		Delegate result;
		for (List<funcType>::Iterator i = this->_functions.iterator(); i.inside(); i.next())
		{
			result += i.current();
		}
		for (List<funcType>::Iterator i = d._functions.iterator(); i.inside(); i.next())
		{
			result -= i.current();
		}
		return result;
	}
	void operator+=(const funcType func)
	{
		if (func != 0)
		{
			this->_functions.add(func);
		}
	}
	void operator-=(const funcType func)
	{
		if (func != 0)
		{
			this->_functions.remove(func);
		}
	}
	const funcType operator[](const int index)
	{
		return this->_functions[index];
	}

protected:

	List<funcType> _functions;
	void* _data;
	unsigned int _error;

};

class Thread
{
public:

#if defined(_WINDOWS_)
	typedef HANDLE threadHandle;
#else
	typedef __int64 threadHandle;
#endif

	Thread() :
		_finished(false),
		_handle(0) {}
	~Thread() {}

	virtual void start()
	{
		if (this->_handle != 0)
		{
			this->abort();
		}

#if defined(_WINDOWS_)
		LPTHREAD_START_ROUTINE start = Thread::_procedure;
		LPVOID parameter = (LPVOID)&this->callstack;
		this->_handle = CreateThread(0, 0, start, parameter, 0, 0);
#endif
	}
	virtual void abort()
	{
		if (this->_handle != 0)
		{
#if defined(_WINDOWS_)
			TerminateThread(this->_handle, 0);
#endif
		}
	}

	virtual bool finished() const
	{
		if (this->_handle != 0)
		{
#if defined(_WINDOWS_)
			DWORD state = WaitForSingleObject(this->_handle, 0);
			return state == WAIT_OBJECT_0;
#endif
		}

		return false;
	}

	Delegate callstack;

protected:

	static unsigned long _stdcall _procedure(void* parameter)
	{
		if (parameter != 0)
		{
			Delegate* callstack = (Delegate*)parameter;
			if (callstack != 0)
			{
				callstack->call();
				return callstack->lastError();
			}
		}

		return -1;
	}

	bool _finished;
	threadHandle _handle;

};

#endif