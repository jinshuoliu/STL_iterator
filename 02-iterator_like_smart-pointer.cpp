/**
 * @brief auto_ptr
 * 它是一个用来z包装原生指针的对象，可以解决内存漏洞问题
 * 源码在头文件<memory>中
 * @tparam T 
 */
template <class T>
class auto_ptr {
public:
  explicit auto_ptr(T *p = 0) : pointee(p) { }
  template<class U>
  auto_ptr(auto_ptr<U>& rhs) : pointee(rhs.release()) {  }
  ~auto_ptr() {
    delete pointee;
  }

  template <class U>
  auto_ptr<T>& operator=(auto_ptr<U>& rhs) {
    if(this != &rhs)
      reset(rhs.release());
    return *this;
  }

  T& operator*() const {
    return *pointee;
  }
  T* operator->() const {
    return pointee;
  }
  T* get() const {
    return pointee;
  }

private:
  T *pointee;
};


/**
 * @brief 一个简单的链表
 * 
 * @tparam T 
 */
template <typename T>
class List {
public:
  void insert_front(T value) {
  }
  void insert_end(T value);
  void display(std::ostream &os = std::cout) const;
  ListItem* front(){
    return _front;
  }
private:
  ListItem<T>* _end;
  ListItem<T>* _front;
  long _size;
};

template <typename T>
class ListItem {
public:
  T value() const {
    return _value;
  }
  ListItem* next() const {
    return _next;
  }

private:
  T _value;
  ListItem* _next;
};

/**
 * @brief 给list写的一个简单的iterator
 * 注意它是一个类
 * @tparam Item 
 */
template <class Item>
struct ListIter {
  Item* ptr; // 与容器的联系,指向容器

  ListIter(Item* p = 0) : ptr(p){ }

  // 这些完全是指针的行为
  Item& operator*() const {
    return *ptr;
  }
  Item* operator->() const {
    return ptr;
  }

  ListIter& operator++() {
    ptr = ptr->next();
    return *this;
  }

  ListIter operator++(int){
    ListIter tmp = *this;
    ++*this;
    return tmp;
  }

  bool operator==(const ListIter& i) const {
    return ptr == i.ptr;
  }

  bool operator!=(const ListIter& i) const {
    return ptr != i.ptr;
  }
};

#include <iostream>
using namespace std;

int main()
{
  // 这样暴露了太多东西
  List<int> mylist;

  for(int i=0; i<5; ++i) {
    mylist.insert_front(i);
    mylist.insert_end(i+2);
  }
  mylist.display();

  ListIter<ListItem<int>> begin(mylist.front());
  ListIter<ListItem<int>> end;
  ListIter<ListItem<int>> iter;

  iter = find(begin, end, 3);
  if(iter == end)
    cout << "not found" << endl;
  else
    cout<< "found." << iter->value() << endl;

  system("pause");
  return 0;
}