
/*
    find_by_order(index) -> iterator pointing to index (0-based)
    order_of_key(key) -> no. of elements strictly smaller than key
*/

template <typename K, typename V, typename Comp>
using rb_tree = __gnu_pbds::tree<K, V, Comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

template <typename K, typename V>
using imap = rb_tree<K, V, less<K>>;  // indexed map

template <typename K>
using iset = rb_tree<K, __gnu_pbds::null_type, less<K>>;  // indexed set

template <typename K>
using imset = rb_tree<K, __gnu_pbds::null_type, less_equal<K>>;  // indexed multiset
