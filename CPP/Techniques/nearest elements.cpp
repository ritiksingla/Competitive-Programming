// Nearest greater/smaller elements
//
// Nearest greater/smaller than equal to elements
// replace with equal to sign for strictly smaller/greater.
vector<int>rge(n, -1), lge(n, -1), rse(n, -1), lse(n, -1);
// Nearest greater from the left
for (int i = 0; i < n; i++) {
    while (!st.empty() && a[st.back()] < a[i]) {
        st.pop_back();
    }
    if (!st.empty()) {
        lge[i] = st.back();
    }
    st.push_back(i);
}
st.clear();
// Nearest smaller from the left
for (int i = 0; i < n; i++) {
    while (!st.empty() && a[st.back()] > a[i]) {
        st.pop_back();
    }
    if (!st.empty()) {
        lse[i] = st.back();
    }
    st.push_back(i);
}
st.clear();
// Nearest greater from the right
for (int i = n - 1; i >= 0; i--) {
    while (!st.empty() && a[st.back()] < a[i]) {
        st.pop_back();
    }
    if (!st.empty()) {
        rge[i] = st.back();
    }
    st.push_back(i);
}
st.clear();
// Nearest smaller from the right
for (int i = n - 1; i >= 0; i--) {
    while (!st.empty() && a[st.back()] > a[i]) {
        st.pop_back();
    }
    if (!st.empty()) {
        rse[i] = st.back();
    }
    st.push_back(i);
}
st.clear();
