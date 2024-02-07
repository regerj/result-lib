#include "Result.h"
#include <cstdio>

int main (int argc, char *argv[]) {
    Result res = Result<>::Err();

    if (res.is_ok()) {
        printf("It is ok!\n");
    } else {
        printf("It is not ok!\n");
    }
    return 0;
}
