// Type Traits Namespace
//
namespace type_traits {

	/*-------------------------- Integral Constant --------------------------*/
	template<class T, T v>
	struct integral_constant {
		static constexpr T value = v;
		using value_type = T;
		using type = integral_constant;
		constexpr operator value_type() const noexcept {
			return value;
		}
		constexpr value_type operator()() const noexcept {
			return value;
		}
	};

	/*-------------------------- Boolean Constant --------------------------*/
	template<bool B>
	using bool_constant = integral_constant<bool, B>;
	using false_type = bool_constant<false>;
	using true_type = bool_constant<true>;

	/*-------------------------- Type Identity --------------------------*/
	template <class T>
	struct type_identity {
		using type = T;
	};

	/*-------------------------- Is Same --------------------------*/
	template<class T, class U>
	struct is_same: false_type {};
	template<class T>
	struct is_same<T, T>: true_type {};
	// Helper Values
	template<class T, class U>
	inline constexpr bool is_same_v = is_same<T, U>::value;

	/*-------------------------- Is Reference --------------------------*/
	template <class T> struct is_reference: false_type {};
	template <class T> struct is_reference<T&>: true_type {};
	template <class T> struct is_reference < T&& > : true_type {};
	// Helper Values
	template<class T>
	inline constexpr bool is_reference_v = is_reference<T>::value;

	/*-------------------------- Is Constant --------------------------*/
	template<class T> struct is_const: false_type {};
	template<class T> struct is_const<const T>: true_type {};
	// Helper Values
	template<class T>
	inline constexpr bool is_const_v = is_const<T>::value;

	/*-------------------------- Is Function --------------------------*/
	template<class T>
	struct is_function : integral_constant <
		bool,
		!is_const_v<const T>&& !is_reference_v<T>
		> {};
	// Helper Values
	template<class T>
	inline constexpr bool is_function_v = is_function<T>::value;

	/*-------------------------- Remove Extent --------------------------*/
	template<class T>
	struct remove_extent {
		using type = T;
	};
	template<class T>
	struct remove_extent<T[]> {
		using type = T;
	};

	template<class T, std::size_t N>
	struct remove_extent<T[N]> {
		using type = T;
	};
	// Helper Types
	template<class T>
	using remove_extent_t = typename remove_extent<T>::type;

	/*-------------------------- Is L-Value Reference --------------------------*/
	template<class T> struct is_lvalue_reference     : false_type {};
	template<class T> struct is_lvalue_reference<T&> : true_type {};
	// Helper Values
	template<class T>
	inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

	/*-------------------------- Is R-Value Reference --------------------------*/
	template<class T> struct is_rvalue_reference: false_type {};
	template<class T> struct is_rvalue_reference < T&& > : true_type {};
	// Helper Values
	template<class T>
	inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

	/*-------------------------- Is Array --------------------------*/
	template<class T>
	struct is_array : false_type {};

	template<class T>
	struct is_array<T[]> : true_type {};

	template<class T, std::size_t N>
	struct is_array<T[N]> : true_type {};

	// Helper Values
	template<class T>
	inline constexpr bool is_array_v = is_array<T>::value;

	/*-------------------------- Remove Const Volatile (CV) --------------------------*/
	template<class T>
	struct remove_cv {
		using type = T;
	};
	template<class T>
	struct remove_cv<const T> {
		using type = T;
	};
	template<class T>
	struct remove_cv<volatile T> {
		using type = T;
	};
	template<class T>
	struct remove_cv<const volatile T> {
		using type = T;
	};
	// Remove Const
	template<class T> struct remove_const {
		using type = T;
	};
	template<class T> struct remove_const<const T> {
		using type = T;
	};
	// Remove Volatile
	template<class T> struct remove_volatile {
		using type = T;
	};
	template<class T> struct remove_volatile<volatile T> {
		using type = T;
	};
	// Helper Types
	template<class T>
	using remove_cv_t = typename remove_cv<T>::type;
	template<class T>
	using remove_const_t = typename remove_const<T>::type;
	template<class T>
	using remove_volatile_t = typename remove_volatile<T>::type;

	/*-------------------------- Add Const Volatile (CV) --------------------------*/
	template<class T> struct add_cv {
		using type = const volatile T;
	};
	template<class T> struct add_const {
		using type = const T;
	};
	template<class T> struct add_volatile {
		using type = volatile T;
	};
	// Helper Types
	template<class T>
	using add_cv_t = typename add_cv<T>::type;
	template<class T>
	using add_const_t = typename add_const<T>::type;
	template<class T>
	using add_volatile_t = typename add_volatile<T>::type;

