/*
    Runtime Fixed Length Array.
    Flexibility of use is lower than std::vector. 
    But memory efficiency is much better.
*/

#include <stdexcept>
#include <utility>
#include <iterator>

namespace xstl
{

    template <class T>
	class fixed_vector
	{
	public:
		using Self = fixed_vector;

	public: //stl standard type member
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type & ;
		using const_reference = const value_type&;
		using pointer = value_type * ;
		using const_pointer = const value_type*;
		class iterator;
		class const_iterator;
		using reverse_iterator = std::reverse_iterator<fixed_vector::iterator>;
		using const_reverse_iterator = std::reverse_iterator<fixed_vector::const_iterator>;

	private:
		T* _array = nullptr;
		size_type _length = 0;
	public:
		fixed_vector(size_type length, const_reference value=value_type()) : _array(new value_type[length]), _length(length)
		{
			for (int i = 0; i < this->_length; i++)
				_array[i] = value;
		}

		fixed_vector(std::initializer_list<value_type> init) : _array(new value_type[init.size()]), _length(init.size())
		{
			int i = 0;
			for (auto&&e : init)
			{
				_array[i] = e;
				i++;
			}
		}

		template<class InputIterator>
		fixed_vector(InputIterator begin, InputIterator end) : _length(std::distance(begin, end))
		{
			this->_array = new value_type[this->_length];
			int i = 0;
			for (; begin != end; begin++)
			{
				_array[i] = *begin;
				i++;
			}
		}
	public:
		fixed_vector() = default;
		~fixed_vector()
		{
			if (this->_array != nullptr)
				delete[] this->_array;
		}

	public: //copy & move
		fixed_vector(const Self& other)
		{
			this->_length = other._length;
			this->_array = new value_type[other._length];

			for (int i = 0; i < other._length; i++)
				this->_array[i] = other._array[i];
		}
		fixed_vector(Self&& other)
		{
			this->_length = other._length;
			this->_array = other._array;
			other._length = 0;
			other._array = nullptr;
		}
		Self& operator=(const Self& other)
		{
			this->clear();

			this->_length = other._length;
			this->_array = new value_type[other._length];

			for (int i = 0; i < other._length; i++)
				this->_array[i] = other._array[i];

			return *this;
		}
		Self& operator=(Self&& other) 
		{
			this->_length = other._length;
			this->_array = other._array;
			other._length = 0;
			other._array = nullptr;

			return *this;
		}

	public:
		reference operator[](size_type index)
		{
			return this->_array[index];
		}
		const_reference operator[](size_type index) const
		{
			return this->_array[index];
		}
		reference at(size_type index)
		{
			if (index >= this->_length)
				throw std::out_of_range();
			return this->_array[index];
		}
		const_reference at(size_type index) const
		{
			if (index >= this->_length)
				throw std::out_of_range();
			return this->_array[index];
		}
		pointer data() noexcept
		{
			return this->_array;
		}
		const_pointer data() const noexcept
		{
			return this->_array;
		}

	public:
		bool empty() const noexcept
		{
			return this->_length == 0;
		}
		size_type size() const noexcept
		{
			return this->_length;
		}
	public:
		void clear() noexcept
		{
			if (this->_array != nullptr)
			{
				delete[] this->_array;
				this->_length = 0;
			}
		}

		void assign(size_type length, const_reference value = value_type())
		{
			this->clear();
			this->_length = length;
			this->_array = new value_type[length];
			for (int i = 0; i < this->_length; i++)
				_array[i] = value;
		}
		void assign(std::initializer_list<value_type> init)
		{
			this->assign(init.size());
			int i = 0;
			for (auto&&e : init)
			{
				_array[i] = e;
				i++;
			}
		}
		template <class InputIterator>
		void assign(InputIterator begin, InputIterator end)
		{
			this->assign(std::distance(begin, end));
			this->_array = new value_type[this->_length];
			int i = 0;
			for (; begin != end; begin++)
			{
				_array[i] = *begin;
				i++;
			}
		}

		void swap(Self& other) noexcept
		{
			size_type length_temp = other._length;
			T* array_temp = other._array;

			other._length = this->_length;
			other._array = this->_array;

			this->_length = length_temp;
			this->_array = array_temp;
		}

