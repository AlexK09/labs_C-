
#include <atomic>
#include <iostream>
#include <utility>
#include <algorithm>

class Control {
	std::atomic_uint counter;


public:
	Control() { counter = 0; }
	void increase() { counter++; }
	
	
		
	
	void decrease() { counter--; }
	size_t size() { return static_cast<size_t>(counter); }
};
template <typename T>
class SharedPtr {
private:
	Control* cont;
	T* data; 

public:
	SharedPtr() { 
		data = nullptr; 
		cont = nullptr;
	}
	 SharedPtr(T* r) { 
		data = r;
		cont = new Control(); 
		cont->increase(); 
	}


	SharedPtr(const SharedPtr& r) {
		                             
			cont = r.cont;
		data = r.data;
		if (cont != nullptr) {
			cont->increase();
		}
	}


	SharedPtr(SharedPtr&& r) {
		cont = r.cont;
		data = r.data;
		cont->increase();
		r.cont = nullptr;
		r.data = nullptr;
	}
	
	
	~SharedPtr() {
		if (data == nullptr || cont == nullptr) return;
		if (*this) {
			cont->decrease();
			if (cont->size() == 0) {
				std::cout << "deleted";
				delete data;
				delete cont;
			}
		}
	}
	
	auto operator=(const SharedPtr& r) -> SharedPtr& {
		if (data != nullptr) {
			cont->decrease();
			if (cont->size() == 0) {
				delete cont;
				delete data;
			}
		}

		cont = r.cont;
		if (cont != nullptr) cont->increase();
		data = r.data;
		return (*this);
	}

	auto operator=(SharedPtr&& r) -> SharedPtr& {
		if (data != nullptr) {
			cont->decrease();
			if (cont->size() == 0) {
				delete cont;
				delete data;
			}
		}
		cont = r.cont;
		data = r.data;
		if (r.data != nullptr) {
			delete r.cont;
			delete r.data;
		}
		return (*this);
	}
	 operator bool() const {
		if (data == nullptr) return false;
		if (cont->size() == 0) return false;
		return true;
	}
	auto operator*() const -> T& { return *data; }
	auto operator-> () const -> T* { return data; }
	auto get() -> T* { return data; }
	auto reset() {
		if (cont != nullptr) {
			cont->decrease();
			if (cont->size() == 0) {
			//if (!cont){
			delete data;
				delete cont;
			}
		}
		data = nullptr;
		cont = nullptr;
	}
	auto reset(T* ptr) {
		reset();
		data = ptr;
		cont = new Control();
		cont->increase();
	}
	void swap(SharedPtr& r) {
		auto buf = r.data;
		r.data = data;
		data = buf;
		auto buf2 = r.cont;
		r.cont = cont;
		cont = buf2;
	
	}
	auto use_count() const -> size_t {
		if (!*this) return 0;
		return cont->size();
	}
};

int main() {
	int* p = new int(5);
	/*SharedPtr<int> ptr1(p);
	SharedPtr<int> ptr2(ptr1);
	SharedPtr<int> ptr3(ptr2);
	SharedPtr<int> ptr4(ptr3);*/
	auto ptr1 = std::make_shared<int*>(p);
	//auto ptr2= std::make_shared<int>(ptr1);
	auto ptr2(ptr1);
	auto ptr3(ptr2);
	auto ptr4(ptr3);
	std::cout << ptr1.use_count()<<std::endl;
	ptr3.reset();
	ptr4.reset();
	
		//SharedPtr<int> ptr5(ptr4);
	auto ptr5(ptr4);
		std::cout << ptr1.use_count() << std::endl;
		std::cout << ptr5.use_count() << std::endl;
	
	std::cout << ptr2.use_count() << std::endl;
	
	system("pause");
	return 0;
}