	/*-------------------------- Remove Reference --------------------------*/
	template <typename T>
	struct remove_reference {
		using type = T;
	};
	template <typename T>
	struct remove_reference<T&> {
		using type = T;
	};
	template <typename T>
	struct remove_reference < T&& > {
		using type = T;
	};
	// Helper Types
	template <typename  T>
	using remove_reference_t = typename remove_reference<T>::type;

	/*-------------------------- Add Reference --------------------------*/
	template<class T>
	auto try_add_lvalue_reference(int) -> type_identity<T&>;
	template<class T>
	auto try_add_lvalue_reference(...) -> type_identity<T>;
	template <class T>
	auto try_add_rvalue_reference(int) -> type_identity < T&& >;
	template <class T>
	auto try_add_rvalue_reference(...) -> type_identity<T>;

	template <class T>
	struct add_lvalue_reference : decltype(try_add_lvalue_reference<T>(0)) {};

	template <class T>
	struct add_rvalue_reference : decltype(try_add_rvalue_reference<T>(0)) {};

	/*-------------------------- Conditional --------------------------*/
	template<bool B, class T, class F>
	struct conditional {
		using type = T;
	};
	template<class T, class F>
	struct conditional<false, T, F> {
		using type = F;
	};
	// Helper Types
	template<bool B, class T, class F>
	using conditional_t = typename conditional<B, T, F>::type;

	/*-------------------------- Enable If --------------------------*/
	template<bool B, class T = void>
	struct enable_if {};
	template<class T>
	struct enable_if<true, T> {
		using type = T;
	};
	// Helper Types
	template <bool B, class T = void>
	using enable_if_t = typename enable_if<B, T>::type;

	/*-------------------------- Is Void --------------------------*/
	template<class T>
	struct is_void : is_same<void, remove_cv_t<T>> {};
	// Helper Values
	template<class T>
	inline constexpr bool is_void_v = is_void<T>::value;

	/*-------------------------- Is Floating Point --------------------------*/
	template<class T>
	struct is_floating_point :
		integral_constant < bool,
		is_same_v<float, remove_cv_t<T>> || is_same_v<double, remove_cv_t<T>> || is_same_v<long double, remove_cv_t<T> >> {};
	// Helper Values
	template<class T>
	inline constexpr bool is_floating_point_v = is_floating_point<T>::value;

	/*-------------------------- Add Pointer --------------------------*/
	template <class T>
	auto try_add_pointer(int) -> type_identity<remove_reference_t<T>*>;
	template <class T>
	auto try_add_pointer(...) -> type_identity<T>;
	template <class T>
	struct add_pointer : decltype(try_add_pointer<T>(0)) {};
	// Helper Types
	template<class T>
	using add_pointer_t = typename add_pointer<T>::type;

	/*-------------------------- Decay --------------------------*/
	template<class T>
	struct decay {
	  private:
		using U = remove_reference_t<T>;
	  public:
		using type = conditional_t <
		             is_array_v<U>,
		             remove_extent_t<U>*,
		             conditional_t <
		             is_function_v<U>,
		             add_pointer_t<U>,
		             remove_cv_t<U>
		             >>;
	};
	// Helper Types
	template<class T>
	using decay_t = typename decay<T>::type;

	/*-------------------------- Void Type --------------------------*/
	template<class...>
	using void_t = void;

	/*-------------------------- Conjunction --------------------------*/
	template<class...>struct conjunction: true_type {};
	template<class _Ty> struct conjunction<_Ty>: _Ty {};
	template<class Head, class... Tail>
	struct conjunction<Head, Tail...> : conditional_t<bool(Head::value), conjunction<Tail...>, Head> {};
	// Helper Values
	template<class... Ty>
	inline constexpr bool conjunction_v = conjunction<Ty...>::value;

	/*-------------------------- Disjunction --------------------------*/
	template<class...> struct disjunction : false_type {};
	template<class Head> struct disjunction<Head> : Head {};
	template<class Head, class... Tail>
	struct disjunction<Head, Tail...> : conditional_t<bool(Head::value), Head, disjunction<Tail...>>  {};
	// Helper Values
	template<class... Ty>
	inline constexpr bool disjunction_v = disjunction<Ty...>::value;

	/*-------------------------- Negation --------------------------*/
	template<class Ty>
	struct negation : bool_constant < !bool(Ty::value) > {};
	// Helper Values
	template<class Ty>
	inline constexpr bool negation_v = negation<Ty>::value;

}; //namespace type_traits