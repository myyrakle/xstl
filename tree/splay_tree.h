#include <iostream>

namespace xstl
{

	template <class T, class Compare = std::less<T>>
	class splay_tree
	{
	public:
		class iterator;
		class const_iterator;
		class reverse_iterator;
		class const_reverse_iterator;
		struct node_type;

		using key_type = T;
		using value_type = T;
		using size_type = size_t;
		using different_type = std::ptrdiff_t;
		using key_compare = Compare;
		using value_compare = Compare;
		using reference = value_type &;
		using const_reference = const value_type &;

		struct node_type
		{
			node_type *parent = nullptr; //부모 노드입니다.
			T value;
			node_type *left = nullptr;	//왼쪽 자식 노드입니다.
			node_type *right = nullptr; //오른쪽 자식 노드입니다.

			node_type() = default;
			~node_type() = default;
			node_type(const node_type &) = default;
			node_type(node_type &&) = default;
			node_type &operator=(const node_type &) = default;
			node_type &operator=(node_type &) = default;
			node_type(const key_type &);
			node_type(key_type &&);
		};

	private:
		void _rotate(node_type *); //전달되는 노드를 해당 노드의 부모 위치로 옮깁니다.
		void _splay(node_type *);  //

		node_type* get_lowest_left()
		{

		}

	public:
		node_type *root = nullptr;
		size_t node_count = 0;

	public:
		splay_tree() = default;
		virtual ~splay_tree();

	public:
		splay_tree(const splay_tree &) = default;
		splay_tree(splay_tree &&) = default;
		splay_tree &operator=(const splay_tree &) = default;
		splay_tree &operator=(splay_tree &&) = default;

	public: //capacity
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

	public: //modifiers
		void clear();
		void insert(const value_type &);
		//void insert(key_type&&);
		template <class... Args>
		void emplace(Args &&... args);
		void erase(iterator);

	public: //lookup
		size_type count(const value_type &key) const;
		iterator find(const value_type &key);
		const_iterator find(const value_type &key) const;
		bool contains(const value_type &);

	public:
		class iterator
        {
        private:
            node_type *current;

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
            iterator(const Self &) = default;
            iterator(Self &&) = default;
            Self &operator=(const Self &) = default;
            Self &operator=(Self &&) = default;

        public:
            iterator(node_type *p) : current(p)
            {
            }

        public: //move operator
            Self &operator++()
            {
                assert(current != nullptr);
                //??
                return *this;
            }
            Self operator++(int)
            {
                assert(current != nullptr);
                //??
                return *this;
            }
            Self &operator--()
            {
                assert(current != nullptr);
                //??
                return *this;
            }
            Self operator--(int)
            {
                assert(current != nullptr);
                //??
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
            bool operator==(const Self &other) const
            {
                return this->current == other.current;
            }
            bool operator!=(const Self &other) const
            {
                return this->current != other.current;
            }
        };

		iterator begin();
		iterator end();
		const_iterator cbegin() const;
		const_iterator cend() const;
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;
	};

	template <class T, class Compare>
	splay_tree<T, Compare>::~splay_tree()
	{
		this->clear();
	}

	template <class T, class Compare>
	void splay_tree<T, Compare>::clear()
	{
		//ToDo: 노드 정리
	}

	template <class T, class Compare>
	void splay_tree<T, Compare>::_rotate(splay_tree<T, Compare>::node_type *node)
	{
		node_type *parent = node->parent;
		node_type *b = nullptr;

		if (node == parent->left)
		{
			parent->left = b = node->right;
			node->right = parent;
		}
		else
		{
			parent->right = b = node->left;
			node->left = parent;
		}

		node->parent = parent->parent;
		parent->parent = node;

		if (b)
			b->parent = parent;

		(node->parent ? (parent == node->parent->left ? node->parent->left : node->parent->right)
					  : this->root) = node;
	}

	template <class T, class Compare>
	void splay_tree<T, Compare>::_splay(splay_tree<T, Compare>::node_type *node)
	{
		while (node->parent)
		{
			node_type *parent = node->parent;
			node_type *grand_parent = parent->parent;

			auto node_to__rotate = (node == parent->left) && (parent == grand_parent->left) ? parent : node;

			if (grand_parent)
				_rotate(node_to__rotate);

			_rotate(node);
		}
	}

	template <class T, class Compare>
	void splay_tree<T, Compare>::insert(const splay_tree<T, Compare>::value_type &value)
	{
		node_type *origin_root = this->root;
		node_type **ref;

		if (origin_root == nullptr) //최초삽입
		{
			root = new node_type(value);
			return;
		}

		while (true)
		{
			if (value == origin_root->value)
				return; //중복 배제

			else if (value < origin_root->value)
			{
				if (origin_root->left == nullptr)
				{
					ref = &origin_root->left;
					break;
				}
				origin_root = origin_root->left;
			}
			else
			{
				if (origin_root->right == nullptr)
				{
					ref = &origin_root->right;
					break;
				}
				origin_root = origin_root->right;
			}
		}
		node_type *x = new node_type(value);
		*ref = x;
		x->parent = origin_root;
		_splay(x);
	}

	template <class T, class Compare>
	bool splay_tree<T, Compare>::contains(const T &value)
	{
		node_type *origin_root = this->root;
		if (origin_root == nullptr)
			return false;

		while (origin_root != nullptr)
		{
			if (value == origin_root->value)
				break;
			if (value < origin_root->value)
			{
				if (origin_root->left == nullptr)
					break;
				origin_root = origin_root->left;
			}
			else
			{
				if (origin_root->right == nullptr)
					break;
				origin_root = origin_root->right;
			}
		}
		this->splay(origin_root);
		return value == origin_root->value;
	}

	template <class T, class Compare>
	size_t splay_tree<T, Compare>::size() const
	{
		return this->node_count;
	}

	template <class T, class Compare>
	bool splay_tree<T, Compare>::empty() const
	{
		return !this->node_count;
	}

	/*여기부터 node_type 정의부입니다.*/
	template <class T, class Compare>
	splay_tree<T, Compare>::node_type::node_type(const splay_tree<T, Compare>::key_type &value)
		: value(value)
	{
	}
	template <class T, class Compare>
	splay_tree<T, Compare>::node_type::node_type(splay_tree<T, Compare>::key_type &&value)
		: value(std::move(value))
	{
	}

} // namespace xstl