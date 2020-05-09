#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdint>

template <typename T>
constexpr T min(T a, T b)
{
    return a < b ? a : b;
}

template <typename T>
constexpr T max(T x, T y)
{
    return x > y ? x : y;
}

// READ THIS FIRST ---> https://en.wikipedia.org/wiki/Single_Compilation_Unit
#include "./common_print.cpp"
#include "./common_string.cpp"
#include "./common_config.cpp"

int main()
{
    reload_config_file("./assets/config.vars");

    for (int var = 0; var < CONFIG_VAR_CAPACITY; ++var) {
        auto name = config_var_as_string_view((Config_Var) var);
        print(stdout, "#define ", name, " ");
        switch (config_types[var]) {
        case CONFIG_TYPE_INT: {
            println(stdout, config_values[var].int_value);
        } break;

        case CONFIG_TYPE_FLOAT: {
            println(stdout, config_values[var].float_value, "f");
        } break;

        case CONFIG_TYPE_NONE: {
            println(stderr,
                    "[ERROR] Could not find the type definition of ", name, " variable. ",
                    "Please add it to the init_config_types() function.");
            abort();
        } break;
        }
    }

    return 0;
}
