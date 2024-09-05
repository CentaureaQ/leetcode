#include <iostream>
using namespace std;

/* ---------通过swap来了解“引用” & ---------*/
void swap( int & a, int & b ) // 传引用，实现交换变量的值
 {
    int tmp;
    tmp = a; a = b; b = tmp;
 }

void swap1( int a, int b ) 
// 确实能把值传来，但是和上面的swap函数不一样，这里只能在函数内部用a和b，不能改变外部的值
{
    //cout <<"swap1"<< a << " " << b << endl;
    int tmp;
    tmp = a; a = b; b = tmp;
 }

/* ---------常引用 ---------
函数参数为常量指针时, 可避免函数内部不小心改变参数指针所指地方的内容
*/
void const_reference(){
    // 常引用
    int n;
    const int & r = n;
    n = 100;
    //cout << r << endl; // 100
    n = 200;
    //cout << r << endl; // 200
    // r = 300; // error，不能通过常引用修改变量n的值
}

/* --------- 类 ---------*/
class CRectangle
{
    private:
        int w, h;
        static int nTotalArea;  //静态成员变量
        static int nTotalNumber;  //静态成员变量
    public:
        int Area(); //成员函数仅在此处声明
        int Perimeter() ; 
        void Init( int w_, int h_ );
        CRectangle(int w_, int h_);
        CRectangle(CRectangle r1, CRectangle r2);
        CRectangle(CRectangle & r);
        CRectangle(int i);
        ~CRectangle();
        CRectangle AddOne();
        static void PrintTotal(); //静态成员函数
        // 友元函数
        friend void setWidth(CRectangle & r, int w);
        // 友元类
        friend class Square;
}; 



/*
在类的成员函数内部, 能够访问：
    当前对象的全部属性, 函数
    同类其它对象的全部属性, 函数
在类的成员函数以外的地方, 只能够访问该类对象的公有成员
*/

// 成员函数，通过成员函数访问类的私有对象
int CRectangle::Area()  {  // CRectangle::说明后面的函数是CRectangle类的成员函数, 而非普通函数
    return w * h;      
}
int CRectangle::Perimeter() { 
    return 2 * ( w + h);  
}
void CRectangle::Init( int w_, int h_ ) 
{
    w = w_;  h = h_;
}

// ========================== 构造函数 public ==============================
// private构造函数不能直接用来初始化对象
CRectangle::CRectangle(int w_, int h_){
    w = w_;
    h = h_;
    nTotalNumber++; // 静态成员变量
    nTotalArea += w * h; // 静态成员变量
}
// 构造函数的不同形式，比如R1+R2这种，重载构造函数
CRectangle::CRectangle(CRectangle r1, CRectangle r2){
    w = r1.w + r2.w;
    h = r1.h + r2.h;
    nTotalNumber++; // 静态成员变量
    nTotalArea += w * h; // 静态成员变量
}
// 拷贝构造函数
// 形如X::X( X& )或者X::X( const X& ), 只有一个参数即对同类对象的引用【是引用！】
CRectangle::CRectangle(CRectangle & r){
    w = r.w;
    h = r.h;
    // 考虑到静态成员变量，需要重写拷贝构造函数
    //【避免调用默认的拷贝构造函数生成临时对象，导致没有增加静态成员变量，而在临时对象析构的时候减少静态成员变量】
    nTotalNumber++; // 静态成员变量
    nTotalArea += w * h; // 静态成员变量
} 
// 类型转换构造函数
CRectangle::CRectangle(int i){
    w = i;
    h = i;
}
// ==========================析构函数==============================
// ~X()，没有参数，没有返回值，不能重载
// 一个类只能有一个析构函数
CRectangle::~CRectangle(){
    // cout << "Destructor called" << endl;
    // 或者delete一些已分配的动态内存
    nTotalNumber--; // 静态成员变量·
    nTotalArea -= w * h; // 静态成员变量
}

/*---------new & delete---------
Ctest * pTest;
pTest = new Ctest;      //构造函数调用
delete pTest;           //析构函数调用
----------------------------------------------------------------
pTest = new Ctest[3]; //构造函数调用3次
delete [] pTest;      //析构函数调用3次
//若new一个对象数组, 那么用delete释放时应该写[]
//否则只delete一个对象(调用一次析构函数)
*/