	public: //iterator 
		iterator begin()
		{
			return fixed_vector::iterator(this->_array);
		}
		fixed_vector::const_iterator begin() const noexcept
		{
			return this->cbegin();
		}
		fixed_vector::const_iterator cbegin() const noexcept
		{
			return fixed_vector::const_iterator(this->_array);
		}

		fixed_vector::iterator end()
		{
			return fixed_vector::iterator(this->_array + this->_length);
		}
		fixed_vector::const_iterator end() const noexcept
		{
			return this->cend();
		}
		fixed_vector::const_iterator cend() const noexcept
		{
			return fixed_vector::const_iterator(this->_array + this->_length);
		}

	public: //reverse iterator
		fixed_vector::reverse_iterator rbegin()
		{
			return fixed_vector::reverse_iterator(this->end());
		}
		fixed_vector::const_reverse_iterator rbegin() const noexcept
		{
			return this->crbegin();
		}
		fixed_vector::const_reverse_iterator crbegin() const noexcept
		{
			return fixed_vector::const_reverse_iterator(this->cend());
		}
        
		fixed_vector::reverse_iterator rend()
		{
			return fixed_vector::reverse_iterator(this->begin());
		}
		fixed_vector::const_reverse_iterator rend() const noexcept
		{
			return this->crend();
		}
		fixed_vector::const_reverse_iterator crend() const noexcept
		{
			return fixed_vector::const_reverse_iterator(this->cbegin());
		}
        
        class iterator
        {
        private:
            pointer current;
        public:
            using Self = iterator;
		public:
			using value_type = fixed_vector::value_type;
			using pointer = fixed_vector::pointer;
			using reference = fixed_vector::reference;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::random_access_iterator_tag;
        public:
            iterator() = delete;
            virtual ~iterator() = default;
        public: //move & copy member
            iterator(const Self&) = default;
            iterator(Self&&) = default;
            Self& operator=(const Self&) = default;
            Self& operator=(Self&&) = default;
        public:
            iterator(pointer p): current(p) 
            {}
        public: //move operator
            Self& operator++()
            {
                current++;
                return *this;
            }
            Self operator++(int)
            {
                current++;
                return *this;
            }
            Self& operator--()
            {
                current--;
                return *this;
            }
            Self operator--(int)
            {
                current--;
                return *this;
            }
        public: //access operator
			reference operator*()
            {
                return *current;
            }
			const_reference operator*() const
            {
                return *current;
            }
			reference operator[](size_type index)
            {
                return current[index];
            }
			const_reference operator[](size_type index) const
            {
                return current[index];
            }
			pointer operator->()
            {
                return current;
            }
			const_pointer operator->() const
            {
                return current;
            }
        public: //comparer
            bool operator==(const Self& other) const
            {
                return this->current == other.current;
            }
            bool operator!=(const Self& other) const
            {
                return this->current != other.current;
            }
        };

        class const_iterator
        {
		private:
			const_pointer current;
		public:
			using Self = const_iterator;
		public:
			using value_type = value_type;
			using pointer = pointer;
			using reference = reference;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::random_access_iterator_tag;
		public:
			const_iterator() = delete;
			virtual ~const_iterator() = default;
		public: //move & copy member
			const_iterator(const Self&) = default;
			const_iterator(Self&&) = default;
			Self& operator=(const Self&) = default;
			Self& operator=(Self&&) = default;
		public:
			const_iterator(const_pointer p) : current(p)
			{}
		public: //move operator
			Self& operator++()
			{
				current++;
				return *this;
			}
			Self operator++(int)
			{
				current++;
				return *this;
			}
			Self& operator--()
			{
				current--;
				return *this;
			}
			Self operator--(int)
			{
				current--;
				return *this;
			}
		public: //access operator
			const_reference operator*() const
			{
				return *current;
			}
			const_reference operator[](size_type index) const
			{
				return current[index];
			}
			const_pointer operator->() const
			{
				return current;
			}
		public: //comparer
			bool operator==(const Self& other) const
			{
				return this->current == other.current;
			}
			bool operator!=(const Self& other) const
			{
				return this->current != other.current;
			}
        };
    };


};
