// function specialization
template <class T>
void fun(T a)
{
   cout << "The main template fun(): "
        << a << endl;
}
 
template<>
void fun(int a)
{
    cout << "Specialized Template for int type: "
         << a << endl;
}

// clas specialization
// !!! mnogo vajno e che ako pravq class specialization vsichki metodi trqbva da sa mi inline !!!
// !!! inache hvurlq greshki koito ako tova ne go znam mnogo shte se chudq					  !!!
template <class T>
class Test
{
  // Data members of test
public:
   Test()
   {
       // Initialization of data members
       cout << "General template object \n";
   }
   // Other methods of Test
};
 
template <>
class Test <int>
{
public:
   Test()
   {
       // Initialization of data members
       cout << "Specialized template object\n";
   }
};

// posfix and prefix operator overloading
class Check
{
private:
    int i;
public:
    Check() : i(0) {  }
    Check operator ++ ()
    {
        Check temp; // here it is not neccessary to make a temp value
        temp.i = ++i;
        return temp;
    }

    // !!Notice int inside barcket which indicates postfix increment!!!
    Check operator ++ (int) // Dummy value for the postfix
    {
        Check temp;	  // here IT IS neccessary to make a temp, give it the ORIGINAL value and return the temp,
        temp.i = i++; // when we should make sure that the original value is incremented
        return temp;
    }

    void Display()
    {
        cout << "i = " << i << endl;
    }
};
int main()
{
    Check obj, obj1;
    obj.Display();  // 0
    obj1.Display(); // 0

    // Operator function is called, only then value of obj is assigned to obj1
    obj1 = ++obj;
    obj.Display();  // 1
    obj1.Display(); // 1

    // Assigns value of obj to obj1, only then operator function is called.
    obj1 = obj++;
    obj1.Display(); // 1
    obj.Display();  // 2
}

// Define a template class with a default type of int for T
template <typename T = int>
class MyClass {
public:
    T data;
    
    MyClass(T val) : data(val) {}

    void show() const {
        std::cout << data << std::endl;
    }
};

template <template <typename, typename> class Container, typename T>
class Wrapper {
public:
    Container<T, std::allocator<T>> c;
	//...
};
int main() {
    Wrapper<std::vector, int> vectorWrapper;
}

//!!! CASTS IN CPP !!!
//
// static_cast(expression)
// Най-близкото нещо до стандартният C style cast. 
// Той прави смяна от един тип към друг, ако тази операция е дефинирана(можем да направим смяната на типа)
// 
// const_cast(expression)
// !!! Не е добра практика да използваме const_cast !!!
// 
// Използва се за добавяне и махане на const. 
// Той конвертира указател или референция към обект, към съответно константен или не константен такъв.
// 
// reinterpret_cast(expression)
// Използва се за реинтерпретиране на битовете на един тип към друг тип. 
// Той конвертира указател или референция към обект, към target-type, който е указател или референция към друг тип.
// 
// dynamic_cast(expression)
// Използва се за конвертиране от базов клас към наследник. 
// Работи само с указатели или референции към полиморфни обекти(трябва да има поне една виртуална функция). 
// Ако target-type е наследник на типът на expression, ще се конвертира успешно и ще се върне наследника, ако не ще се върне nullptr.



// Ukazateli kum funkcii
void Print(int x)
{
    std::cout << "Hello World! Value is: " << x << '\n';
}

int main()
{
    void(*function)(int);

    function = &Print;
    function = Print;

    return 0;
}

// Функции, които връщат функции, като резултат
void HelloWorld()
{
    std::cout << "Hello World!\n";
}

void HelloThere()
{
    std::cout << "Hello There!\n";
}

void (*PrintFactory(const bool flag))()
{
    if(flag)
    {
        return HelloWorld;
    }
    return HelloThere;
}

int main()
{
    PrintFactory(true)();
    PrintFactory(false)();

    return 0;
}

