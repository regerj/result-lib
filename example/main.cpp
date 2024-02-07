#include "../Result.h"
#include <cstdio>

// Some error code implemenation is recommended
enum Status {
    SUCCESS = 0,
    GENERAL_FAIL = 1,
    SPECIFIC_FAIL = 2
};

ResultLib::ResultCode<Status> temp = ResultLib::ResultCode<Status>::Ok();

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
