// Tensor
//
template<typename T, int NDIMS> struct tensor_view {
    static_assert(NDIMS >= 0, "NDIMS must be non_negative");

protected:
    array<int, NDIMS>shape;
    array<int, NDIMS>strides;
    T*data;

    tensor_view(array<int, NDIMS>shape_, array<int, NDIMS>strides_, T*data_): shape(shape_), strides(strides_), data(data_) {}

public:
    tensor_view(): shape( {0}), strides({0}), data(nullptr) {}

protected:
    int flatten_index(array<int, NDIMS> idx) const {
        int res{};
        for (int i = 0; i < NDIMS; i++) {
            assert(0 <= idx[i] && idx[i] < shape[i]);
            res += idx[i] * strides[i];
        }
        return res;
    }
    // int flatten_index_checked(array<int, NDIMS> idx) const {
    //     int res = 0;
    //     for (int i = 0; i < NDIMS; i++) {
    //         assert(0 <= idx[i] && idx[i] < shape[i]);
    //         res += idx[i] * strides[i];
    //     }
    //     return res;
    // }

public:

    T& operator[](array<int, NDIMS> idx) const {
        return data[flatten_index(idx)];
    }

    T& at(array<int, NDIMS> idx) const {
        return data[flatten_index(idx)];
    }

    // template <int D = NDIMS>
    // enable_if_t < (0 < D), tensor_view < T, NDIMS - 1 >> operator[] (int idx) const {
    //     array < int, NDIMS - 1 > nshape; copy(shape.begin() + 1, shape.end(), nshape.begin());
    //     array < int, NDIMS - 1 > nstrides; copy(strides.begin() + 1, strides.end(), nstrides.begin());
    //     T* ndata = data + (strides[0] * idx);
    //     return tensor_view < T, NDIMS - 1 > (nshape, nstrides, ndata);
    // }
    // template <int D = NDIMS>
    // enable_if_t < (0 < D), tensor_view < T, NDIMS - 1 >> at(int idx) const {
    //     assert(0 <= idx && idx < shape[0]);
    //     return operator[](idx);
    // }

    // template <int D = NDIMS>
    // enable_if_t<(0 == D), T&> operator * () const {
    //     return *data;
    // }

    template <typename U, int D> friend struct tensor_view;
    template <typename U, int D> friend struct tensor;
};

template<typename T, int NDIMS> struct tensor {
    static_assert(NDIMS >= 0, "NDIMS must be non_negative");

protected:
    array<int, NDIMS> shape;
    array<int, NDIMS> strides;
    int len;
    T* data;

public:
    tensor(): shape( {0}), strides({0}), len(0), data(nullptr) {}

    // t = 0 by default if not passed
    explicit tensor(array<int, NDIMS> shape_, const T&t = T()) {
        // Depth first, height second , width third rule
        shape = shape_;
        strides[NDIMS - 1] = 1;
        for (int i = NDIMS - 2; i >= 0; i--) {
            strides[i] = strides[i + 1] * shape[i + 1];
        }
        // Flatten tensor size
        len = strides[0] * shape[0];
        data = new T[len];
        fill(data, data + len, t);
    }
    // Simple copy constructor (l value reference)
    tensor(const tensor &o): shape(o.shape), strides(o.strides), len(o.len), data(new T[len]) {
        for (int i = 0; i < len; ++i) {
            data[i] = o.data[i];
        }
    }

    // = overloaded with rvalue reference
    tensor&    operator = (tensor&& o ) noexcept {
        swap(shape, o.shape);
        swap(strides, o.strides);
        swap(len, o.len);
        swap(data, o.data);
        return *this;
    }

    // Simple copy constructor (r value reference)
    // First call default constructor then use prefect forwarding
    tensor(tensor&& o) : tensor() {
        *this = move(o);
    }

    tensor& operator = (const tensor& o) {
        return *this = tensor(0);
    }

    ~tensor() { delete[] data; }

    using view_t = tensor_view<T, NDIMS>;

    view_t view() {
        return view_t(shape, strides, data);
    }
    operator view_t() {
        return view();
    }

    using const_view_t = tensor_view<const T, NDIMS>;
    const_view_t view() const {
        return tensor_view<const T, NDIMS>(shape, strides, data);
    }
    operator const_view_t() const {
        return view();
    }

    T& operator[] (std::array<int, NDIMS> idx) { return view()[idx]; }
    T& at(std::array<int, NDIMS> idx) { return view().at(idx); }
    const T& operator[] (std::array<int, NDIMS> idx) const { return view()[idx]; }
    const T& at(std::array<int, NDIMS> idx) const { return view().at(idx); }

    // template <int D = NDIMS>
    // std::enable_if_t < (0 < D), tensor_view < T, NDIMS - 1 >> operator[] (int idx) {
    //     return view()[idx];
    // }
    // template <int D = NDIMS>
    // std::enable_if_t < (0 < D), tensor_view < T, NDIMS - 1 >> at(int idx) {
    //     return view().at(idx);
    // }

    // template <int D = NDIMS>
    // std::enable_if_t < (0 < D), tensor_view < const T, NDIMS - 1 >> operator[] (int idx) const {
    //     return view()[idx];
    // }
    // template <int D = NDIMS>
    // std::enable_if_t < (0 < D), tensor_view < const T, NDIMS - 1 >> at(int idx) const {
    //     return view().at(idx);
    // }

    // template <int D = NDIMS>
    // std::enable_if_t<(0 == D), T&> operator * () {
    //     return *view();
    // }
    // template <int D = NDIMS>
    // std::enable_if_t<(0 == D), const T&> operator * () const {
    //     return *view();
    // }
};
