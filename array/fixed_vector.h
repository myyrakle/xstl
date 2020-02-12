#include <stdexcept>
#include <utility>

template <class T>
class fixed_vector
{
public:
    using Self = fixed_vector;
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
    T* array;
    size_type length;
public:
    fixed_vector(): array(nullptr), length(0)
    {}

    fixed_vector(size_type length): array(new T[length]), length(length)
    {}

    virtual ~fixed_vector()
    {
        if(this->array != nullptr)
            delete[] this->array;
    }

public:
    fixed_vector(const Self&);
    fixed_vector(Self&&);
    Self& operator=(const Self&);
    Self& operator=(Self&&);

public:
    reference operator[](size_type index)
    {
        return this->array[index];
    }
    const_reference operator[](size_type index) const
    {
        return this->array[index];
    }
    reference at(size_type index)
    {
        if(index >= this->length)
            throw std::out_of_range();
        return this->array[index];
    }
    const_reference at(size_type index) const
    {
        if(index >= this->length)
            throw std::out_of_range();
        return this->array[index];
    }

public:
    void clear() noexcept
    {
        if(this->array != nullptr)
            delete[] this->array;
        this->length = 0;
    }
};