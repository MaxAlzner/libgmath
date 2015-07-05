#ifndef MAP_H
#define MAP_H

#if !defined(Map)

template <typename T> class Map
{
public:

	Map() :
		_width(0),
		_height(0),
		_depth(0),
		_size(0),
		_bytes(0),
		_data(0) {}
	Map(const int width, const int height) :
		_width(width < 1 ? 1 : width),
		_height(height < 1 ? 1 : height),
		_depth(1),
		_size(this->_width * this->_height),
		_bytes(sizeof(T) * this->_size),
		_data(0)
	{
		this->resize(this->_width, this->_height);
	}
	Map(const int width, const int height, const int depth) :
		_width(width < 1 ? 1 : width),
		_height(height < 1 ? 1 : height),
		_depth(depth < 1 ? 1 : depth),
		_size(this->_width * this->_height * this->_depth),
		_bytes(sizeof(T) * this->_size),
		_data(0)
	{
		this->resize(this->_width, this->_height, this->_depth);
	}
	~Map()
	{
		this->resize(0, 0, 0);
	}

	T& get(const int x, const int y)
	{
		if (this->_data == 0)
		{
			this->resize(1, 1);
		}

		return this->_data[(this->_width * (y % this->_height)) + (x % this->_width)];
	}
	T& get(const int x, const int y, const int z)
	{
		if (this->_data == 0)
		{
			this->resize(1, 1);
		}

		return this->_data[(this->_width * this->_height * (z % this->_depth)) + (this->_width * (y % this->_height)) + (x % this->_width)];
	}

	void set(const int x, const int y, const T& item)
	{
		if (this->_size < 1)
		{
			this->resize(1, 1);
		}

		this->_data[(this->_width * (y % this->_height)) + (x % this->_width)] = item;
	}
	void set(const int x, const int y, const int z, const T& item)
	{
		if (this->_size < 1)
		{
			this->resize(1, 1);
		}

		this->_data[(this->_width * this->_height * (z % this->_depth)) + (this->_width * (y % this->_height)) + (x % this->_width)] = item;
	}

	void resize(const int width, const int height)
	{
		this->resize(width, height, 1);
	}
	void resize(const int width, const int height, const int depth)
	{
		if (width < 1 || height < 1 || depth < 1)
		{
			this->_width = 0;
			this->_height = 0;
			this->_depth = 0;
			this->_size = 0;
			this->_bytes = 0;
			if (this->_data != 0)
			{
				delete[] this->_data;
			}

			this->_data = 0;
			return;
		}

		const int oldWidth = this->_width;
		const int oldHeight = this->_height;
		const int oldDepth = this->_depth;
		this->_width = width;
		this->_height = height;
		this->_depth = depth;
		this->_size = this->_width * this->_height * this->_depth;
		this->_bytes = sizeof(T) * this->_size;
		T* clean = new T[this->_size];
		memset(clean, 0, this->_bytes);
		if (this->_data != 0)
		{
			for (int j = 0; j < oldDepth; j++)
			{
				for (int i = 0; i < oldHeight; i++)
				{
					memcpy(clean + (oldWidth * oldHeight * j) + (oldWidth * i), this->_data, sizeof(T) * oldWidth);
				}
			}

			delete[] this->_data;
		}

		this->_data = clean;
	}

	void clear()
	{
		this->resize(0, 0, 0);
	}
	void zero()
	{
		memset(this->_data, 0, this->_bytes);
	}

	void operator=(const Map<T>& m)
	{
		this->resize(m._width, m._height, m._depth);
		memcpy(this->_data, m._data, this->_bytes);
	}
	T& operator[](const int index)
	{
		return this->_data[index % this->_size];
	}

protected:

	int _width;
	int _height;
	int _depth;
	int _size;
	int _bytes;
	T* _data;

};

#endif
#endif