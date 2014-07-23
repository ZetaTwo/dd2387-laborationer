#include <iostream>

class A {
public:
    A()
        {std::cout << "The default contructor" << std::endl; }
    A(const A & ref)
        {std::cout << "The copy contructor" << std::endl; }
    ~A()
        {std::cout << "The destructor" << std::endl; }
    A(char * s)
        {std::cout << "Some other constructor " << s << std::endl;}
    A & operator=(const A & s)
        {std::cout << "The assignment operator" << std::endl;
         return *this;}
};

void no_ref(A a) {}
void with_ref(const A & a) {}

int main()
{
    A a("my name is a");
    A b = a;         // vad är skillnaden
    A c(a);          // mellan dessa
    A d;             // tre tekniker?
    d = a;

    no_ref(a);       // Bildas temporära objekt?
    with_ref(a);     // Bildas temporära objekt?

    A *aa = new A[5];
    delete aa;       // Vad kommer att hända?
    return 0;
}
