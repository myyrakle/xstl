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
		using size_type = typename Container::size_type;
		using refernce = typename Container::reference;
		using const_reference = typename Container::const_reference;
		using pointer = typename Container::pointer;
		using const_pointer = typename Container::const_pointer;
		
	private:
		Container _container;
	private:
		void _push_heap()
		{
			std::push_heap(_container.begin(), _container.end(), Compare());
		}
		void _make_heap()
		{
			std::make_heap(_container.begin(), _container.end(), Compare());
		}
	
	public:
		heap() = default;
		virtual ~heap() = default;
	public: //기본 생성/대입자
		heap(const Self&) = default;
		heap(Self&&) = default;
		Self& operator=(const Self&) = default;
		Self& operator=(Self&&) = default;

	public: //constructor
		heap(std::initializer_list<value_type> init) : _container(init)
		{
			this->_make_heap();
		}
		template<class InputIterator>
		heap(InputIterator begin, InputIterator end): _container(begin, end)
		{
			this->_make_heap();
		}
		heap(size_type count, const_reference value): _container(count, value)
		{
			this->_make_heap();
		}

	public:
		heap& operator=(std::initializer_list<value_type> init)
		{
			_container = init;
			this->_make_heap();
		}

	public: //vector와의 호환용
		heap(const Container& vec) : _container(vec)
		{
			this->_make_heap();
		}
		heap(Container&& vec): _container(vec)
		{
			this->_make_heap();
		}

	public: //vector와의 호환용
		operator Container&() const
		{
			return this->_container;
		}

	public:
		Container sorted() const
		{
			Container clone = this->_container;
			std::sort_heap(clone.begin(), clone.end(), Compare());
			return clone;
		}

	public: //최대 힙을 기준으로, 최대값을 가져옵니다.
		const_reference front() const
		{
			return _container.front();
		}

	public: //요소를 추가합니다.
		void push(const_reference value)
		{
			_container.push_back(value);
			this->push_heap();
		}
		void push(value_type&& value)
		{
			_container.push_back(std::move(value));
			this->push_heap();
		}
		template <class ...Args>
		void emplace(Args&&... args)
		{
			_container.emplace_back(std::forward<Args>(args)...);
			this->push_heap();
		}

	public: //최대 힙을 기준으로, 최대값을 제거합니다.
		void pop()
		{
			std::pop_heap(_container.begin(), _container.end(), Compare());
			_container.pop_back();
		}

	public:
		void clear() noexcept
		{
			return _container.clear();
		}
		bool empty() const noexcept
		{
			return _container.empty();
		}
		bool not_empty() const noexcept
		{
			return !_container.empty();
		}
		size_t size() const noexcept
		{
			return _container.size();
		}
		size_t max_size() const noexcept
		{
			return _container.max_size();
		}
	};
}