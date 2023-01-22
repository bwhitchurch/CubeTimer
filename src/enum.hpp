/*!
 * @file enum.hpp
 * @brief Helper functions and classes for working with enumerators.
 * @author Brandon M. Whitchurch
 * @version 0.0.1
 * @date 2023-01-16
 */
#ifndef ENUM_HPP
#define ENUM_HPP

#include <algorithm>  // for find_if
#include <array>      // for array
#include <cstddef>    // for size_t
#include <utility>    // for pair

/*!
 * @brief BiEnumTraits traits class for BiEnum
 *
 * @tparam Enum enumerator type. Either plain enum or enum class is acceptable.
 * @tparam Value
 * @tparam N
 */
template < typename Enum, typename Value, size_t N > struct BiEnumTraits {
    /*!
     * @brief type of element stored in array.
     */
    using element_type = std::pair< Enum, Value >;
    /*!
     * @brief typedef for the array type to be used as a map.
     */
    using array_type = std::array< element_type, N >;
};

/*!
 * @brief BiEnum is a bidirectional enum. I.e. one that allows converting
 * between enum labels and string representations
 *
 * @tparam Enum
 * @tparam Value
 * @tparam N
 */
template < typename Enum, typename Value, size_t N > struct BiEnum {

    /*!
     * @brief type traits for the BiEnum.
     */
    using traits_type = BiEnumTraits< Enum, Value, N >;
    /*!
     * @brief array of pairs to function as contexpr map
     */
    typename traits_type::array_type m_enum_map;

    /*!
     * @brief Search the map by Value, the second member of the pair type.
     *
     * @param val
     *
     * @return Enum label that corresponds with val.
     */
    constexpr Enum operator[](const Value& t_val) const {
        const auto* found_ptr = std::find_if(
            m_enum_map.begin(),
            m_enum_map.end(),
            [t_val](auto t_iter_val) { return t_iter_val.second == t_val; }
        );
        return found_ptr->first;
    }

    /*!
     * @brief Search the map b Enum, the first member of the pair type.
     *
     * @param eVal
     *
     * @return Value correponding with the enum label.
     */
    constexpr Value operator[](const Enum& t_e_val) const
    requires(!std::is_same_v< Enum, Value >)
    {
        const auto* found_ptr = std::find_if(
            m_enum_map.begin(),
            m_enum_map.end(),
            [t_e_val](auto t_iter_val) { return t_iter_val.first == t_e_val; }
        );
        return found_ptr->second;
    }
};
#endif
