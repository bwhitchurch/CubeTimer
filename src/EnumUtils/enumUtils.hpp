#ifndef ENUM_UTILS_HPP
#define ENUM_UTILS_HPP

#define MAKE_ENUM(NAME,TYPE,...) \
    enum class NAME : TYPE {__VA_ARGS__};

#include <functional>
#include <initializer_list>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

template < typename Enum > struct ReflectiveEnum {
    private:
    static std::vector< Enum >                     sequence_values;
    static std::unordered_map< Enum, std::string > enum_names;
    static std::unordered_map< std::string, Enum > names_to_enums;
    public:

    ReflectiveEnum()= default;

    // cppcheck-suppress noExplicitConstructor ; because initializer list
    // should support var = {l1, l2, l3} syntax.
    ReflectiveEnum(
        std::initializer_list< std::pair< Enum, std::string > > t_enum_name_list
    )
        : ReflectiveEnum() {
        for (const auto& enum_pair : t_enum_name_list) {
            sequence_values.push_back(enum_pair.first);
            enum_names.insert(enum_pair);
            names_to_enums.insert({enum_pair.second, enum_pair.first});
        }
    }

    Enum& operator[](const std::string& t_name) {
        return names_to_enums[t_name];
    }

    const Enum& operator[](const std::string& t_name) const {
        return names_to_enums.at(t_name);
    }

    std::string& operator[](const Enum& t_val) { return enum_names[t_val]; }

    const std::string& operator[](const Enum& t_val) const {
        return enum_names.at(t_val);
    }

    typename std::vector< Enum >::iterator begin() {
        return sequence_values.begin();
    }

    typename std::vector< Enum >::const_iterator begin() const {
        return sequence_values.begin();
    }

    typename std::vector< Enum >::const_iterator cbegin() const {
        return sequence_values.cbegin();
    }

    typename std::vector< Enum >::iterator end() {
        return sequence_values.end();
    }

    typename std::vector< Enum >::const_iterator end() const {
        return sequence_values.end();
    }

    typename std::vector< Enum >::const_iterator cend() const {
        return sequence_values.cend();
    }

    friend std::ostream& operator << (std::ostream& t_os, const Enum& t_e_val);
};

template <class Enum>
std::ostream& operator << (std::ostream& t_os, const Enum& t_e_val);
#endif
