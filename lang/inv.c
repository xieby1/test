// to test tidle operator '~', bit-wise invert,
// will be compiled to which instruction 
int main(void)
{
    int value = -1; // all bits are 1
    int inv_value = ~value;
    return inv_value;
}
