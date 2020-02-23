

namespace xstl
{
    template <class T>
    class circular_list
    {
    public:
		using Self = fixed_vector;

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
        };


    public:
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