// typedef
typedef int** IntMatrix; <=>
using IntMatrix = int**;
template <typename T>
using Vector = std::vector<T>;
typedef int(*FuncType)(int);

int main()
{
    IntMatrix matrix;
    return 0;
}
typedef void(*PrintFunction)();

void HelloWorld()
{
    std::cout << "Hello World!\n";
}

void HelloThere()
{
    std::cout << "Hello There!\n";
}

PrintFunction PrintFactory(const bool flag)
{
    if(flag)
    {
        return HelloWorld;
    }
    return HelloThere;
}

int main()
{
    PrintFunction func = PrintFactory(true);
    func();
    func = PrintFactory(false);
    func();
    return 0;
}

// lambda functions
// [captures] <t-params> (params) exception_specifier(optional) trailing_type(optional) { body }
int main(){

    const double PI = 3.14;

    void (*printLambda)(int) = [PI](int x)->void{
        std::cout << x * PI << '\n';
    };

    printLambda(10); // 31.4
    printLambda(5);  // 15.7

    return 0;
}

// friend - The friend declaration appears in a class body and grants a function or another class access to 
// private and protected members of the class where the friend declaration appears.
class Y
{
    int data; // private member
 
    // the non-member function operator<< will have access to Y's private members
    friend std::ostream& operator<<(std::ostream& out, const Y& o);
    friend char* X::foo(int); // members of other classes can be friends too
    friend X::X(char), X::~X(); // constructors and destructors can be friends
};
 
// friend declaration does not declare a member function
// this operator<< still needs to be defined, as a non-member
std::ostream& operator<<(std::ostream& out, const Y& y)
{
    return out << y.data; // can access private member Y::data
}

// mutable
struct Test
{
private:
	mutable int n;
public:
	void f() const
	{
		n++;
	}
};
int main()
{
	const Test t;
	t.f();
}

// files 
ifs.seekg(offset, origin) // offset (chislo v bytove)
	ofs.seekp(oft, org)

	ifs.seekg(10, ios::beg) 
	
	ifs.seekg(-10, ios::end) 
	
	ifs.seekg(-1, ios::cur) // potoka se vrushta s edin byte
	
	int count = 10; //trqbva da go napravim v const char*
out.write((char*)&count ,sizeof(count))	//nai lesen nachin na Armqnov ne go haresva mnogo (c-style casting(reinterpret_cast))

