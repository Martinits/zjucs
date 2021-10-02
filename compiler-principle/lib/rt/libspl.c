#include<math.h>
#include <assert.h>

//    name    ret type     params type  isvararg
// {"printf", Int32Ty(),  {Int8PtrTy()}, true },
// {"scanf",  Int32Ty(),  {Int8PtrTy()}, true },
// {"abs_i",  Int32Ty(),  {Int32Ty()},   false},
// {"abs_d",  DoubleTy(), {DoubleTy()},  false},
// {"chr",    Int8Ty(),   {Int32Ty()},   false},
// {"ord",    Int32Ty(),  {Int8Ty()},    false},
// {"odd",    Int1Ty(),   {Int32Ty()},   false},
// {"pred_i", Int32Ty(),  {Int32Ty()},   false},
// {"pred_c", Int8Ty(),   {Int8Ty()},    false},
// {"succ_i", Int32Ty(),  {Int32Ty()},   false},
// {"succ_c", Int8Ty(),   {Int8Ty()},    false},
// {"sqr_i",  Int32Ty(),  {Int32Ty()},   false},
// {"sqr_d",  DoubleTy(), {DoubleTy()},  false},
// {"sqrt_i", Int32Ty(),  {Int32Ty()},   false},
// {"sqrt_d", DoubleTy(), {DoubleTy()},  false}

int abs_i(int n){
    return (int)fabs((double)n);
}

double abs_d(double n){
    return fabs(n);
}

char chr(int n){
    assert(n>=0 && n<=255);
    return '\0'+n;
}

int ord(char n){
    return (int)n;
}

unsigned char odd(int n){
    return n%2 ? 0x01 : 0x00;
}

int pred_i(int n){
    return n-1;
}

char pred_c(char n){
    return n-1;
}

int succ_i(int n){
    return n+1;
}

char succ_c(char n){
    return n+1;
}

int sqr_i(int n){
    return n*n;
}

double sqr_d(double n){
    return n*n;
}

double sqrt_i(int n){
    return sqrt(n);
}

double sqrt_d(double n){
    return sqrt(n);
}