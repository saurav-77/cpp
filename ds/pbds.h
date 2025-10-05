template <typename K, typename V, typename Comp>
using rb_tree = __gnu_pbds::tree<K, V, Comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

template <typename K, typename V>
using imap = rb_tree<K, V, less<K>>;

template <typename K>
using iset = rb_tree<K, __gnu_pbds::null_type, less<K>>;

template <typename K>
using imset = rb_tree<K, __gnu_pbds::null_type, less_equal<K>>;
