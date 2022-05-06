// 通过参数推导机制就可判断型别
template <class T>
void func1(T t){

}

// 使用内嵌型别来确定返回值型别
// 这里typename用来告诉编译器这是一个型别
// 因为在编译之前，无法确定T::value_type到底是型别还是member function或者data memory
template <class T>
typename T::value_type func2(T t){

}

// 它需要为传入型别为pointer和pointer-to-const设计特化版本
template <class I>
struct iterator_traits {
  typedef typename I::iterator_category iterator_category;
  typedef typename I::value_type value_type;
  typedef typename I::difference_type difference_type;
  typedef typename I::pointer pointer;
  typedef typename I::reference reference;
};

// 像这种类型的就需要返回difference_type
template <class I, class T>
typename iterator_traits<I>::difference_type // 返回型别
  count(I first, I last, const T& value) {
    typename iterator_traits<I>::difference_type n = 0;
    for(; first != last; ++first)
      if(*first == value)
        ++n;
    return n;
}

template <class I>
struct iterator_traits {
  typedef typename I::difference_type difference_type;
  typedef typename I::reference reference;
  typedef typename I::pointer pointer;
};

// 针对原生指针的偏特化版本
template <class T>
struct iterator_traits<T*> {
  typedef ptrdiff_t difference_type;
  typedef T& reference;
  typedef T* pointer;
};

// 针对原生pointer-to-const的偏特化版本
template <class T>
struct iterator_traits<const T*> {
  typedef ptrdiff_t difference_type;
  typedef const T& reference;
  typedef const T* pointer;
};

/**
 * @brief advanced()例子
 * 
 */

/*
下面的三个定义：
  一个针对Input Iterator
  一个针对Bidirectional Iterator
  一个针对RandomAccess Iterator
这个会产生一些问题：
  程序调用advance()的时候，应该选用哪一份函数定义呢？
  毕竟它们三个不同名
*/
template <class InputIterator, class Distance>
void advance_II(InputIterator& i, Distance n) {
  // 单向，逐一前进
  while (n--) ++i;
}

template <class BidirectionalIterator, class Distance>
void advance_BI(BidirectionalIterator& i, Distance n) {
  // 双向，逐一前进
  if (n >= 0)
    while(n--) ++i;
  else
    while(n++) --i;
}

template <class RandomAccessIterator, class Distance>
void advance_RAI(RandomAccessIterator& i, Distance n) {
  // 双向，跳跃前进
  i += n;
}
/*
将他们三个合在一起
  但是这样会影响执行效率
*/
template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n) {
  if(is_random_access_iterator(i))
    advance_RAI(i, n);
  else if(is_bidirectional_iterator(i))
    advance_BI(i, n);
  else
    advance_II(i, n);
}

/*
为了提高效率，我们需要加上一个型别已确定的函数参数，使得函数重载机制得以有效运作
还要看traits
  若traits有能力萃取出迭代器的种类，我们便可以利用这个迭代器类型相应型别做advanced()的第三参数。
  这个相应型别一定是一个class type，因为编译器需要依赖它进行重载决议
下面定义五种迭代器类型
*/
// 五个作为i奥基用的型别(tag types)
struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };
/*
这里的继承关系：
  通过继承，我们可以不再写 单纯只做传递调用的函数
*/
/* 继承好处的测试案例 */
#include <iostream>
using namespace std;

struct B {};
struct D1 : public B {};
struct D2 : public D1 {};

template <class I>
void func(I& p, B) {
  cout << "B version" << endl;
}

template <class I>
void func(I& p, D2) {
  cout << "D2 version" << endl;
}

int main()
{
  int * p;
  // 输出B version
  func(p, B());
  // 因为参数不饿能完全吻合，因为继承关系，输出B version
  func(p, D1());
  // 输出D2 version
  func(p, D2());
}
/* 继承好处的测试案例 */



// 重新设计__advance()
template <class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag) {
  // 单向，逐一向前
  while (n--) ++i;
}

template <class ForwardIterator, class Distance>
inline void __advance(ForwardIterator& i, Distance n, forward_iterator_tag) {
  // 单纯地进行传递调用
  advance(i, n, input_iterator_tag());
}

template <class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag) {
  // 双向，逐一前进
  if (n >= 0)
    while(n--) ++i;
  else
    while(n++) --i;
}

template <class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag) {
  // 双向，跳跃前进
  i += n;
}

/*  */
// 需要一个对外开放的上层控制接口，调用上述各个重载的__advance()
template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n) {
  // 第三个参数：迭代器类型
  // 通过traits的机制 从它所获得的迭代器中推导出它的类型
  __advance(i, n, iterator_traits<InputIterator>::iterator_category());
}
/*  */

/* SGI STL */
// 这里在SGI STL里面是这样写的
template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n) {
  __advance(i, n, iterator_category(i));
}
template <class I>
inline typename iterator_traits<I>::iterator_category iterator_category(const I&) {
  typedef typename iterator_traits<I>::iterator_category category;
  return category();
}
/* SGI STL */

// 因此，为了满足上述行为，traits还需要增加一个相应的型别
template <class I>
struct iterator_traits {
  typedef typename I::iterator_category iterator_category;
};
// 针对原生指针的偏特化
template <class T>
struct iterator_traits<T*> {
  // 注意，原生指针是一种Random Access Iterator
  typedef random_access_iterator_tag iterator_category;
};
// 针对原生pointer-to-const的偏特化
template <class T>
struct iterator_traits<const T*> {
  // 注意，原生指针是一种Random Access Iterator
  typedef random_access_iterator_tag iterator_category;
};

/**
 * @brief STL提供的iterators class
 * 它不含任何成员，纯粹只是型别定义，所以继承它并不会导致任何额外的负担
 * @tparam Category 
 * @tparam T 
 * @tparam Distance 
 * @tparam Poinetr 
 * @tparam Reference 
 */
template <class Category, class T, class Distance = ptrdiff_t,
  class Poinetr = T*, class Reference = T&>
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};