#define expandMe(type, func) static type func(void);
#define expandMe(type, func) static type anothor_##func(void);
expandMe(int, testFunc)
