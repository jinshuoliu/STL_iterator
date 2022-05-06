// /**
//  * @brief 
//  * 从这里查看rotate需要知道iterators的三个associated types
//  * iterators必须有能力回答algorithms的提问
//  * 这里体现出了三个
//  * @tparam _ForwardIterator 
//  * @param __first 
//  * @param __middle 
//  * @param __last 
//  */
// template<typename _ForwardIterator>
// inline void rotate(_ForwardIterator __first, _ForwardIterator __middle, _ForwardIterator __last)
// {
//   ...
//   std::__rotate(__first, __middle, __last,
//         std::__iterator_category(__first));
//   ...
// }

// /**
//  * @brief 
//  * This function is not a part of the C++ standard but is syntactic
//  * sugar for internal library use only.
//  * @tparam _Iter 
//  * @return iterator_traits<_Iter>::iterator_category 
//  */
// template<typename _Iter>
// inline typename iterator_traits<_Iter>::iterator_category
//   __iterator_category(const _Iter&)
// {
//   return typename iterator_traits<_Iter>::iterator_category(); // 1.分类
// }

// /**
//  * @brief 
//  * This is a helper function for the rotate algorithm.
//  * @tparam _RandomAccessIterator 
//  * @param __first 
//  * @param __middle 
//  * @param __last 
//  */
// template<typename _RandomAccessIterator>
// void __rotate(_RandomAccessIterator __first,
//   _RandomAccessIterator __middle,
//   _RandomAccessIterator __last,
//   random_access_iterator_tag)
// {
//   ...
//   // iterators必须有能力回答algorithms的提问
//   // 2.difference_type是两个iterator之间的距离
//   typedef typename iterator_traits<_RandomAccessIterator>::difference_type _Distance;
//   // 3.这个是说明它所指的value的type
//   typedef typename iterator_traits<_RandomAccessIterator>::value_type _ValueType;
//   _Distance __n = __last -__first;
//   _Distance __k = __middle -__first;
//   ...
//   for(;;) {
//     if(__k<__n-__k) {
//       if(__is_pod(_ValueType)&&__k==1) {
//         _ValueType __t = _GLIBCXX_MOVE(*__p);
//       }
//     }
//   }
// }

// // I是class iterator
// template <class I>
// struct iterator_traits { // traits是特性的意思
//   typedef typename I::iterator_category iterator_category;
//   typedef typename I::value_type value_type;
//   typedef typename I::difference_type difference_type;
//   typedef typename I::pointer pointer;
//   typedef typename I::reference reference;
// };

// // I是pointer to T
// // 两个 partial specialization:
// template <class T>
// struct iterator_traits<T*> {
//   typedef  random_access_iterator_tag iterator_category;
//   typedef T value_type;
//   typedef ptrdiff_t difference_type;
//   typedef T* pointer;
//   typedef T& reference;
// };

// // I是pointer to const T
// template <class T>
// struct iterator_traits<const T*> {
//   // 这里是为了声明变量，所以不用const修饰
//   typedef  random_access_iterator_tag iterator_category;
//   typedef T value_type;
//   typedef ptrdiff_t difference_type;
//   // 顶层const
//   typedef const T* pointer;
//   typedef const T& reference;
// };

// // 在需要了解value type 时便可如此操作：
// template <typename I,...>
// void algorithm(...) {
//   typename iterator_traits<T>::value_type v1;
// }