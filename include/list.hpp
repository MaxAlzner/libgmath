#ifndef LIST_H
#define LIST_H

#if !defined (List)

template <typename T> class List
{
public:

	List()
	{
		this->_count = 0;
		this->_first = 0;
		this->_last = 0;
	}
	~List()
	{
		this->clear();
	}

	struct ListItem
	{

		ListItem() : index(0), next(0), previous(0) {}
		ListItem(const T& item, ListItem* previous, ListItem* next, int index) : data(item), previous(previous), next(next), index(index) {}
		~ListItem() {}

		ListItem* next;
		ListItem* previous;
		int index;
		T data;

	};

	struct Iterator
	{

		Iterator() : _list(0), _link(0) {}
		Iterator(List<T>* list) : _list(list), _link(list->_first) {}
		~Iterator() {}

		bool next()
		{
			if (this->_link != 0)
			{
				this->_link = this->_link->next;
				if (this->_link != 0)
				{
					return true;
				}
			}

			return false;
		}
		bool previous()
		{
			if (this->_link != 0)
			{
				this->_link = this->_link->previous;
				if (this->_link != 0)
				{
					return true;
				}
			}

			return false;
		}

		bool inside()
		{
			return this->_link != 0;
		}

		void restart()
		{
			if (this->_list != 0)
			{
				this->_link = this->_list->_first;
			}
		}
		void end()
		{
			if (this->_list != 0)
			{
				this->_link = this->_list->_last;
			}
		}

		T& current()
		{
			if (this->_link != 0)
			{
				return this->_link->data;
			}

			throw std::exception("invalid iterator position");
		}

	protected:

		List<T>* _list;
		ListItem* _link;

	};

	friend struct Iterator;

	const int add(const T& item)
	{
		ListItem* link = new ListItem(item, this->_last, 0, this->_count);
		if (this->_last != 0)
		{
			this->_last->next = link;
		}

		this->_last = link;

		if (this->_first == 0)
		{
			this->_first = link;
		}

		this->_count++;
		return link->index;
	}
	T& get(const int index)
	{
		ListItem* current = this->_first;
		int iteration = 0;
		while (current != 0)
		{
			if (iteration == index)
			{
				return current->data;
			}

			iteration++;
			current = current->next;
		}

		throw std::exception("invalid index");
	}
	bool contains(const T& item)
	{
		ListItem* current = this->_first;
		while (current != 0)
		{
			if (memcmp(&(current->data), &item, sizeof(T)) == 0)
			{
				return true;
			}

			current = current->next;
		}

		return false;
	}
	const int indexOf(const T& item)
	{
		ListItem* current = this->_first;
		while (current != 0)
		{
			if (memcmp(&(current->data), &item, sizeof(T)) == 0)
			{
				return current->index;
			}

			current = current->next;
		}

		return -1;
	}
	void insert(const T& item, const int index)
	{
		if (this->_first == 0)
		{
			this->_first = new ListItem(item, 0, 0, 0);
			this->_last = this->_first;
			this->_count = 1;
		}
		else if (index >= this->_count)
		{
			ListItem* link = new ListItem(item, this->_last, 0, this->_count);
			if (this->_last != 0)
			{
				this->_last->next = link;
			}

			this->_last = link;
			this->_count++;
		}
		else
		{
			ListItem* existing = this->search(index);
			ListItem* link = new ListItem(item, existing->previous, existing, existing->index);
			if (existing->previous != 0)
			{
				existing->previous->next = link;
			}

			existing->previous = link;

			this->shift(existing, 1);
		}
	}
	void remove(const T& item)
	{
		ListItem* current = this->_first;
		while (current != 0)
		{
			if (memcmp(&(current->data), &item, sizeof(T)) == 0)
			{
				this->unlink(current);
				delete current;

				return;
			}

			current = current->next;
		}
	}
	void removeAt(const int index)
	{
		ListItem* current = this->_first;
		while (current != 0)
		{
			if (current->index == index)
			{
				this->unlink(current);
				delete current;

				return;
			}

			current = current->next;
		}
	}

	void clear()
	{
		ListItem* current = this->_first;
		ListItem* temp = 0;
		while (current != 0)
		{
			temp = current;
			current = temp->next;
			delete temp;
		}

		this->_first = 0;
		this->_last = 0;
		this->_count = 0;
	}

	const int count() const
	{
		return this->_count;
	}
	bool inside(const int index) const
	{
		return index < this->_count && index >= 0;
	}

	Iterator iterator() const
	{
		//this->_iterator->restart();
		//return this->_iterator;
		return Iterator((List<T>*)this);
	}
	Iterator iteratorAtEnd() const
	{
		//this->_iterator->end();
		//return this->_iterator;
		Iterator i((List<T>*)this);
		i.end();
		return i;
	}

	T& operator[](const int index)
	{
		return this->get(index);
	}

protected:

	int _count;
	ListItem* _first;
	ListItem* _last;

	ListItem* search(const int index)
	{
		ListItem* current = this->_first;
		while (current != 0)
		{
			if (current->index == index)
			{
				return current;
			}

			current = current->next;
		}

		return 0;
	}
	void shift(ListItem* start, const int amount)
	{
		ListItem* current = start;
		while (current != 0)
		{
			current->index += amount;
			current = current->next;
		}
	}
	void unlink(ListItem* link)
	{
		ListItem* prev = link->previous;
		ListItem* next = link->next;
		if (prev != 0)
		{
			prev->next = next;
		}

		if (next != 0)
		{
			next->previous = prev;
			this->shift(next, -1);
		}

		if (link == this->_first)
		{
			this->_first = next;
		}

		if (link == this->_last)
		{
			this->_last = prev;
		}
	}

};

#endif
#endif