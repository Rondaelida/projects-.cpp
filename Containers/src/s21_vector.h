#ifndef CONTAINERS_SRC_S21_VECTOR_H_
#define CONTAINERS_SRC_S21_VECTOR_H_

// подключаем библиотеки
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
// class s21_vector переименовать
class Vector {
 public:
  // внутренние типы
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef std::ptrdiff_t difference_type;
  typedef size_t size_type;

  // итераторы
  class Iterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;

    // конструктор итератора
    Iterator(pointer ptr) : ptr_(ptr) {}

    // разыменование
    reference operator*() const { return *ptr_; }
    // оператор доступа к члену возвращает указатель на элемент контейнера
    pointer operator->() const { return ptr_; }
    // возвращает ссылку на измененный итератор +1
    Iterator& operator++() {
      ++ptr_;
      return *this;
    }
    // возвращает копию исходного итератора до его изменения +1
    Iterator operator++(int) {
      Iterator temp(*this);
      ++ptr_;
      return temp;
    }
    // возвращает ссылку -1
    Iterator& operator--() {
      --ptr_;
      return *this;
    }
    // возвращает копию  -1
    Iterator operator--(int) {
      Iterator temp(*this);
      --ptr_;
      return temp;
    }
    // + число
    Iterator operator+(int n) { return Iterator(ptr_ + n); }
    // + число присвоение
    Iterator& operator+=(int n) {
      ptr_ += n;
      return *this;
    }
    // - число
    Iterator operator-(int n) {
      return Iterator(ptr_ - n);
    }  // - число присвоение

    Iterator operator-(Iterator n) {
      return Iterator(ptr_ - *n.ptr_);
    }  // - число присвоение

