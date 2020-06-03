#include <cassert>
#include <utility>
#include <iterator>

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
        circular_list() = default;
        ~circular_list()
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
        
    public: // copy&move member
        circular_list(const Self& other): circular_list(other.begin(), other.end())
        {}
        circular_list(Self&& other): _head(other._head), _length(other._length)
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

            if (this->_length == 1)
            {
                delete this->_head;
                this->_head = nullptr;
            }
            else 
            {
                auto original_head = this->_head;
                this->_head = this->_head->next;
                this->_head->prev = original_head->prev;
                delete original_head;
            }
            
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

            if (this->_length == 1)
            {
                delete this->_head;
                this->_head = nullptr;
            }
            else 
            {
                auto original_back = this->_head->prev;
                this->_head->prev = original_back->prev;
                original_back->prev->next = this->_head;
                delete original_back;
            }
            
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
        }

    public:
        iterator insert(const_iterator pos, const_reference value)
        {
            auto& before = const_cast<node_type*&>(pos.current);
            auto& after = pos.current->next;
            before->next = new node_type(before, value, after);
            after->prev = before->next;

            this->_length++;
            return iterator(before->next);
        }
        iterator insert(const_iterator pos, value_type&& value)
        {
            auto& before = const_cast<node_type*&>(pos.current);
            auto& after = pos.current->next;
            before->next = new node_type(before, std::move(value), after);
            after->prev = before->next;

            this->_length++;
            return iterator(before->next);
        }

        iterator insert(const_iterator pos, size_type count, const_reference value)
        {
            auto position = pos;

            for (int i = 0; i < count; i++)
            {
                position = this->insert(position, value);
            }

            return iterator(pos.current->next);
        }

        template <class InputIterator>
        iterator insert(const_iterator pos, InputIterator begin, InputIterator end)
        {
            auto position = pos;

            for (;begin!=end; begin++)
            {
                position = this->insert(position, *begin);
            }

            return iterator(pos.current->next);
        }
        iterator insert(const_iterator pos, std::initializer_list<T> init)
        {
            auto position = pos;

            for (auto& e:init)
            {
                position = this->insert(position, e);
            }

            return iterator(pos.current->next);
        }

        template <class... Args>
        iterator emplace(const_iterator pos, Args&&... args)
        {
            auto& before = const_cast<node_type*&>(pos.current);
            auto& after = pos.current->next;
            before->next = new node_type(before, value_type(std::forward<Args>(args)...) , after);
            after->prev = before->next;

            this->_length++;
            return iterator(before->next);
        }

        iterator erase(const_iterator pos)
        {
            assert(this->_head != nullptr);

            this->_length--;

            if (this->_length == 1)
            {
                assert(this->_head == pos.current);
                this->_head = nullptr;

                return iterator(nullptr);
            }
            else
            {
                auto& before = pos.current->prev;
                auto& after = pos.current->next;

                if (this->_head == pos.current)
                    this->_head = after;

                before->next = after;
                after->prev = before;

                delete pos.current;

                return iterator(after);
            }
        }
        iterator erase(const_iterator begin, const_iterator end)
        {
            auto& before = const_cast<node_type*&>(begin.current->prev);
            auto& after = const_cast<node_type*&>(end.current);

            before->next = after;
            after->prev = before;

            if (this->_head == begin.current)
                this->_head = after;

            while (begin != end)
            {
                auto temp = begin.current;
                begin++;
                delete temp;
                this->_length--;
            }

            return iterator(after);
        }

        void resize(size_type count, const_reference new_value = value_type())
        {
            if(count > this->_length)
            { 
                size_type difference = count - _length;
                for (int i = 0; i < difference; i++)
                    this->push_back(new_value);
            }
            else if (count == this->_length)
            {
                //Nothing To Do
            }
            else
            {
                size_type difference = _length - count;
                for (int i = 0; i < difference; i++)
                    this->pop_back();
            }
        }

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
            iterator(node_type* p): current(p) 
            {}
        public: //move operator
            Self& operator++()
            {
                assert(current!=nullptr);
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
            const_iterator(const iterator& mutable_iterator): current(mutable_iterator.current)
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
