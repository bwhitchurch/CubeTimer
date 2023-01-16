#ifndef ENUM_HPP
#define ENUM_HPP

#include <algorithm>
#include <array>

template < typename E, typename Value, size_t N > struct BiEnum {

  public:
	std::array< std::pair< E, Value >, N > m_enumMap;
	using value_type = std::pair< E, Value >;
	using array_type = std::array< value_type, N >;

	constexpr E operator[](const Value& val) const {
		const auto* found = std::find_if(
			m_enumMap.begin(),
			m_enumMap.end(),
			[val](auto iterVal) { return iterVal.second == val; }
		);
		return found->first;
	}

	constexpr Value operator[](const E& eVal) const {
		const auto* found = std::find_if(
			m_enumMap.begin(),
			m_enumMap.end(),
			[eVal](auto iterVal) { return iterVal.first == eVal; }
		);
		return found->second;
	}
};
#endif
