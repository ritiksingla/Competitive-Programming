#include <bits/stdc++.h>
using namespace std;
// --------------------------------- Macros ---------------------------------------------------------
using ll = long long;
using ld = long double;
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define eb emplace_back
#define in insert
#define rep(i,n) for(int i=0;i<(n);i++)
#define forn(i,a,b) for(int i=(a);i<=(b);i++)
#define revforn(i,a,b) for(int i=(a);i>=(b);i--)
#define trav(a,x) for(auto & a : x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
#define TT ll t;cin>>t;while (t--)
// --------------------------------------- Debug -----------------------------------------------------
template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "vector:\t";
    typename vector<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++)
        os << *it << " ";
    return os;
}
void show(ll *a, ll m, ll n)
{
    cout << "2D Array\n";
    rep(i, m)
    rep(j, n)
    cout << *((a + i * n) + j) << " \n"[j == n - 1];
}
template<typename T>
ostream &operator<<(ostream &os, const set<T> &v)
{
    os << "set: ";
    typename set<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++ )
        os << *it << " ";
    return os;
}
template<typename T>
ostream &operator<<(ostream &os, const multiset<T> &v)
{
    os << "multiset:\t";
    typename multiset<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++ )
        os << *it << " ";
    return os;
}
template<typename T>void show(T q)
{
    cout << "\npriority_queue:\t";
    while (!q.empty())
    {
        cout << q.top() << " ";
        q.pop();
    }
    cout << '\n';
}
template<typename F, typename str>
ostream &operator<<(ostream &os, const map<F, str> &v)
{
    os << "map:\t";
    typename map<F, str>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++)
        os << it->ff << "->" << it->ss << " | ";
    return os;
}
template<typename F, typename str>
ostream &operator<<(ostream &os, const unordered_map<F, str> &v)
{
    os << "unordered_map: ";
    typename unordered_map<F, str>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++)
        os << it->ff << "->" << it->ss << " | ";
    return os;
}
template <typename A>
string to_string(vector<A> &v)
{
    string s = "";
    s += "(";
    for(A &x : v)s += to_string(x) + " ";
    s += ")";
    return s;
}
string to_string(bool b)
{
    return (b ? "true" : "false");
}
template <typename A, typename B>
string to_string(pair<A, B> p)
{
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
template <typename T>
void show(T arr, ll n)
{
    cout << "\narray :\t";
    rep(i, n)
    {
        cout << arr[i] << " ";
    }
    cerr << '\n';
}
string to_string(const string s, ll x1 = 0, ll x2 = 1e9)
{
    return '"' + ((x1 < s.size()) ? s.substr(x1, x2 - x1 + 1) : "") + '"';
}
string to_string(const char *s)
{
    return to_string((string) s);
}
void debug()
{
    cerr << '\n';
}
template<typename Head, typename... Tail> void debug(Head H, Tail... T)
{
    cerr << to_string(H) << " | ";
    debug(T...);
}
#define debug(...) cerr<<"["<<#__VA_ARGS__<<"] : "; debug(__VA_ARGS__);
void console()
{
    cout << '\n';
}
template<typename Head, typename... Tail>
void console(Head H, Tail ... T)
{
    cout << to_string(H) << " | ";
    console(T...);
}
#define console(...) cout<<"["<<#__VA_ARGS__<<"] : "; console(__VA_ARGS__);

// ---------------------------------------- Policy Based Data Structures -------------------------
#include <ext/pb_ds/assoc_container.hpp>
/*
template<
      typename Key, // Key type
      typename Mapped, // Mapped-policy
      typename Cmp_Fn = std::less<Key>, std::less_equal<Key> // Key comparison functor
      typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
      template<
      typename Const_Node_Iterator,
      typename Node_Iterator,
      typename Cmp_Fn_,
      typename Allocator_>
      class Node_Update = null_node_update, // A policy for updating node invariants
      typename Allocator = std::allocator<char> > // An allocator type
      class tree;

      s.find_by_order(x): zero based xth element in set
      s.order_of_key(x): number of items strictly smaller than x
*/
template<typename T, typename Comp = less<T>, typename V = __gnu_pbds::null_type >
using ordered_set = __gnu_pbds::tree <
                    T, V, Comp,
                    __gnu_pbds::rb_tree_tag,
                    __gnu_pbds::tree_order_statistics_node_update
                    >;
// ------------------------------------------------------------------------------------------------
const int inf = 1e9;
const ll INF = (inf * 1ll * inf);
const int mod = (119 << 23) + 1;
int main()
{
    fastio;
    ordered_set<int>s; // ordered_set<int,less_equal<int> >multi_set;
    s.insert(12);
    s.insert(1);
    s.insert(1);
    s.insert(14);
    s.insert(51);
    s.insert(164);
    debug(s.order_of_key(51), *s.find_by_order(1));
    vpi x;
    x.eb(1, 2);
    x.eb(31, 222);
    x.eb(14, 25);
    trav(it, x)
    {
        debug(it.ff, it.ss);
    }
    return 0;
}
