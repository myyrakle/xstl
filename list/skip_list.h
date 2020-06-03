#include <cassert>
#include <utility>
#include <iterator>

namespace xstl
{
    template <class T>
    class skip_list
    {
    public:
        using Self = skip_list;

    public: //stl standard type member
        using value_type = T;
        struct node_type;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        class iterator;
        class const_iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    private:
        node_type* _head = nullptr;
        size_type _length = 0;

    public: //list node type
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
        skip_list() = default;
        ~skip_list()
        {
            this->clear();
        }

    public:
        skip_list(size_type count, const_reference value = value_type())
        {
            for (int i = 0; i < count; i++)
                this->push_back(value);
        }
        skip_list(std::initializer_list<value_type> init)
        {
            for (auto& e : init)
                this->push_back(e);
        }
        template <class InputIterator>
        skip_list(InputIterator begin, InputIterator end)
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

    public: // copy&move member
        skip_list(const Self& other) : circular_list(other.begin(), other.end())
        {}
        skip_list(Self&& other) : _head(other._head), _length(other._length)
        {
            other._head = nullptr;
            other._length = 0;
        }
        Self& operator=(const Self& other)
        {
            this->assign(other.begin(), other.end());
            return *this;
        }
        Self& operator=(Self&& other)
        {
            this->_head = other._head;
            this->_length = other._length;
            other._head = nullptr;
            other._length = 0;
            return *this;
        }

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
        //Clear All Data
        void clear() noexcept
        {
            if (!this->empty())
                this->pop_front();
        }

        //Swap
        void swap(Self& other) noexcept;

    public: //front modifier
        void push_front(const_reference value);        
        void push_front(value_type&& value);

        void pop_front();

        template <class... Args>
        void emplace_front(Args&&... args);

    public: // back modifier
        void push_back(const_reference value);
        void push_back(value_type&& value);
        void pop_back();

        template <class... Args>
        void emplace_back(Args&&... args);

    public:
        iterator insert(const_iterator pos, const_reference value);
        iterator insert(const_iterator pos, value_type&& value);

        iterator insert(const_iterator pos, size_type count, const_reference value);

        template <class InputIterator>
        iterator insert(const_iterator pos, InputIterator begin, InputIterator end);
        iterator insert(const_iterator pos, std::initializer_list<T> init);

        template <class... Args>
        iterator emplace(const_iterator pos, Args&&... args);

        iterator erase(const_iterator pos);
        iterator erase(const_iterator begin, const_iterator end);

        void resize(size_type count, const_reference new_value = value_type());

    public: //iterator
        iterator begin()
        {
            return iterator(this->_head);
        }
        iterator end()
        {
            return iterator(nullptr);
        }
        const_iterator begin() const
        {
            return this->cbegin();
        }
        const_iterator end() const
        {
            return this->cend();
        }
        const_iterator cbegin() const
        {
            return const_iterator(this->_head);
        }
        const_iterator cend() const
        {
            return const_iterator(nullptr);
        }

    public: //reverse iterator
        reverse_iterator rbegin()
        {
            return reverse_iterator(this->_head);
        }
        reverse_iterator rend()
        {
            return reverse_iterator(nullptr);
        }
        const_reverse_iterator rbegin() const
        {
            return this->cbegin();
        }
        const_reverse_iterator rend() const
        {
            return this->cend();
        }
        const_reverse_iterator crbegin() const
        {
            return const_reverse_iterator(this->_head);
        }
        const_reverse_iterator crend() const
        {
            return const_reverse_iterator(nullptr);
        }

    public:
        class iterator
        {
        private:
            node_type* current;
        public:
            using Self = iterator;
            friend const_iterator;
            friend circular_list;
        public:
            using value_type = value_type;
            using pointer = pointer;
            using reference = reference;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;
        public:
            iterator() = delete;
            virtual ~iterator() = default;
        public: //move & copy member
            iterator(const Self&) = default;
            iterator(Self&&) = default;
            Self& operator=(const Self&) = default;
            Self& operator=(Self&&) = default;
        public:
            iterator(node_type* p) : current(p)
            {}
        public: //move operator
            Self& operator++()
            {
                assert(current != nullptr);
                current = current->next;
                return *this;
            }
            Self operator++(int)
            {
                assert(current != nullptr);
                current = current->next;
                return *this;
            }
            Self& operator--()
            {
                assert(current != nullptr);
                current = current->prev;
                return *this;
            }
            Self operator--(int)
            {
                assert(current != nullptr);
                current = current->prev;
                return *this;
            }
        public: //access operator
            reference operator*()
            {
                assert(current != nullptr);
                return current->value;
            }
            const_reference operator*() const
            {
                assert(current != nullptr);
                return current->value;
            }
            pointer operator->()
            {
                assert(current != nullptr);
                return &current->value;
            }
            const_pointer operator->() const
            {
                assert(current != nullptr);
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

        class const_iterator
        {
        private:
            const node_type* current;
        public:
            using Self = const_iterator;
            friend circular_list;
        public:
            using value_type = value_type;
            using pointer = pointer;
            using reference = reference;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;
        public:
            const_iterator() = delete;
            ~const_iterator() = default;
        public: //move & copy member
            const_iterator(const Self&) = default;
            const_iterator(Self&&) = default;
            Self& operator=(const Self&) = default;
            Self& operator=(Self&&) = default;
        public:
            const_iterator(node_type* p) : current(p)
            {}
            const_iterator(const iterator& mutable_iterator) : current(mutable_iterator.current)
            {}
        public: //move operator
            Self& operator++()
            {
                assert(current != nullptr);
                current = current->next;
                return *this;
            }
            Self operator++(int)
            {
                assert(current != nullptr);
                current = current->next;
                return *this;
            }
            Self& operator--()
            {
                assert(current != nullptr);
                current = current->prev;
                return *this;
            }
            Self operator--(int)
            {
                assert(current != nullptr);
                current = current->prev;
                return *this;
            }
        public: //access operator
            const_reference operator*() const
            {
                assert(current != nullptr);
                return current->value;
            }
            const_pointer operator->() const
            {
                assert(current != nullptr);
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
