#ifndef PP_UTILS_HPP
#define PP_UTILS_HPP
// NOLINTBEGIN(cppcoreguidelines-macro-usage)
/******************************************************************************
 *                              Object Literals                               *
 ******************************************************************************/
#define T_PARENS ()
#define T_LPAREN (
#define T_RPAREN )
#define T_COMMA ,

/******************************************************************************
 *                              Basic Functions                               *
 ******************************************************************************/
#define MM_ID(arg)              arg
#define MM_CONCAT(arg_a, arg_b) arg_a##arg_b
#define MM_STRINGIFY(arg)       #arg
#define MM_STRINGIFY_M(arg)     MM_STRINGIFY(arg)

/*!
 * Macros that will cause unexpanded macros in __VA_ARGS__ to be expanded.
 * Current max depth is 2^8
 */
#define MM_EXPAND(...)   MM_EXPAND_8(__VA_ARGS__)
#define MM_EXPAND_1(...) __VA_ARGS__
#define MM_EXPAND_2(...) MM_EXPAND_1(MM_EXPAND_1(__VA_ARGS__))
#define MM_EXPAND_3(...) MM_EXPAND_2(MM_EXPAND_2(__VA_ARGS__))
#define MM_EXPAND_4(...) MM_EXPAND_3(MM_EXPAND_3(__VA_ARGS__))
#define MM_EXPAND_5(...) MM_EXPAND_4(MM_EXPAND_4(__VA_ARGS__))
#define MM_EXPAND_6(...) MM_EXPAND_5(MM_EXPAND_5(__VA_ARGS__))
#define MM_EXPAND_7(...) MM_EXPAND_6(MM_EXPAND_6(__VA_ARGS__))
#define MM_EXPAND_8(...) MM_EXPAND_7(MM_EXPAND_7(__VA_ARGS__))

/******************************************************************************
 *                             High Order Macros                              *
 ******************************************************************************/
/*!
 * Applies macro to each argument int the trailing argument list
 */
#define MM_FOR_EACH(macro, ...) \
    __VA_OPT__(MM_EXPAND(MM_FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define MM_FOR_EACH_HELPER(macro, _1, ...) \
    macro(_1) __VA_OPT__(MM_FOR_EACH_AGAIN T_PARENS(macro, __VA_ARGS__))
#define MM_FOR_EACH_AGAIN() MM_FOR_EACH_HELPER

#define MM_TRANSFORM(macro, ...) \
    __VA_OPT__(MM_EXPAND(MM_TRANSFORM_HELPER(macro, __VA_ARGS__)))
#define MM_TRANSFORM_HELPER(macro, _1, ...)                   \
    macro(_1) __VA_OPT__(                                     \
        T_COMMA MM_TRANSFORM_AGAIN T_PARENS T_LPAREN macro,   \
        __VA_ARGS__                                  T_RPAREN \
    )
#define MM_TRANSFORM_AGAIN() MM_TRANSFORM_HELPER

#define MM_TRANSFORM_1(macro, ...) \
    __VA_OPT__(MM_EXPAND(MM_TRANSFORM_HELPER_1(macro, __VA_ARGS__)))
#define MM_TRANSFORM_HELPER_1(macro, _1, _2, ...)             \
    macro(_1, _2) __VA_OPT__(                                 \
        T_COMMA MM_TRANSFORM_AGAIN_1 T_PARENS T_LPAREN macro, \
        _1,                                                   \
        __VA_ARGS__ T_RPAREN                                  \
    )
#define MM_TRANSFORM_AGAIN_1() MM_TRANSFORM_HELPER_1
/*!
 * Calls macro(_1, arg) for each arg in the variadic argument list
 */
#define MM_FOR_EACH_1(macro, _1, ...) \
    __VA_OPT__(MM_EXPAND(MM_FOR_EACH_HELPER_1(macro, _1, __VA_ARGS__)))
#define MM_FOR_EACH_HELPER_1(macro, _1, _2, ...) \
    macro(_1, _2)                                \
        __VA_OPT__(MM_FOR_EACH_AGAIN_1 T_PARENS(macro, _1, __VA_ARGS__))
#define MM_FOR_EACH_AGAIN_1() MM_FOR_EACH_HELPER_1

/*!
 * Calls macro(a,b) on the first two arguments in the variadic list. The next
 * call is generated as macro(macro(a,b), c) and so on until all arguments are
 * consumed.
 */
#define MM_FOLD_LEFT(macro, ...) \
    __VA_OPT__(MM_EXPAND(MM_FOLD_LEFT_HELPER(macro, __VA_ARGS__)))
#define MM_FOLD_LEFT_HELPER(macro, _1, _2, ...)              \
    __VA_OPT__(MM_FOLD_LEFT_AGAIN T_PARENS T_LPAREN macro, ) \
    macro(_1, _2) __VA_OPT__(, __VA_ARGS__ T_RPAREN)
#define MM_FOLD_LEFT_AGAIN() MM_FOLD_LEFT_HELPER

#define MM_INCREMENT(arg)       ((arg) + 1)
#define MM_COUNT_IF(sum, arg_b) MM_INCREMENT(sum)
#define MM_COUNT_ARGS(...)      MM_FOLD_LEFT(MM_COUNT_IF, 0, __VA_ARGS__)

// NOLINTEND(cppcoreguidelines-macro-usage)
#endif
