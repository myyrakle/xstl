#include <stdexcept>
#include <utility>
#include <iterator>

namespace xstl
{
    /*
    Runtime Fixed Length Array.
    Flexibility of use is lower than vector. 
    But memory efficiency is much better.
    */

    template <class T>
    class fixed_vector
    {
    public:
        using Self = fixed_vector;
        
    public: //stl standard type member
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference	= value_type&; 
        using const_reference = const value_type&; 
        using pointer =	value_type*;
        using const_pointer	= const value_type*; 
        class iterator;
        class const_iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    private:
        T* _array;
        size_type _length;
    public:
        fixed_vector(): _array(nullptr), _length(0)
        {}

        fixed_vector(size_type length): _array(new T[length]), _length(length)
        {}

        fixed_vector(size_type length, const_reference value): _array(new T[length]), _length(length)
        {
            for(int i=0; i < this->_length; i++)
                _array[i] = value;
        }

        fixed_vector(std::initializer_list<T> init): _array(new T[init.size()]), _length(init.size())
        {
            int i = 0;
            for(auto&&e : init)
            {
                _array[i];
                i++;
            }
        }

        template<class InputIterator>
        fixed_vector(InputIterator begin, InputIterator end): _length(std::distance(begin, end))
        {
            this->_array = new T[this->_length];
            int i = 0;
            for(;begin!=end; begin++)
            {
                _array[i];
                i++;
            }
        }

        virtual ~fixed_vector()
        {
            if(this->_array != nullptr)
                delete[] this->_array;
        }

    public: //copy & move
        fixed_vector(const Self&);
        fixed_vector(Self&&);
        Self& operator=(const Self&);
        Self& operator=(Self&&);

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
            if(index >= this->_length)
                throw std::out_of_range();
            return this->_array[index];
        }
        const_reference at(size_type index) const
        {
            if(index >= this->_length)
                throw std::out_of_range();
            return this->_array[index];
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
            if(this->_array != nullptr)
            {
                delete[] this->_array;
                this->_length = 0;
            }
        }

        void assign(size_type length, const_reference value)
        {
            this->clear();
        }
        void assign(std::initializer_list<T> init)
        {
            this->clear();
        }
        template <class InputIterator>
        void assign(InputIterator begin, InputIterator end)
        {
            this->clear();
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
        iterator begin();
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept;
        
        iterator end();
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;
        
    public: //reverse iterator
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        
        reverse_iterator rend();
        const_reverse_iterator rend() const noexcept;
        const_reverse_iterator crend() const noexcept;
        
        class iterator
        {
        private:
            T* current;
        public:
            using Self = iterator;
        public:
            T(T*);
        public:
            iterator& operator
        };

        class const_iterator
        {
        private:
            T* current;
        public:
            using Self = iterator;
        public:
            T(T*);
        public:
            iterator& operator
        };
    };


}