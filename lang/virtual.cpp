class Base
{
public:
    virtual int func(void);
};

int Base::func(void){return 17;}

int main(void)
{
    Base b;
    return b.func();
}
