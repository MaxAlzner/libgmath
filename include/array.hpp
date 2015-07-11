#ifndef ARRAY_H
#define ARRAY_H

#if !defined(Array)

template <typename T> class Array
{
public:

	Array()
	{
		this->_count = 0;
		this->_capacity = 0;
		this->_data = 0;
	}
	Array(const int length)
	{
		this->_count = 0;
		this->resize(length);
	}
	~Array()
	{
		this->clear();
	}

	const int add(const T& item)
	{
		if (this->_capacity < 1)
		{
			this->resize(1);
		}
		else if (this->_count >= this->_capacity)
		{
			this->resize(this->_capacity * 2);
		}

		this->_data[this->_count] = item;
		int index = this->_count;
		this->_count++;
		return index;
	}
	T& get(const int index)
	{
		if (this->_capacity < 1)
		{
			this->resize(index);
		}

		if (index >= this->_count)
		{
			this->_count = index + 1;
		}

		return this->_data[index % this->_capacity];
	}
	bool contains(const T& item)
	{
		if (this->_count > 0 && this->_capacity > 0)
		{
			for (int i = 0; i < this->_count; i++)
			{
				if (memcmp(this->_data + i, &item, sizeof(T)) == 0)
				{
					return true;
				}
			}
		}

		return false;
	}
	const int indexOf(const T& item)
	{
		if (this->_count > 0 && this->_capacity > 0)
		{
			for (int i = 0; i < this->_count; i++)
			{
				if (memcmp(this->_data + i, &item, sizeof(T)) == 0)
				{
					return i;
				}
			}
		}

		return -1;
	}
	void insert(const T& item, const int index)
	{
		if (index < 0)
		{
			return;
		}
		else if (index >= this->_capacity)
		{
			this->resize(index + 1);
		}

		this->_data[index] = item;
		if (index >= this->_count)
		{
			this->_count = index + 1;
		}
		else
		{
			this->_count++;
		}
	}
	void remove(const T& item)
	{
		int index = this->indexOf(item);
		if (index >= 0)
		{
			this->removeAt(index);
		}
	}
	void removeAt(const int index)
	{
		if (this->_count > 0 && this->_capacity > 0)
		{
			int k = index % this->_count;
			memset(this->_data + k, 0, sizeof(T));
			for (int i = k + 1; i < this->_count; i++)
			{
				this->_data[i - 1] = this->_data[i];
			}

			if (this->_count > 0)
			{
				this->_count--;
			}
		}
	}

	void clear()
	{
		this->resize(0);
	}
	void zero()
	{
		if (this->_capacity > 0 && this->_data != 0)
		{
			memset(this->_data, 0, sizeof(T) * this->_capacity);
			this->_count = 0;
		}
	}

	void resize(const int length)
	{
		this->_capacity = length;
		if (this->_capacity < 1)
		{
			if (this->_data == 0)
			{
				return;
			}

			delete[] this->_data;
			this->_data = 0;
			this->_count = 0;
		}
		else
		{
			T* clean = new T[this->_capacity];
			memset(clean, 0, sizeof(T) * this->_capacity);
			if (this->_count > this->_capacity)
			{
				this->_count = this->_capacity;
			}

			memcpy(clean, this->_data, sizeof(T) * this->_count);
			if (this->_data != 0)
			{
				delete[] this->_data;
			}

			this->_data = clean;
		}
	}

	const int count() const
	{
		return this->_count;
	}
	const int capacity() const
	{
		return this->_capacity;
	}
	bool inside(const int index) const
	{
		return index < this->_count && index >= 0;
	}

	operator T*() const
	{
		return this->_data;
	}
	T& operator[](const int index)
	{
		return this->get(index);
	}

private:

	int _count;
	int _capacity;
	T* _data;

};

#endif
#endif