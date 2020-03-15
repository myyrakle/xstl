#pragma once

#include <vector>
#include <algorithm>
#include <functional> //less

namespace xstl 
{
	template <class T, class Compare = std::less<T>, class Container=std::vector<T> >
	class heap;

	template <class T>
	using max_heap = heap<T, std::less<T>>;
	template <class T>
	using min_heap = heap<T, std::greater<T>>;

	template <class T, class Compare, class Container>
	class heap
	{
	public:
		using Self = heap;
	public:
		using container_type = Container;
		using value_type = typename Container::value_type;
		using size_type = typename std::vector<T>::size_type;
		using allocator_type = typename std::vector<T>::allocator_type;
		using difference_type = typename std::vector<T>::difference_type;
		using refernce = typename std::vector<T>::reference;
		using const_reference = typename std::vector<T>::const_reference;
		using pointer = typename std::vector<T>::pointer;
		using const_pointer = typename std::vector<T>::const_pointer;
		
	private:
		Container<value_type> datas;
	public:
		heap() = default;
		virtual ~heap() = default;
	public: //기본 생성/대입자
		heap(const heap&) = default;
		heap(heap&&) = default;
		heap& operator=(const heap&) = default;
		heap& operator=(heap&&) = default;

	public: //중괄호 초기치 대응
		heap(std::initializer_list<T> init) : datas(init)
		{
			this->make_heap();
		}
		heap& operator=(std::initializer_list<T> init)
		{
			datas = init;
			this->make_heap();
		}

	public: //vector와의 호환용
		heap(const std::vector<T>& vec) : datas(vec)
		{
			this->make_heap();
		}
		heap(std::vector<T>&& vec): datas(vec)
		{
			this->make_heap();
		}

	public: //vector와의 호환용
		operator const std::vector<T>&() const
		{
			return this->data;
		}

	public:
		std::vector<T> sorted() const
		{
			std::vector<T> clone = this->datas;
			std::sort_heap(clone.begin(), clone.end(), Compare());
			return clone;
		}

	public: //최대 힙을 기준으로, 최대값을 가져옵니다.
		const T& front() const
		{
			return datas.front();
		}

	public: //요소를 추가합니다.
		void push(const T& value)
		{
			datas.push_back(value);
			this->push_heap();
		}
		void push(T&& value)
		{
			datas.push_back(std::move(value));
			this->push_heap();
		}
		template <class ...Args>
		void emplace(Args&&... args)
		{
			datas.emplace_back(args...);
			this->push_heap();
		}

	public: //최대 힙을 기준으로, 최대값을 제거합니다.
		void pop()
		{
			std::pop_heap(datas.begin(), datas.end(), Compare());
			datas.pop_back();
		}

	public:
		void clear()
		{
			return datas.clear();
		}
		bool empty() const
		{
			return datas.empty();
		}
		bool not_empty() const
		{
			return !datas.empty();
		}
		size_t size() const
		{
			return datas.size();
		}
		size_t max_size() const
		{
			return datas.max_size();
		}

	private:
		void push_heap()
		{
			std::push_heap(datas.begin(), datas.end(), Compare());
		}
		void make_heap()
		{
			std::make_heap(datas.begin(), datas.end(), Compare());
		}
	};