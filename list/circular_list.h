#include <cassert>
#include <utility>

namespace xstl
{
    template <class T>
    class circular_list
    {
    public:
		using Self = circular_list;

	public: //stl standard type member
		using value_type = T;
        struct node_type;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type & ;
		using const_reference = const value_type&;
		using pointer = value_type *;
		using const_pointer = const value_type*;
		class iterator;
		class const_iterator;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    private:
        node_type* _head = nullptr;
        size_type _length = 0;

    public:
        struct node_type
        {
            using Self = node_type;
        public:
            Self* prev;
            value_type value;
            Self* next;
        public:
            node_type() = delete;
            virtual ~node_type() = default;
            node_type(Self* _prev, const_reference _value, Self* _next)
                : prev(_prev), value(_value), next(_next)
            {}
            node_type(Self* _prev, value_type&& _value, Self* _next)
                : prev(_prev), value(std::move(_value)), next(_next)
            {}
        };

    public:
        circular_list() = default;
        virtual ~circular_list()
        {
			this->clear();
        }
	public:
		circular_list(size_type count, const_reference value = value_type())
		{
			for (int i = 0; i < count; i++)
				this->push_back(value);
		}
		circular_list(std::initializer_list<value_type> init)
		{
			for (auto& e : init)
				this->push_back(e);
		}
		template <class InputIterator>
		circular_list(InputIterator begin, InputIterator end)
		{
			for (; begin != end; begin++)
				this->push_back(*begin);
		}

	public:
		void assign(size_type count, const_reference value = value_type())
		{
			this->clear();
			for (int i = 0; i < count; i++)
				this->push_back(value);
		}
		void assign(std::initializer_list<value_type> init)
		{
			this->clear();
			for (auto& e : init)
				this->push_back(e);
		}
		template <class InputIterator>
		void assign(InputIterator begin, InputIterator end)
		{
			this->clear();
			for (; begin != end; begin++)
				this->push_back(*begin);
		}
        
    public:
        circular_list(const Self&);
        circular_list(Self&&);
        Self& operator=(const Self&);
        Self& operator=(Self&&);

    public: //Element Access
        reference front()
        {
			assert(this->_head != nullptr);
            return this->_head->value;
        }
        const_reference front() const
        {
			assert(this->_head != nullptr);
            return this->_head->value;
        }
        reference back()
        {
			assert(this->_head != nullptr);
            return this->_head->prev->value;
        }
        const_reference back() const
        {
			assert(this->_head != nullptr);
            return this->_head->prev->value;
        }

    public: //Capacity
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
			if (!this->empty())
				this->pop_front();
		}

		void swap(Self& other) noexcept
		{
			auto temp_head = this->_head;
			auto temp_length = this->_length;

			this->_head = other._head;
			this->_length = other._length;

			other._head = temp_head;
			other._length = temp_length;
		}

	public: //front modifier
        void push_front(const_reference value)
        {
            if(this->_head==nullptr)
            {
                this->_head = new node_type(nullptr, value, nullptr);
                _head->prev = _head; 
                _head->next = _head;
            }
            else
            {
                this->_head = new node_type(this->_head->prev, value, this->_head);
				_head->next->prev = _head;
            }
            
            _length++;
        }
        void push_front(value_type&& value)
        {
			if (this->_head == nullptr)
			{
				this->_head = new node_type(nullptr, std::move(value), nullptr);
				_head->prev = _head;
				_head->next = _head;
			}
			else
			{
				this->_head = new node_type(this->_head->prev, value, this->_head);
				_head->next->prev = _head;
			}

			_length++;
        }
		void pop_front()
		{
			assert(this->_head != nullptr);

			auto original_head = this->_head;
			this->_head = this->_head->next;
			this->_head->prev = original_head->prev;
			delete original_head;

			this->_length--;
		}
		template <class... Args>
		void emplace_front(Args&&... args)
		{
			if (this->_head == nullptr)
			{
				this->_head = new node_type(nullptr, value_type(std::forward<Args>(args)...), nullptr);
				_head->prev = _head;
				_head->next = _head;
			}
			else
			{
				this->_head = new node_type(this->_head->prev, value_type(std::forward<Args>(args)...), this->_head);
				_head->next->prev = _head;
			}

			_length++;
		}

	public: // back modifier
		void push_back(const_reference value)
		{
			if (this->_head == nullptr)
			{
				this->_head = new node_type(nullptr, value, nullptr);
				_head->prev = _head;
				_head->next = _head;
			}
			else
			{
				this->_head->prev = new node_type(this->_head->prev, value, this->_head);
				this->_head->prev->prev->next = this->_head->prev;
			}

			_length++;
		}
		void push_back(value_type&& value)
		{
			if (this->_head == nullptr)
			{
				this->_head = new node_type(nullptr, std::move(value), nullptr);
				_head->prev = _head;
				_head->next = _head;
			}
			else
			{
				this->_head->prev = new node_type(this->_head->prev, std::move(value), this->_head);
				this->_head->prev->prev->next = this->_head->prev;
			}

			_length++;
		}
		void pop_back()
		{
			assert(this->_head != nullptr);

			auto original_back = this->_head->prev;
			this->_head->prev = original_back->prev;
			original_back->prev->next = this->_head;
			delete original_back;

			this->_length--;
		}
		
		template <class... Args>
		void emplace_back(Args&&... args)
		{
			if (this->_head == nullptr)
			{
				this->_head = new node_type(nullptr, value_type(std::forward<Args>(args)...), nullptr);
				_head->prev = _head;
				_head->next = _head;
			}
			else
			{
				this->_head->prev = new node_type(this->_head->prev, value_type(std::forward<Args>(args)...), this->_head);
				this->_head->prev->prev->next = this->_head->prev;
			}

			_length++;


    public: //iterator
        iterator begin()
        {
            return iterator(this->_head);
        }
        iterator end()
        {
            return iterator(nullptr);
        }

	public:
        class iterator
        {
        private:
            pointer current;
        public:
            using Self = iterator;
		public:
			using value_type = value_type;
			using pointer = pointer;
			using reference = reference;
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
                current = current->next;
                return *this;
            }
            Self operator++(int)
            {
                current = current->next;
                return *this;
            }
            Self& operator--()
            {
                current = current->prev;
                return *this;
            }
            Self operator--(int)
            {
                current = current->prev;
                return *this;
            }
        public: //access operator
            reference operator*()
            {
                return current->value;
            }
            const_reference operator*() const
            {
                return current->value;
            }
            pointer operator->()
            {
                return &current->value;
            }
            const_pointer operator->() const
            {
                return &current->value;
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
}
