namespace xstl
{
    template<class T>
    class sorted_array
    {
    public:
		using Self = sorted_array;

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
		sorted_array() = default;
		~sorted_array() = default;
	public:
		sorted_array(const Self&) = default;
		sorted_array(Self&&) = default;
		Self& operator=(const Self&) = default;
		Self& operator=(Self&&) = default;
	public:
		sorted_array(std::initializer_list<T>);
		template <class InputIterator>
		sorted_array(InputIterator begin, InputIterator end);
		sorted_array(size_type count, const value_type& value);
    };

    
}