#include <iostream>

struct element {
  double data;
  element* next;
  element() {
    data = 0;
    next = nullptr;
  }
};

template <typename T>
class stack {
private:
  element* hd;
public:
  stack() {
    hd=nullptr;
  }

  void push(T&& value) {
    
    element* A = new element;
    A->data = std::move(value);
    if (hd == nullptr) {

      hd = A;
    }
    else {
      A->next = hd;
      hd = A;
    }

  }

  void push(const T& value) {
    element* A = new element;
    A->data = value;
    if (hd == nullptr) {
      hd = A;
    }
    else{
      A->next=hd;
      hd = A;
    }
  }

  void pop() {
    element* buf = new element;
    hd = std::move(hd->next);
  }
  const T& head() const {  
    return hd->data;
  }
  
  template <typename ... Args>
  void push_emplace(Args&&... value) {
    element* A = new element;
    A->data = T(std::forward<Args>(value)...);
    if (hd == nullptr) {
      hd = A;
    }
    else {
      A->next = hd;
      hd = A;
    }
  }

  void printer() {  
    std::cout << hd->data<<std::endl;
    element* buffer=hd;
    while (buffer->next != nullptr) {
      std::cout << buffer->next->data<<std::endl;
      buffer = buffer->next;
    }
    std::cout << std::endl;
  }
};

int main() {
  stack<int>p;
  int a = 5;
  int b = 6;
  int c = 7;
  int d = 8;
  int e = 1;
  int* ptr1 = &a;
  int* ptr2 = &e;
  p.push(*ptr1);
  p.push(b);
  p.push(7);
  p.push(std::move(d));
  p.printer();
  p.pop();
  p.printer();
  p.push_emplace(*ptr2);
  p.printer();
  std::cout << p.head() << std::endl;
  return 0;
}
