#ifndef ENUM_UTILS_HPP
#define ENUM_UTILS_HPP
#include "ppUtils.hpp"

#include <algorithm>
#include <array>
#include <string_view>
#include <functional>
using namespace std::string_view_literals;
#ifdef __cpp_lib_constexpr_string
#define CUBE_TIMER_CONSTEXPR constexpr
#else
#define CUBE_TIMER_CONSTEXPR
#endif

template < typename Type > struct IgnoreEquals {
    Type value;

    template < typename Any >
    constexpr IgnoreEquals& operator=([[maybe_unused]] Any t_val) {
        return *this;
    }

    constexpr explicit IgnoreEquals() : value() {}

    constexpr explicit IgnoreEquals(Type t_value) : value(t_value) {}

    // NOLINTNEXTLINE(hicpp-explicit-conversions)
    constexpr operator Type() const { return value; }

    constexpr IgnoreEquals operator*(const Type& t_value) {
        return IgnoreEquals(t_value);
    }
};

// NOLINTBEGIN(cppcoreguidelines-macro-usage)
#define MAKE_ENUM(enum_name, enum_type, ...) \
    enum enum_name : enum_type { __VA_ARGS__ };

#define NAME_ENTRY(arg) #arg##sv.substr(0, #arg##sv.find_first_of('=') - 1)

#define MAKE_NAMES(array_prefix, enum_name, ...)              \
    constexpr static std::                                    \
        array< std::string_view, MM_COUNT_ARGS(__VA_ARGS__) > \
            array_prefix##_names{{MM_TRANSFORM(NAME_ENTRY, __VA_ARGS__)}};

// NOLINTNEXTLINE(bugprone-macro-parentheses)
#define VALUE_ENTRY(enum_name, arg) IgnoreEquals< enum_name >{} * arg
#define MAKE_VALUES(array_prefix, enum_name, ...)                        \
    constexpr static std::array< enum_name, MM_COUNT_ARGS(__VA_ARGS__) > \
        array_prefix##_values{                                           \
            {MM_TRANSFORM_1(VALUE_ENTRY, enum_name, __VA_ARGS__)}};

#define BETTER_ENUM(enum_name, type, ...)                                      \
    class enum_name {                                                          \
      public:                                                                  \
        MAKE_ENUM(m_enumeration, type, __VA_ARGS__)                            \
      private:                                                                 \
        MAKE_VALUES(m, m_enumeration, __VA_ARGS__)                             \
        MAKE_NAMES(m, m_enumeration, __VA_ARGS__)                              \
        constexpr static std::string_view m_name{#enum_name##sv};              \
        m_enumeration                     m_value;                             \
                                                                               \
      public:                                                                  \
        using value_container = decltype(m_values);                            \
        using value_iterator  = typename value_container::iterator;            \
        using value_type      = typename value_container::value_type;          \
        using name_container  = decltype(m_names);                             \
        using name_iterator   = typename name_container::iterator;             \
        using name_type       = typename name_container::value_type;           \
        using underlying      = type;                                          \
                                                                               \
        /* NOLINTNEXTLINE(hicpp-explicit-conversions)*/                        \
        constexpr enum_name(const m_enumeration& t_val) : m_value(t_val) {}    \
        constexpr operator underlying() const { return m_value; }              \
                                                                               \
        friend constexpr enum_name operator+(const m_enumeration& t_val);      \
                                                                               \
        constexpr static value_container& values() { return m_values; }        \
        constexpr static name_container&  names() { return m_names; }          \
        constexpr static size_t size() { return MM_COUNT_ARGS(__VA_ARGS__); }  \
        constexpr static std::string_view  name() { return m_name; }           \
        constexpr static const value_type& from_string(std::string_view t_name \
        ) {                                                                    \
            const auto* found_ptr = std::find_if(                              \
                m_names.begin(),                                               \
                m_names.end(),                                                 \
                [t_name](auto t_iter_name) { return t_iter_name == t_name; }   \
            );                                                                 \
            auto start_val = m_values.begin();                                 \
            std::advance(                                                      \
                start_val, std::distance(m_names.begin(), found_ptr)           \
            );                                                                 \
            return *start_val;                                                 \
        }                                                                      \
        constexpr name_type to_string() {                                      \
            const auto* found_ptr = std::find_if(                              \
                m_values.begin(),                                              \
                m_values.end(),                                                \
                [this](auto t_iter_val) { return t_iter_val == m_value; }      \
            );                                                                 \
            auto start_name = m_names.begin();                                 \
            std::advance(                                                      \
                start_name, std::distance(m_values.begin(), found_ptr)         \
            );                                                                 \
            return *start_name;                                                \
        }                                                                      \
    };                                                                         \
    constexpr enum_name operator+(const enum_name::m_enumeration& t_val) {     \
        return enum_name(t_val);                                               \
    }                                                                          \
    template <> struct std::hash< enum_name > {                                \
        size_t operator()(const enum_name& t_enum) const noexcept {            \
            return std::hash< type >{}(t_enum);                                \
        }                                                                      \
    };
// NOLINTEND(cppcoreguidelines-macro-usage)
#endif
