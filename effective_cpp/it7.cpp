#include <iostream>
/** 
 * rule 1: 
 *      keyword virtual 在析构函数中不能滥用；在结构里使用析构函数时跨语言使用中会导致虚指针在别的语言中不能识别；
 *      析构函数使用virtual的原因是：在delete父类指针时；保证能析构子类的成员；
 *      在继承的关系中；析构函数默认调用父类的析构函数。
 * rule 2:
 *      virtual 在子类重写父类的函数中出现，但不能改变父类函数不是虚函数的本质
 **/
typedef class tag_has_virutal_declare_destruction
{
    char a;
    double b;
    tag_has_virutal_declare_destruction(){}
    virtual ~tag_has_virutal_declare_destruction(){}
}VDES;

typedef class tag_has_no_virutal_declare_destruction
{
    char a;
    double b;
    tag_has_no_virutal_declare_destruction(){}
    ~tag_has_no_virutal_declare_destruction(){}
}NVDES;

class Myclass
{
private:
    char a;
    double b;
public:
    Myclass(/* args */){}
    ~Myclass(){}
};

class A
{
private:
    /* data */
public:
    A(/* args */){}
    ~A(){std::cout << "A" << std::endl;}
};

class B
    : public A
{
private:
    /* data */
public:
    B(/* args */){}
    ~B(){std::cout << "B" << std::endl;}
};



class C
    : public B
{
private:
    /* data */
public:
    C(/* args */){}
    virtual ~C(){std::cout << "C" << std::endl;}
    void cc(){std::cout << "C----------------------" << std::endl; }
};

class D
    :public C
{
private:
    /* data */
public:
    D(/* args */){}
    ~D(){std::cout << "D" << std::endl;}
    virtual void cc(){std::cout << "D----------------------" << std::endl; }
};

int main()
{
    std::cout << sizeof(VDES)  << " " << sizeof(NVDES) << " " << sizeof(Myclass) << std::endl;
    B* p = new D();
    //p->cc();
    delete p;
    return 0;
}