#pragma once

#include <vector>
#include <algorithm>
#include <functional> //less

namespace xstl 
{
	template <class T, class Compare = std::less<T>>
	class heap;

	template <class T>
	using max_heap = heap<T, std::less<T>>;
	template <class T>
	using min_heap = heap<T, std::greater<T>>;

	template <class T, class Compare>
	class heap
	{
	public:
		using const_iterator = typename std::vector<T>::const_iterator;
		using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;
		using value_type = typename std::vector<T>::value_type;
		using size_type = typename std::vector<T>::size_type;
		using allocator_type = typename std::vector<T>::allocator_type;
		using difference_type = typename std::vector<T>::difference_type;
		using refernce = typename std::vector<T>::reference;
		using const_reference = typename std::vector<T>::const_reference;
		using pointer = typename std::vector<T>::pointer;
		using const_pointer = typename std::vector<T>::const_pointer;
		
	public:
		heap() = default;
		virtual ~heap() = default;
	public: //�⺻ ����/������
		heap(const heap&) = default;
		heap(heap&&) = default;
		heap& operator=(const heap&) = default;
		heap& operator=(heap&&) = default;

	public: //�߰�ȣ �ʱ�ġ ����
		heap(std::initializer_list<T> init);
		heap& operator=(std::initializer_list<T> init);

	public: //vector���� ȣȯ��
		heap(const std::vector<T>& vec);
		heap(std::vector<T>&& vec);

	public: //vector���� ȣȯ��
		operator const std::vector<T>&() const;

	public:
		std::vector<T> sorted_vector() const;

	public: //�ִ� ���� ��������, �ִ밪�� �����ɴϴ�.
		const T& front() const;

	public: //��Ҹ� �߰��մϴ�.
		void push(const T& value);
		void push(T&& value);
		template <class ...Args>
		void emplace(Args&&... args);

	public: //�ִ� ���� ��������, �ִ밪�� �����մϴ�.
		void pop();

	public:
		void clear(); //���� �ʱ�ȭ�մϴ�.
		bool empty() const; //������� true�� ��ȯ�մϴ�.
		bool not_empty() const; //������� ������ true�� ��ȯ�մϴ�.
		size_t size() const; //���� ũ�⸦ ��ȯ�մϴ�.
		size_t max_size() const;
		void reserve(size_t);
		size_t capacity() const;
		void shrink_to_fit();

	public: //�ݺ����Դϴ�.
		const_iterator begin() const;
		const_iterator end() const;
		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;

	private:
		void push_heap();
		void make_heap();

	private:
		std::vector<T> datas;
	};

	//�ʱ�ȭ �����
	template<class T, class Compare>
	heap<T, Compare>::heap(std::initializer_list<T> init) : datas(init)
	{
		this->make_heap();
	}
	template<class T, class Compare>
	heap<T, Compare>& heap<T, Compare>::operator=(std::initializer_list<T> init)
	{
		datas = init;
		this->make_heap();
	}
	template<class T, class Compare>
	heap<T, Compare>::heap(const std::vector<T>& vec) : datas(vec)
	{
		this->make_heap();
	}
	template<class T, class Compare>
	heap<T, Compare>::heap(std::vector<T>&& vec) : datas(vec)
	{
		this->make_heap();
	}

	template<class T, class Compare>
	inline heap<T, Compare>::operator const std::vector<T>&() const
	{
		return this->data;
	}


	template<class T, class Compare>
	inline std::vector<T> heap<T, Compare>::sorted_vector() const
	{
		std::vector<T> clone = this->datas;
		std::sort_heap(clone.begin(), clone.end(), Compare());
		return clone;
	}


	template<class T, class Compare>
	inline const T& heap<T, Compare>::front() const
	{
		return datas.front();
	}

	template<class T, class Compare>
	inline void heap<T, Compare>::push(const T& value)
	{
		datas.push_back(value);
		this->push_heap();
	}

	template<class T, class Compare>
	inline void heap<T, Compare>::push(T&& value)
	{
		datas.push_back(std::move(value));
		this->push_heap();
	}

	template<class T, class Compare>
	template<class ...Args>
	inline void heap<T, Compare>::emplace(Args && ...args)
	{
		datas.emplace_back(args...);
		this->push_heap();
	}

	template<class T, class Compare>
	inline void heap<T, Compare>::pop()
	{
		std::pop_heap(datas.begin(), datas.end(), Compare());
		datas.pop_back();
	}

	template<class T, class Compare>
	inline void heap<T, Compare>::clear()
	{
		return datas.clear();
	}

	template<class T, class Compare>
	inline bool heap<T, Compare>::empty() const
	{
		return datas.empty();
	}

	template<class T, class Compare>
	inline bool heap<T, Compare>::not_empty() const
	{
		return !datas.empty();
	}

	template<class T, class Compare>
	inline size_t heap<T, Compare>::size() const
	{
		return datas.size();
	}

	template<class T, class Compare>
	inline size_t heap<T, Compare>::max_size() const
	{
		return datas.max_size();
	}

	template<class T, class Compare>
	inline void heap<T, Compare>::reserve(size_t size)
	{
		datas.reserve(size);
	}

	template<class T, class Compare>
	inline size_t heap<T, Compare>::capacity() const
	{
		return datas.capacity();
	}

	template<class T, class Compare>
	inline void heap<T, Compare>::shrink_to_fit()
	{
		datas.shrink_to_fit();
	}

	template<class T, class Compare>
	inline typename heap<T, Compare>::const_iterator heap<T, Compare>::begin() const
	{
		return datas.cbegin();
	}

	template<class T, class Compare>
	inline typename heap<T, Compare>::const_iterator heap<T, Compare>::end() const
	{
		return datas.cend();
	}

	template<class T, class Compare>
	inline typename heap<T, Compare>::const_reverse_iterator heap<T, Compare>::rbegin() const
	{
		return datas.crbegin();
	}

	template<class T, class Compare>
	inline typename heap<T, Compare>::const_reverse_iterator heap<T, Compare>::rend() const
	{
		return datas.crend();
	}

	template<class T, class Compare>
	inline void heap<T, Compare>::push_heap()
	{
		std::push_heap(datas.begin(), datas.end(), Compare());
	}

	template<class T, class Compare>
	inline void heap<T, Compare>::make_heap()
	{
		std::make_heap(datas.begin(), datas.end(), Compare());
	}
}