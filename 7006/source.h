#define DECL_CLASS(X)                            \
    class X                                      \
    {                                            \
    public:                                      \
        X() { cout << "In " #X "()" << endl; }   \
        ~X() { cout << "In ~" #X "()" << endl; } \
    };

#define DECL_CLASS_INH(X, INH)                   \
    class X : INH                                \
    {                                            \
    public:                                      \
        X() { cout << "In " #X "()" << endl; }   \
        ~X() { cout << "In ~" #X "()" << endl; } \
    };

DECL_CLASS(B);
DECL_CLASS_INH(A, B);
DECL_CLASS_INH(C, B);
class D : C, A
{
public:
    D() { cout << "In D()" << endl; }
    ~D() { cout << "In ~D()" << endl; }
};
