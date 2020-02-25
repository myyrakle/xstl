#include <cassert>

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

        }
        
    public:
        circular_list(const Self&);
        circular_list(Self&&);
        Self& operator=(const Self&);
        Self& operator=(Self&&);

    public:
        reference front()
        {
            return this->_head->value;
        }
        const_reference front() const
        {
            return this->_head->value;
        }
        reference back()
        {
            return this->_head->prev->value;
        }
        const_reference back() const
        {
            return this->_head->prev->value;
        }
    public:
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
        // void push_front(value_type&& value)
        // {

        // }
    public: //iterator
        iterator begin()
        {
            return iterator(this->_head);
        }
        iterator end()
        {
            return iterator(nullptr);
        }

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