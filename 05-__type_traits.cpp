// 这里想要响应真假性质的对象，可以利用结果来进行参数推导，而不是只是表示真假的bool
struct __true_type {};
struct __false_type {};

template <class type>
struct __type_traits {
  // 这个成员，它通知有能力自动将 __type_traits 特化的编译器
  // 告诉编译器这个__type_traits template是特殊的
  // 目的是：为了确保万一编译器也使用一个名为__type_traits但与此处定义没有任何关联的template的时候仍然能够顺利进行
  typedef __true_type this_dummy_member_must_be_first;

  // 因为编译器可能会自动为各型别产生专属的__type_traits特化版本
  // 所以需要遵循以下条件：
  // 可以重新排列以下的成员次序
  // 可以移除任何成员
  // 不可以将以下成员重新命名却没有改变编译器中对应名称
  // 新加入的成员会被视为一般成员，但可以在编译器中添加适当的支持
  typedef __false_type has_trival_default_constructor;
  typedef __false_type has_trival_copy_constructor;
  typedef __false_type has_trival_assignment_operator;
  typedef __false_type has_trival_destructor;
  typedef __false_type is_POD_type;
  // SGI把所有内嵌型别都定义为__false_type
  // 这是因为SGI定义出最保守的值，然后再针对每个标量型别设计出合适的特化版本
};

/*
以下是<type_traits.h>对所有C++标量型别所定义的__type_traits特化版本
  针对基本型别:char、signed char、unsigned char、short、unsigned short、
    unsigned int、long、float、double、long double
  提供特化版本
每一个成员的值都是__true_type，表示这些型别都可以采用最快速方式(最底层)进行操作(拷贝、赋值...)

注意：SGI STL <stl_config.h>将__STL_TEMPLATE_NULL定义为template<>
  这就是所谓的class template explicit specializetion
*/
__STL_TEMPLATE_NULL struct __type_traits<char> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<signed char> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned char> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<short> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned short> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<int> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned int> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<long> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<unsigned long> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<float> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<double> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<long double> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

// 针对原生指针设计的偏特化版本
template <class T>
struct __type_traits<T*> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

// 例1：__type_traits在uninitialized_fill_n()全局函数中的应用
template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x) {
  // 以value_type()萃取出迭代器first的value type
  return __uninitialized_fill_n(first, n, x, value_type(first));
}
template <class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n, const T& x, T1*) {
  // 利用__type_traits判断该型别是否为POD型别，然后以是不是POD型别分别派送到不同重载函数中
  typedef typename __type_traits<T1>::is_POD_type is_POD;
  return __uninitialized_fill_n_zux(first, n, x, is_POD());
}
// 是POD型别
template <class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __true_type) {
  return fill_n(first, n, x);
}
template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value){
  for(; n>0; --n, ++first)
    *first = value;
  return first;
}

// 例2：copy()全局函数(它有很多特化、强化版本)
// 下面只是针对函数参数为原生指针的情况设计的，它还有很多复杂情况
// 拷贝一个数组，其元素为任意型别，视情况采用最有效的拷贝手段
template <class T>
inline void copy(T* source, T* destination, int n) {
  copy(source, destination, n, typename __type_traits<T>::has_trivial_copy_constructor());
}

// 拷贝一个数组，其元素型别拥有non-trivial copy constructors
template <class T>
void copy(T* source, T* destination, int n, __false_type){

}
// 拷贝一个数组，其元素型别拥有trivial copy constructors
template <class T>
void copy(T* source, T* destination, int n, __true_type){

}