#include <iostream>

class X
{
public:
    X() : m_id(++s_cntr) {}
    int GetId() { std::cout << m_id << std::endl; return m_id;}
    static int Counter(X obj); 
private:
    static int s_cntr; 
    int m_id;
};

int X::s_cntr = 0;
int X::Counter(X obj) 
    {
        obj.m_id = 5;// only if it got X as parameter
        std::cout << obj.m_id << std::endl;
        s_cntr *= 10; 
        return (s_cntr);
    }      

int main()
{
    X x1;
    X x2;

    std::cout << sizeof(x1) << std::endl;
    std::cout << X::Counter(x2) << std::endl;
    std::cout << x1.Counter(x2) << std::endl;
    // std::cout << X::s_cntr << std::endl;
    x1.GetId();
    x2.GetId();
    

    return 0;
}
