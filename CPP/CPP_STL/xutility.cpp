namespace xutility {

	/*-------------------------- Get First Parameter --------------------------*/
	template <class T> struct get_first_parameter {};
	template <template <class, class...> class T, class Head, class... Tail>
	struct get_first_parameter<T<Head, Tail...>> { // given T<Head, Tail...>, extract Head
		using type = Head;
	};

	/*-------------------------- Replace First Parameter --------------------------*/
	template <class Newhead, class T> struct replace_first_parameter {};
	template <class Newhead, template <class, class...> class T, class Head, class... Tail>
	struct replace_first_parameter<Newhead, T<Head, Tail...>> { // given T<Head, Tail...>, replace Head
		using type = T<Newhead, Tail...>;
	};

	/*-------------------------- Get Element Type --------------------------*/
	// primary template handles types that have no nested ::element_type member
	template <class T, class = void>
	struct get_element_type {
		using type = typename get_first_parameter<T>::type;
	};
	// specialization recognizes types that do have a nested ::element_type member
	template <class T>
	struct get_element_type<T, std::void_t<typename T::element_type>> {
		using type = typename T::element_type;
	};
	template<class T>
	using get_element_type_t = typename get_element_type<T>::type;

	/*-------------------------- Get Ptr Difference Type --------------------------*/
	template <class T, class = void>
	struct get_ptr_difference_type {
		using type = std::ptrdiff_t;
	};
	template <class T>
	struct get_ptr_difference_type<T, std::void_t<typename T::difference_type>> {
		using type = typename T::difference_type;
	};
	template<class T>
	using get_ptr_difference_type_t = typename get_ptr_difference_type<T>::type;

	/*-------------------------- Get Rebind Alias --------------------------*/
	template <class T, class _Other, class = void>
	struct get_rebind_alias {
		using type = typename replace_first_parameter<_Other, T>::type;
	};

	template <class T, class _Other>
	struct get_rebind_alias<T, _Other, std::void_t<typename T::template rebind<_Other>>> {
	            using type = typename T::template rebind<_Other>;
	                                                    };
	template <class T, class _Other>
	using get_rebind_alias_t = typename get_rebind_alias<T, _Other>::type;

	/*-------------------------- Pointer Traits --------------------------*/
	template<class T>
	struct pointer_traits {
		using pointer = T;
		using element_type = get_element_type_t<T>;
		using difference_type = get_ptr_difference_type_t<T>;

		template <class _Other>
		using rebind = get_rebind_alias_t<T, _Other>;

		using ref_type = type_traits::conditional_t<type_traits::is_void_v<element_type>, char, element_type>& ;
	};

}; // namespace xutility