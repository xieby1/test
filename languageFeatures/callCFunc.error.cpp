// just assemble this .cpp file you will find c name conflics with cpp keywords
extern "C"
{
    struct Object
    {
        int *class;
    }
}
extern "C" void cFunc3(int *class);
extern "C" void cFunc1(int new);
extern "C" void cFunc2(int typename);