/* =======================内联函数=========================
函数调用本身是有时间开销的，但是函数被反复执行很多次, 调用函数所产生的这个开销就会显得比较大
定义函数时, 在返回值类型前面加inline关键字, 可以使得函数成为内联函数
编译器处理内联函数的调用语句时将整个函数的代码插入到调用语句处, 而不会生出调用函数的语句
 */
inline int max(int a, int b){
    return a > b ? a : b;
}
/*
类中的内联函数
在成员函数前面加上inline关键字后, 成员函数就成为内联成员函数
将整个函数体写在类定义内部, 函数也会成为内联成员函数
*/

// ======================= this 指针 ==========================
// this指针是一个隐含于每一个成员函数中的特殊指针
// 它指向调用该成员函数的对象
// 当对象调用成员函数时, 编译系统会自动将对象的地址赋给this指针
// this指针是一个常量指针, 它不能被赋值
CRectangle CRectangle::AddOne(){
    w++; // 等价于 this->w++;   
    h++; // 等价于 this->h++; this指向调用该成员函数的对象
    return *this;
}
 
/*
================ static: 静态成员变量和静态成员函数====================
// 静态成员变量是属于整个类的, 而不是某个对象的
// 静态成员变量在定义时加上static关键字
普通成员变量每个对象有各自的一份
Vs. 静态成员变量一共*就一份*,  为所有对象共享
sizeof 运算符不会计算静态成员变量
普通成员函数必须具体作用于某个对象
Vs. 静态成员函数并不具体作用于某个对象
静态成员不需要通过对象就能访问

类似于类中的全局变量和全局函数
*/
// 必须在定义类定义的外面专门对静态成员变量进行声明
int CRectangle::nTotalNumber = 0;
int CRectangle::nTotalArea = 0;

// 静态成员函数
void CRectangle::PrintTotal(){
    // 在静态成员函数中不能访问非静态成员变量
    // cout << w << endl; // error
    cout << nTotalNumber << "," << nTotalArea << endl;
}

/*
// ========================= const 类中常量成员和常量成员函数 ===========================
// 常量成员函数
• 在类的成员函数说明后面加const关键字, 则该成员函数成为常量成员函数
• 常量成员函数内部不能改非静态属性的值, 也不能调用同类的非常量成员函数(静态成员函数除外)
*/

class Sample {
    public: 
    int value; 
    const int a = 0;
    static int b;
    mutable int c; // mutable关键字修饰的变量，即使在const成员函数中也可以被修改
    void GetValue( )  const; // 注意这里的const关键字
    void func( ) { }; // 普通成员函数，不能在const成员函数中被调用
}; 
// 静态成员变量初始化
int Sample::b = 0;

void Sample::GetValue( ) const { // 注意这里的const关键字
    //value = 0;  // wrong, 常量成员函数不能修改非静态成员变量
    //func();       //wrong, 常量成员函数不能调用非常量成员函数
    cout << value << endl; // ok, 常量成员函数可以访问常量成员变量
    b = 1; // 静态static成员变量可以在常量const成员函数中被修改
    c = 2; // mutable关键字修饰的变量，即使在const成员函数中也可以被修改
 }

/*
如果觉得传递一个对象效率太低（导致复制构造函数调用, 还费时间）又不想传递指针, 又要确保实际参数的值不能在函数中被修改,那么可以使用:
 const T & 类型的参数
*/

void PrintfObj( const Sample & o ){
    // o.func();          //error
    o.GetValue();   //ok, 常量对象上可以执行常量成员函数
    Sample & r = (Sample &) o;  //必须强制类型转换
    r.func();           //ok
}

