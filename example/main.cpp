#include "../Result.h"
#include <cstdio>

enum Status {
    SUCCESS = 0,
    GENERAL_FAIL = 1,
    SPECIFIC_FAIL = 2
};

using ShallowResult = ResultLib::Result<Status>;
template <typename ResultT>
using DeepResult = ResultLib::Result<Status, ResultT>;

int main (int argc, char *argv[]) {
    auto res = ShallowResult::Err();

    if (res.is_ok()) {
        printf("It is ok!\n");
    } else {
        printf("It is not ok!\n");
    }
    return 0;
}