file.getline(t, 50) <=> char t[50]; file >> t // razlikata m-u dvete e che >> shte chete do tab space ili newline
file.ignore(count, symbol) // skipva do simvol
// types of initializing
int x(3) <=> int x = 3 </=> int {3
//Narrowing Conversions:
//
//int x{3.14}; would cause a compile-time error because it tries to convert a double to int, which is a narrowing conversion.
//int x = 3.14; would compile but truncate the value to 3.


// wierd function explanation:  int f(int x)&&;
class MyClass {
public:
    // Member function that can only be called on rvalue objects
    int f(int x) && {
        return x * 2;
    }

    // Regular member function that can be called on any object
    int g(int x) {
        return x + 2;
    }
};

int main() {
    MyClass obj;

    // This will not compile, because obj is an lvalue
    // int result1 = obj.f(5); // Error: lvalue 'obj' cannot bind to '&&'

    // This will compile, because std::move(obj) is an rvalue
    int result2 = std::move(obj).f(5);

    // Regular member function can be called on both lvalues and rvalues
    int result3 = obj.g(5);
    int result4 = MyClass().g(5);

    std::cout << "result2: " << result2 << std::endl; // Output: 10
    std::cout << "result3: " << result3 << std::endl; // Output: 7
    std::cout << "result4: " << result4 << std::endl; // Output: 7

    return 0;
}


// move semantika na derived class 
	// Move constructor
    Derived(Derived&& other) noexcept : /*!!!*/Base(std::move(other))/*!!!*/, derivedSize(other.derivedSize), derivedData(other.derivedData) {
        other.derivedSize = 0;
        other.derivedData = nullptr;
    }

    // Move assignment operator
    Derived& operator=(Derived&& other) noexcept {
        if (this == &other) return *this; // Self-assignment check
 /*!!!*/Base::operator=(std::move(other)); /*!!!*/ // Move base class part
        delete[] derivedData;
        derivedSize = other.derivedSize;
        derivedData = other.derivedData;
        other.derivedSize = 0;
        other.derivedData = nullptr;
        return *this;
    }
	
	
// ppc virtualni operatori da se definirat ne e dobra ideq!!!

// virtualno nasledqvane se izpolzva za multiple inheritence, opravqneto na diamanteniq problem i vuvejdaneto na specialni policita
// The class to be made final
class Final;
 
// used to make the Final class final
class MakeFinal {
private:
    MakeFinal() { cout << "MakFinal constructor" << endl; }
    friend class Final;
};
 
class Final : virtual MakeFinal {
public:
    Final() { cout << "Final constructor" << endl; }
};
 
// Compiler error, zashtoto tuk trqbva da izvikame konstruktora na MakeFinal (zashototo toi e virtualno nasleden) no ne moje zashoto e private
class Derived : public Final {
public:
    Derived() { cout << "Derived constructor" << endl; }
};

class Base {
public:
    Base(int value) : value(value) {
        std::cout << "Base constructor called with value: " << value << std::endl;
    }

private:
    int value;
};

class Derived1 : virtual public Base {
public:
    // Constructor of Derived1 does not need to initialize Base
    Derived1(int value) : Base(value) {
        std::cout << "Derived1 constructor called" << std::endl;
    }
};

class Derived2 : virtual public Base {
public:
    // Constructor of Derived2 does not need to initialize Base
    Derived2(int value) : Base(value) {
        std::cout << "Derived2 constructor called" << std::endl;
    }
};

class MostDerived : public Derived1, public Derived2 {
public:
    MostDerived(int value) : Base(value), Derived1(value), Derived2(value) {
        std::cout << "MostDerived constructor called" << std::endl;
    }
};



// typedef function pointers
// typedef <current_name> <new_name>
typedef void (*DrawFunc)();
typedef double (*AreaFunc)();
// Base structure representing a Shape
struct Shape {
    DrawFunc draw;
    AreaFunc area;
};

// another example of functors use 
typedef int(*fri)(int);
using fri = int(*)(int);

int add(int x)
{
    return 2 * x;
}

void hoho(fri func)
{
    int res = func(3);
    std::cout << res;
}

int main()
{
    int a = 2;
    auto f = [](int x) ->int { return x * 3; };
    hoho(f);
}


// operator[] example
T& operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

// here the second its purpose is when dealing with const objects
const T& operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}


// namespace example
namespace first 
{
	int val = 500;
	void foo() { ... }
}

//decltype used
template <typename T1, typename T2>
auto multiply(T1 a, T2 b) -> decltype(a * b) {
    return a * b;
}
template <typename T1, typename T2>
auto add_wrapper(T1 a, T2 b) -> decltype(add(a, b)) {
    return add(a, b);
}
int a = 10;
decltype(a) b = 20;  // b will have the same type as a, which is int



// hmm ! NEW !
//Copy Constructor:
Vector<int> v2 = v1;

//Copy Assignment Operator:
Vector<int> v2;
v2 = v1;



// reinterpret cast !!
//
// !!It can typecast any pointer to any other data type.!!
// reinterpret_cast is a very special and dangerous type of casting operator.
// And is suggested to use it using proper data type i.e., (pointer data type should be same as original data type).

// this initializes the *a with 0
int* a = new int(); // 'a' points to an integer with value 0



// !!! bad practice !!! don't do it
#define MAX_SIZE 512

// array initialization
int arr[13]{};


//when opening a binary file with fstream I should specify if I really want to open it with in and out like this
std::fstream stream("file.bin", std::ios::in | std::ios::out| std::ios::binary);