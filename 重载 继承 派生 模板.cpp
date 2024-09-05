#include<iostream>
#include <string>
using namespace std;
//================= 重载 =================
class Complex{
private:
    double real, imag;
public:
    Complex(double r, double i): real(r), imag(i){};
    // 运算符重载为成员函数
    // 这样的写法只能满足c+5不能满足5+c，要想解决这个问题还是应该重载为普通函数【类似-】
    Complex operator + (const Complex & c2) const{ // 尾部的const表示这是一个常成员函数，不能修改成员变量
        return Complex(real + c2.real, imag + c2.imag);
    }
    friend Complex operator - (const Complex & c1, const Complex & c2);
    // ‘=’ 只能重载为成员函数
};
// 运算符重载为普通函数
// 但是这里是private的，所以不能直接访问，写成为友元函数
// 重载为成员函数时, 参数个数为运算符目数减1
// 重载为普通函数时, 参数个数为运算符目数
Complex operator - (const Complex & c1, const Complex & c2){
    return Complex(c1.real - c2.real, c1.imag - c2.imag);
} 

//================= 继承派生 =================
/* 
基类的private成员：可以被下列函数访问
    基类的成员函数
    基类的友员函数
基类的public成员：可以被下列函数访问
    基类的成员函数
    基类的友员函数
    派生类的成员函数
    派生类的友员函数
    其他的函数 

要在派生类中访问由基类定义的同名成员时, 要使用作用域符号::
*/
// 基类：Animal
class Animal {
public:
    std::string name;

    void eat() {
        std::cout << name << " is eating." << std::endl;
    }

    void sleep() {
        std::cout << name << " is sleeping." << std::endl;
    }
};

// 派生类：Lion，从 Animal 继承
class Lion : public Animal { // 公有继承
    // 基类中的公有和保护成员在派生类中分别保持公有和保护
public:
    void bark() {
        std::cout << name << " is barking." << std::endl;
    }
};

class Cat : protected Animal {  // 保护继承
    // 基类中的公有和保护成员在派生类中都变为保护成员
};

class Rabbit : private Animal {  // 私有继承
    // 基类中的公有和保护成员在派生类中都变为私有成员
};

// ========================= 类的双向关联关系 =========================

class Dog;  // 预先声明Dog类

// Owner类定义
class Owner {
public:
    std::string name;
    Dog* dogs[10];  // 一个指向Dog对象的指针数组，可以容纳最多10只狗
    int dogCount;

    Owner(const std::string& ownerName) : name(ownerName), dogCount(0) {}

    // 为业主添加一只狗
    void addDog(Dog* dog);

    // 显示业主的所有狗
    void showDogs();
};

// Dog类定义
class Dog {
public:
    std::string name;
    Owner* owner;  // 指向Owner对象的指针

    Dog(const std::string& dogName) : name(dogName), owner(nullptr) {}

    // 设置狗的业主
    void setOwner(Owner* owner) {
        this->owner = owner;
    }

    // 显示狗的业主信息
    void showOwner() {
        if (owner) {
            std::cout << name << "'s owner is " << owner->name << "." << std::endl;
        } else {
            std::cout << name << " has no owner." << std::endl;
        }
    }
};

// Owner类方法实现

void Owner::addDog(Dog* dog) {
    if (dogCount < 10) {
        dogs[dogCount] = dog;
        dog->setOwner(this);  // 将此Owner对象设置为狗的业主
        dogCount++;
    } else {
        std::cout << name << " cannot own more than 10 dogs." << std::endl;
    }
}

void Owner::showDogs() {
    std::cout << name << " owns the following dogs:" << std::endl;
    for (int i = 0; i < dogCount; ++i) {
        std::cout << "- " << dogs[i]->name << std::endl;
    }
}


// =============== 虚继承 ===============
// 虚继承的目的是为了解决多继承条件下的菱形继承问题（浪费存储空间、存在二义性）
/* 
“菱形继承”（Diamond Inheritance）是C++多继承中的一个经典问题，发生在以下情况下：
当一个类通过多继承同时继承自两个类，而这两个类又继承自同一个基类时，就会形成一个“菱形”结构。在这种情况下，最下层的派生类将继承两次上层的基类，导致基类中的成员会在派生类中出现两次。这种重复继承可能导致数据的冗余、函数调用的歧义，甚至是意外的行为。
class Parent1 : virtual public Grandparent {
}; 
*/

//================ 类模板和函数模板 ================
// 定义类模板
// template<class T1, class T2> 一个函数模板可以有多个类型参数
template <typename T>
class Box {
private:
    T value; // 存储值的变量

public:
    // 构造函数
    Box(T val) : value(val) {}

    // 获取值的方法
    T getValue() {
        return value;
    }

    // 设置值的方法
    void setValue(T val) {
        value = val;
    }
};
// 定义函数模板
template <typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}



int main(){
    // ===== 运算符重载 =====
    Complex c1(3, 4), c2(1, 2);
    Complex c3 = c1 + c2;

    // ===== 继承派生 =====
    // 创建一个 Lion 对象
    Lion myLion;
    myLion.name = "Buddy";

    // 使用继承自 Animal 的方法
    myLion.eat();
    myLion.sleep();

    // 使用 Lion 自己的方法
    myLion.bark();

    // ===== 类的双向关联关系 =====
    // 创建Owner对象
    Owner john("John");
    // 创建Dog对象
    Dog buddy("Buddy");
    Dog max("Max");
    // 将狗添加到业主
    john.addDog(&buddy);
    john.addDog(&max);
    // 显示业主的狗
    john.showDogs();
    // 显示狗的业主
    buddy.showOwner();
    max.showOwner();

    // ===== 类模板和函数模板 =====
    // 创建 int 类型的 Box
    Box<int> intBox(123);
    cout << "intBox contains: " << intBox.getValue() << endl;
    // 创建 double 类型的 Box
    Box<double> doubleBox(456.78);
    cout << "doubleBox contains: " << doubleBox.getValue() << endl;
    // 创建 string 类型的 Box
    Box<string> stringBox("Hello, Templates!");
    cout << "stringBox contains: " << stringBox.getValue() << endl;

    int x = 5, y = 10;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swapValues(x, y);
    cout << "After swap: x = " << x << ", y = " << y << endl;

    double d1 = 1.1, d2 = 2.2;
    cout << "Before swap: d1 = " << d1 << ", d2 = " << d2 << endl;
    swapValues(d1, d2);
    cout << "After swap: d1 = " << d1 << ", d2 = " << d2 << endl;

}