// ========================= const 指针 ============================
void const_pointer(){
    // （为了方便记忆可以想成）被 const 修饰（在 const 后面）的值不可改变
    // const对指针定义,不可通过该指针修改其指向的地方的内容
    int n, m;
    const int * p8 = & n;
    //* p8 = 5; //编译出错
    n = 4;    //ok
    p8 = & m; //ok
    // 注意: 不能把常量指针赋值给非常量指针, 反过来可以
    const int * pp1; int * pp2;
    pp1 = pp2;  //ok
    // pp2 = pp1;  //error [会有通过pp2（非常量）篡改pp1指向的内容的风险]
    pp2 = (int * ) pp1; //ok

    char greeting[] = "Hello";
    char greeting1[] = "HELLO";
    char* p5 = greeting1;

    char* px = greeting;                // 指针变量，指向字符数组变量

    const char* p2 = greeting;          // 指针变量，指向字符数组常量（const 后面是 char，说明指向的字符（char）不可改变）
    // p2[0] = 'a'; // error 不能通过p2修改greeting的内容
    p2 = p5; // 可以改变p2的指向
    // cout << "p2 " << p2 << endl; // HELLO
/*  // 打印p2、p5、greeting、greeting1的地址
    cout << "p2 " << (void*)p2 << endl; // 0x7ffedf7f3b80
    cout << "p5 " << (void*)p5 << endl; // 0x7ffedf7f3b90
    cout << "greeting " << (void*)greeting << endl; // 0x7ffedf7f3b80
    cout << "greeting1 " << (void*)greeting1 << endl; // 0x7ffedf7f3b90 */


    char* const p3 = greeting;          // 自身是常量的指针，指向字符数组变量（const 后面是 p3，说明 p3 指针自身不可改变）
    // p3 = p1; // error 不能改变p3的指向
    // 可以通过p3修改greeting的内容
    p3[0] = 'a';
    // cout << "p3 " << greeting << endl; // aello

    const char* const p4 = greeting;    // 自身是常量的指针，指向字符数组常量
}


//============================== 成员对象和封闭类 ==============================
// 成员对象
// 一个类的对象作为另一个类的成员
// 成员对象的构造函数在封闭类的构造函数初始化列表中调用
// 封闭类是指一个类的成员变量是另一个类的对象，包含成员对象的类叫做封闭类
class EECS {
    public:
    EECS( int a, int b, int c ) : obj1( a ), obj2( b, c ) { }
    private:
    CRectangle obj1;
    CRectangle obj2;
};
class PKU {
    public:
    // 构造函数初始化列表
    // 初始化const成员和引用成员时, 必须在成员初始化列表中进行
    PKU( int a, int b, int c, int d ) : obj1( a ), obj2( b, c , d) { }
    // 需要注意，即使是EECS作为PKU的成员对象，PKU也不能直接访问EECS的私有成员
    private:
    CRectangle obj1;
    EECS obj2;
};


//============================== 友元 ==============================
// 友元函数
// 友元函数是定义在类外部, 但有权访问类的所有私有（private）成员和保护（protected）成员
// 友元函数不是成员函数, 但是它可以访问类的所有成员
// 友元类之间的关系不能传递,不能继承
void setWidth(CRectangle & r, int w){
    r.w = w;
}

// 友元类
// 友元类的所有成员函数都是另一个类的友元函数
// 友元类的所有成员函数都可以访问另一个类的所有成员
class Square{
    private:
    int side;
    CRectangle r; // 友元类可以有另一个类的对象 作为 成员对象，友元类作为封闭类
    public:
    Square(int a):side(a), r(a, a){} // 要使用初始化列表 来初始化另一个类的对象
    int calculateArea() {
        return side * side;
    }
    int calculateArea(CRectangle & r) {
        return r.w * r.h;
    }
};


int main(){
    int n1, n2;
    n1 = 1;
    n2 = 2;
    swap1(n1, n2);
    
    const_reference();

    CRectangle r1(3, 4);
    CRectangle *p1 = &r1; // &是引用，本质上是一个“取地址”的操作，&r1是一个指向r1的指针，CRectangle *表示一个指向CRectangle对象的指针
    // 动态内存
    CRectangle *pr = new CRectangle(5, 6);
    delete pr;
    CRectangle r2(r1); // 调用拷贝构造函数，用一个对象去初始化同类的另一个对象
    CRectangle r3 = r1; // 调用拷贝构造函数，用一个对象去初始化同类的另一个对象， //初始化语句, 非赋值语句
    // CRectangle r3; r3 = r1; // 赋值语句，和上面不同，不调用拷贝构造函数
    CRectangle r4 = 5; // 类型转换构造函数，5被自动转换成一个临时CRectangle对象

    // 动态分配数组
    int *p;
    int size = 5;
    p = new int[size];
    delete [] p; // 释放数组

    // this指针
    CRectangle r5 = r1.AddOne();

    // 静态成员变量和静态成员函数
    CRectangle::PrintTotal();
    // 错误的print方法
    // r1.PrintTotal(); // error, 静态成员函数不能通过对象调用
    // cout << r1.nTotalNumber << endl; // error, 静态成员变量不能通过对象调用

    // 友元函数
    setWidth(r1, 10); 
    // 友元类
    Square s(5);
    cout << s.calculateArea(r1) << endl; // 利用square这一友元类的成员函数计算rectangle类的面积

    PKU pku(1, 2, 3, 4);
    return 0;
}