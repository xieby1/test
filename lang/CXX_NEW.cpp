// #define CXX_NEW(constructor, mempool)			\
//  (_dummy_new_mempool = mempool,			\
//   new constructor)

// SBT_INSTR_C_STRUCT *p_instr_c = CXX_NEW (SBT_INSTR_C_STRUCT, &SBT_MEM_pool);

// I am curious about the grammar

class c1
{
public:
    int value;
    c1(){value = 1;};
};

int main(void)
{
    int neverMind;
//    c1 *instance = (new c1(), neverMind=3);
    c1 *instance = (neverMind=3, new c1());
    return instance->value;
}
