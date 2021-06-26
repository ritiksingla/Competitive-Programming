namespace iterator_traits {

	/*-------------------------- Empty class types used to indicate iterator categories --------------------------*/
	struct input_iterator_tag {};

	struct output_iterator_tag {};

	struct forward_iterator_tag : input_iterator_tag {};

	struct bidirectional_iterator_tag : forward_iterator_tag {};

	struct random_access_iterator_tag : bidirectional_iterator_tag {};

	struct contiguous_iterator_tag : random_access_iterator_tag {};

	/*-------------------------- Iterator Adaptors --------------------------*/

	/*-------------------------- 1. Back Insert Iterator --------------------------*/
	/* back_insert_iterator is a LegacyOutputIterator that appends to a container for which it was constructed.
	The container's push_back() member function is called whenever the iterator (whether dereferenced or not) is assigned to.
	Incrementing the back_insert_iterator is a no-op.*/
	template <class _Container>
	class back_insert_iterator {
	  public:
		using iterator_category = output_iterator_tag;
		using value_type = void;
		using pointer = void;
		using reference = void;
		using container_type = _Container;
		using difference_type = void;

		// Constructs a new back_insert_iterator
		inline explicit back_insert_iterator(_Container& _Cont) noexcept : container(std::addressof(_Cont)) {}

		// inserts an object into the associated container
		inline back_insert_iterator& operator = (const typename _Container::value_type& _Val) {
			container->push_back(_Val);
			return *this;
		}

		inline back_insert_iterator& operator = (typename _Container::value_type&& _Val) {
			container->push_back(std::move(_Val));
			return *this;
		}

		// No operations on {*, ++, ++(int)}
		[[nodiscard]] inline back_insert_iterator& operator * () noexcept {
			return *this;
		}

		inline back_insert_iterator& operator++() noexcept {
			return *this;
		}

		inline back_insert_iterator operator++(int) noexcept {
			return *this;
		}

	  protected:
		_Container* container = nullptr;
	};

	/*-------------------------- Back Inserter (Helper) --------------------------*/
	template <class _Container>
	[[nodiscard]] inline back_insert_iterator<_Container> back_inserter(_Container& _Cont) noexcept {
		return back_insert_iterator<_Container>(_Cont);
	}

	/*-------------------------- 2. Front Insert Iterator --------------------------*/
	/* front_insert_iterator is an LegacyOutputIterator that prepends elements to a container for which it was constructed.
	The container's push_front() member function is called whenever the iterator (whether dereferenced or not) is assigned to.
	Incrementing the front_insert_iterator is a no-op*/
	template <class _Container>
	class front_insert_iterator {
	  public:
		using iterator_category = output_iterator_tag;
		using value_type = void;
		using pointer = void;
		using reference = void;
		using container_type = _Container;
		using difference_type = void;

		inline explicit front_insert_iterator(_Container& _Cont) : container(std::addressof(_Cont)) {}

		inline front_insert_iterator& operator = (const typename _Container::value_type& _Val) {
			container->push_front(_Val);
			return *this;
		}

		inline front_insert_iterator& operator = (typename _Container::value_type&& _Val) {
			container->push_front(std::move(_Val));
			return *this;
		}

		// No operations on {*, ++, ++(int)}
		[[nodiscard]] inline front_insert_iterator& operator*() {
			return *this;
		}

		inline front_insert_iterator& operator++() {
			return *this;
		}

		inline front_insert_iterator operator++(int) {
			return *this;
		}

	  protected:
		_Container* container = nullptr;
	};

	/*-------------------------- Front Insert (Helper) --------------------------*/
	template <class _Container>
	[[nodiscard]] inline front_insert_iterator<_Container> front_inserter(_Container& _Cont) {
		return front_insert_iterator<_Container>(_Cont);
	}

	/*-------------------------- 3. Insert Iterator --------------------------*/
	/* insert_iterator is a LegacyOutputIterator that inserts elements into a container for which it was constructed,
	at the position pointed to by the supplied iterator. The container's insert() member function is called whenever
	the iterator (whether dereferenced or not) is assigned to. Incrementing the insert_iterator is a no-op*/
	template <class _Container>
	class insert_iterator { // wrap inserts into container as output iterator
	  public:
		using iterator_category = output_iterator_tag;
		using value_type = void;
		using pointer = void;
		using reference = void;
		using container_type = _Container;
		using difference_type = void;

		inline insert_iterator(_Container& _Cont, typename _Container::iterator _Where)
			: container(std::addressof(_Cont)), iter(_Where) {}

		inline insert_iterator& operator = (const typename _Container::value_type& _Val) {
			// insert into container and increment stored iterator
			iter = container->insert(iter, _Val);
			++iter;
			return *this;
		}

		inline insert_iterator& operator = (typename _Container::value_type&& _Val) {
			iter = container->insert(iter, std::move(_Val));
			++iter;
			return *this;
		}

		[[nodiscard]] inline insert_iterator& operator*() {
			return *this;
		}

		inline insert_iterator& operator++() {
			return *this;
		}

		inline insert_iterator& operator++(int) {
			return *this;
		}

	  protected:
		_Container* container = nullptr;
		typename _Container::iterator iter{};
	};

	/*-------------------------- Inserter (Helper) --------------------------*/
	template <class _Container>
	[[nodiscard]] inline insert_iterator<_Container> inserter(_Container& _Cont, typename _Container::iterator _Where) {
		return insert_iterator<_Container>(_Cont, _Where);
	}

}; // namespace iterator_traits