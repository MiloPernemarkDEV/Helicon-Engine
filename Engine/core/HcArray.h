#include <utility>
#include <initializer_list>
#include "Defines.h"

template<typename T>
class HcArray {
public:
	HcArray()
		: m_data(nullptr),
		m_size(0),
		m_capacity(0)
	{
	}

	HcArray(size_t size)
		: m_size(size),
		m_capacity(size)
	{
		m_data = new T[m_capacity];
	}

	HcArray(std::initializer_list<T> init)
		: m_size(init.size()),
		m_capacity(init.size())
	{
		m_data = new T[m_capacity];

		size_t i = 0;
		for (const T& value : init)
		{
			m_data[i++] = value;
		}
	}

	HcArray(HcArray&& other) noexcept
		: m_data(other.m_data),
		m_size(other.m_size),
		m_capacity(other.m_capacity)
	{
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	HcArray& operator=(HcArray&& other) noexcept
	{
		if (this == &other)
			return *this;

		delete[] m_data;

		m_data = other.m_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;

		return *this;
	}

	HcArray(const HcArray& other)
		: m_size(other.m_size),
		m_capacity(other.m_capacity)
	{
		m_data = new T[m_capacity];

		for (size_t i = 0; i < m_size; ++i)
			m_data[i] = other.m_data[i];
	}

	HcArray& operator=(const HcArray& other)
	{
		if (this == &other)
			return *this;

		T* new_data = new T[other.m_capacity];

		for (size_t i = 0; i < other.m_size; ++i)
			new_data[i] = other.m_data[i];

		delete[] m_data;

		m_data = new_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		return *this;
	}

	template<typename InputIt>
	HcArray(InputIt first, InputIt last)
	{
		m_size = 0;
		m_capacity = static_cast<size_t>(last - first);
		m_data = new T[m_capacity];

		for (InputIt it = first; it != last; ++it)
		{
			m_data[m_size++] = *it;
		}
	}

	~HcArray()
	{
		delete[] m_data;
	}

	FORCE_INLINE void push_back(const T& value)
	{
		if (m_size >= m_capacity)
		{
			size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
			reserve(new_capacity);
		}

		m_data[m_size] = value;
		m_size++;
	}

	// rvalue avoids copies 
	FORCE_INLINE void push_back(T&& value)
	{
		if (m_size >= m_capacity)
			reserve(m_capacity == 0 ? 1 : m_capacity * 2);

		m_data[m_size++] = std::move(value);
	}

	FORCE_INLINE void reserve(size_t new_capacity)
	{
		if (new_capacity <= m_capacity)
			return;

		T* new_data = new T[new_capacity];

		for (size_t i = 0; i < m_size; i++)
			new_data[i] = std::move(m_data[i]);

		delete[] m_data;

		m_data = new_data;
		m_capacity = new_capacity;
	}

	FORCE_INLINE T& operator[](size_t index)
	{
		return m_data[index];
	}

	FORCE_INLINE const T& operator[](size_t index) const
	{
		return m_data[index];
	}

    FORCE_INLINE size_t size() const { return m_size; }

	FORCE_INLINE void clear() { m_size = 0; }

	T* begin() { return m_data; }
	T* end() { return m_data + m_size; }
	T* data() { return m_data; }

	const T* begin() const { return m_data; }
	const T* end()   const { return m_data + m_size; }        
	const T* data() const { return m_data; } 

private:
	T* m_data;
	size_t m_size = 0;
	size_t m_capacity = 0;
};