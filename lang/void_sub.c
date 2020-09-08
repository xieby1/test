// This snippet is meant to test whether void * substraction is legal.
// 
// Result: Yes
// 
// Noted: void * addition is illegal

int main(void)
{
    int v1;
    double v2;
    void *a = &v1;
    void *b = &v2;
    
    unsigned long c = a - b;

    return 0;
}
