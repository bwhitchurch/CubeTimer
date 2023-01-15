#include "internal_use_only/config.hpp"

#include "fmt/format.h"

void sayHello(){
    fmt::print("Hello from version {} of libFoo!\n", cubetimer::cmake::project_version);
}