    Iterator& operator-=(int n) {
      ptr_ -= n;
      return *this;
    }
    // доступ к элементу контейнера
    // reference operator[](difference_type n) const { return *(ptr_ + n); }
    // операторы сравнения
    bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; }
    bool operator<(const Iterator& other) const { return ptr_ < other.ptr_; }
    bool operator<=(const Iterator& other) const { return ptr_ <= other.ptr_; }
    bool operator>(const Iterator& other) const { return ptr_ > other.ptr_; }
    bool operator>=(const Iterator& other) const { return ptr_ >= other.ptr_; }

   private:
    value_type* ptr_;
  };

  class const_iterator {
   public:
    // типы итератора
    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename Vector::value_type;
    using reference = typename Vector::const_reference;
    using pointer = const value_type*;
    using difference_type = typename Vector::difference_type;

    // конструкторы
    // const_iterator() : ptr_(nullptr) {}
    // const_iterator(const pointer ptr) : ptr_(ptr) {}
    // const_iterator(const Iterator& it) : ptr_(it.ptr_) {}

    // оператор разыменования
    reference operator*() const { return *ptr_; }

    // оператор доступа к члену
    pointer operator->() const { return ptr_; }

    // префиксный оператор инкремента
    const_iterator& operator++() {
      ++ptr_;
      return *this;
    }

    // постфиксный оператор инкремента
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      ++ptr_;
      return tmp;
    }

    // префиксный оператор декремента
    const_iterator& operator--() {
      --ptr_;
      return *this;
    }

    // постфиксный оператор декремента
    const_iterator operator--(int) {
      const_iterator tmp(*this);
      --ptr_;
      return tmp;
    }

    // операторы сложения
    const_iterator operator+(difference_type n) const {
      return const_iterator(ptr_ + n);
    }
    const_iterator& operator+=(difference_type n) {
      ptr_ += n;
      return *this;
    }

    // операторы вычитания
    const_iterator operator-(difference_type n) const {
      return const_iterator(ptr_ - n);
    }
    const_iterator& operator-=(difference_type n) {
      ptr_ -= n;
      return *this;
    }

    // оператор индексирования
    reference operator[](difference_type n) const { return *(ptr_ + n); }

    // операторы сравнения
    bool operator==(const const_iterator& other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const const_iterator& other) const {
      return ptr_ != other.ptr_;
    }
    bool operator<(const const_iterator& other) const {
      return ptr_ < other.ptr_;
    }
    bool operator<=(const const_iterator& other) const {
      return ptr_ <= other.ptr_;
    }
    bool operator>(const const_iterator& other) const {
      return ptr_ > other.ptr_;
    }
    bool operator>=(const const_iterator& other) const {
      return ptr_ >= other.ptr_;
    }

    // преобразование в iterator
    // operator Iterator() const { return iterator(ptr_); }

   private:
    value_type* ptr_;  // указатель на элемент контейнера
  };

  // конструкторы
  Vector() : size_(0), capacity_(0), array_(nullptr) {}

  // принимает один аргумент size_type n и создает вектор с n элементами
  Vector(size_type n) : size_(n), capacity_(n), array_(new T[n]) {}

  //  принимает список инициализации items
  //  и создает вектор с элементами, указанными в этом списке.
  Vector(std::initializer_list<value_type> const& items)
      : size_(items.size()),
        capacity_(items.size()),
        array_(new T[items.size()]) {
    int i = 0;
    for (const auto& item : items) {
      array_[i] = item;
      i++;
    }
  }

  //  принимает копию объекта класса s21_vector
  //  и создает новый вектор, который является копией этого объекта.
  Vector(const Vector& v)
      : size_(v.size_), capacity_(v.capacity_), array_(new T[v.capacity_]) {
    for (size_t i = 0; i < size_; ++i) {
      array_[i] = v.array_[i];
    }
  }

  // принимает временный объект класса s21_vector
  // и создает новый вектор, который является копией этого объекта.
  Vector(Vector&& v)
      : size_(v.size_), capacity_(v.capacity_), array_(v.array_) {
    v.size_ = 0;
    v.capacity_ = 0;
    v.array_ = nullptr;
  }

  // диструктор
  ~Vector() {
    delete[] array_;
    size_ = 0;
    capacity_ = 0;
  }

  // оператор позволяет присваивать временный объект класса s21_vector другому
  // объекту класса s21_vector
  Vector& operator=(const Vector& v) {
    if (this != &v) {
      // Создаем копию массива из v
      T* new_array = new T[v.capacity_];
      for (size_t i = 0; i < v.size_; ++i) {
        new_array[i] = v.array_[i];
      }

      // Освобождаем память, выделенную для текущего массива
      delete[] array_;

      // Присваиваем новый массив и обновляем size_ и capacity_
      array_ = new_array;
      size_ = v.size_;
      capacity_ = v.capacity_;
    }
    return *this;
  }

  // доступ к указанному элементу с проверкой границ
  reference at(size_type pos) {
    if (pos >= this->size()) {
      throw std::out_of_range("Vector::at");
    }
    return array_[pos];
  }
  // доступ к указанному элементу
  reference operator[](size_type pos) { return array_[pos]; }

  // доступ к первому элементу
  const_reference front() { return array_[0]; }
  // доступ к последнему элементу
  const_reference back() { return array_[size_ - 1]; }
  // прямой доступ к базовому массиву
  T* data() { return array_; }

  // возвращает итератор в начало
  Iterator begin() const { return Iterator(array_); }

  const_iterator cbegin() const { return const_iterator(array_); }

  // возвращает итератор до конца
  Iterator end() const { return Iterator(array_ + size_); }

  const_iterator cend() const { return const_iterator(array_ + size_); }

  // проверяет, пуст ли контейнер
  bool empty() const { return size_ == 0; }

  // возвращает количество элементов
  size_type size() const { return size_; }

  // возвращает максимально возможное количество элементов c учётом границ
  // value_type
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / (2 * sizeof(value_type));
  }

  // выделяет хранилище элементов размера и копирует текущие элементы массива
  // в новый массив
  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::length_error("Vector::reserve: size execeds max_size");
    }
    if (size > capacity_) {
      value_type* new_array = new value_type[size];
      for (size_type i = 0; i < size_; ++i) {
        new (&new_array[i]) value_type(std::move(array_[i]));
      }
      delete[] array_;
      array_ = new_array;
      capacity_ = size;
    }
  }

  // возвращает количество элементов, которые могут храниться в выделенном на
  // данный момент хранилище
  size_type capacity() const { return capacity_; }

  // уменьшает использование памяти за счет освобождения неиспользуемой
  // памяти
  void shrink_to_fit() {
    if (capacity_ > size_) {
      value_type* new_array = new value_type[size_];
      for (size_type i = 0; i < size_; ++i) {
        new_array[i] = std::move(array_[i]);
      }
      delete[] array_;
      array_ = new_array;
      capacity_ = size_;
    }
  }

  // очищает содержимое
  void clear() {
    // сохраняем текущий размер вектора
    size_type old_size = size_;
    // вызываем деструктор для каждого элемента вектора
    for (size_type i = 0; i < old_size; ++i) {
      array_[i].~T();
    }
    // обнуляем размер вектора
    size_ = 0;
    // если вектор был пуст, то ничего не делаем
    if (capacity_ == 0) {
      return;
    }
    // освобождаем память, выделенную для хранения элементов вектора
    delete[] array_;
    // обнуляем указатель на массив и емкость вектора
    array_ = nullptr;
    capacity_ = 0;
  }

  // вставляет элементы в конкретную позицию и возвращает итератор,
  // указывающий на новый элемент
  Iterator insert(Iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::out_of_range("Iterator is out of range");
    }
    // Если нет свободного места, увеличиваем размер массива
    if (size_ == capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    // Сдвигаем элементы вправо, чтобы освободить место для нового элемента
    for (Iterator it = end() - 1; it >= pos; --it) {
      *it = *(it - 1);
    }
    // Вставляем новый элемент
    *pos = value;
    // Увеличиваем размер вектора
    ++size_;
    return pos;
  }

  // стирает элемент в позиции
  void erase(Iterator pos) {
    Iterator it = pos;
    Iterator it_2 = pos + 1;
    while (it_2 != this->end()) {
      *it = *it_2;
      it++;
      it_2++;
    }
    *it = '\0';
    size_--;
  }

  // добавляет элемент в конец
  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(capacity_ * 2);
    }
    array_[size_++] = value;
  }

  // удаляет последний элемент
  void pop_back() {
    if (size_ == 0) {
      throw std::out_of_range("Vector is empty");
    }
    --size_;
    if (size_ < capacity_ / 2) {
      reserve(capacity_ / 2);
    }
  }

  // меняет содержимое
  void swap(Vector& other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(array_, other.array_);
  }

 private:
  size_type size_;
  size_type capacity_;
  value_type* array_;
};
}  // namespace s21

#endif  // CONTAINERS_SRC_S21_VECTOR_H_