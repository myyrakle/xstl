

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
    };
}