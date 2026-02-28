#include <utility>

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

	~HcArray()
	{
		delete[] m_data;
	}

	HcArray(const HcArray&) = delete;
	HcArray& operator=(const HcArray&) = delete;

	inline void push_back(const T& value)
	{
		if (m_size >= m_capacity)
		{
			size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
			reserve(new_capacity);
		}

		m_data[m_size] = value;
		m_size++;
	}


	inline void reserve(size_t new_capacity)
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

	inline T& operator[](size_t index)
	{
		return m_data[index];
	}

	inline const T& operator[](size_t index) const
	{
		return m_data[index];
	}

    inline size_t size() const { return m_size; }

private:
	T* m_data;
	size_t m_size = 0;
	size_t m_capacity = 0;
};


