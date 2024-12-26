#ifndef PMS_BASICITEM_HPP
#define PMS_BASICITEM_HPP

#include <array>
#include <pms/fields.hpp>
#include <pms/types.hpp>
#include <tuple>
#include <type_traits>

namespace pms {

/**
 * @brief the base class for information item, the derived classes must provide
 * two static member variables of array<string, field_count> type, containing
 * the fields' names and types.
 * @tparam V the types of the fields
 * @param field_values the count of the fields
 */
template <size_t field_count, typename... V>
class BasicItem {
public:
    // the type alias for the tuple containing the fields
    using Fields = std::tuple<V...>;
    // the string array with the same length as the fields
    using str_array = std::array<string, field_count>;

private:
    // the fields of an item
    Fields fields_;

    /**
     * @brief the base case of the recursive function to iterate the fields
     * @param field_values the string array to receive the string values of the
     * fields
     */
    template <size_t idx = 0>
    typename std::enable_if<(idx == field_count), void>::type
    iterate_fields(str_array& field_strs) const {}

    /**
     * @brief the non-base case of the recursive function to iterate the fields
     * @param field_values the string array to receive the string values of the
     */
    template <size_t idx = 0>
    typename std::enable_if<(idx < field_count), void>::type
    iterate_fields(str_array& field_strs) const {
        field_strs.at(idx) = get_field_str<idx>();
        iterate_fields<idx + 1>(field_strs);
    }

public:
    BasicItem() = default;
    template <typename... Var>
    BasicItem(Var&&... args) : fields_(std::forward<Var>(args)...) {}
    BasicItem(const BasicItem& rhs) = default;
    BasicItem(BasicItem&& rhs) noexcept = default;

    ~BasicItem() = default;

    BasicItem& operator=(const BasicItem& rhs) = default;
    BasicItem& operator=(BasicItem&& rhs) noexcept = default;

    /**
     * @brief get the count of fields
     * @return the count of fields
     */
    static constexpr size_t get_field_count() {
        return field_count;
    }

    /**
     * @brief get the value of the Nth field
     * @tparam N the index of the field in the tuple
     * @return the const reference of the value of the Nth field
     */
    template <size_t N>
    auto get_field_value() const -> const
        decltype(std::get<N>(fields_).value())& {
        return std::get<N>(fields_).value();
    }

    /**
     * @brief get the value of the Nth field
     * @tparam N the index of the field in the tuple
     * @return the reference of the value of the Nth field
     */
    template <typename N>
    auto get_field_value() -> decltype(std::get<N>(fields_).value())& {
        return const_cast<decltype(std::get<N>(fields_).value())&>(
            static_cast<const BasicItem*>(this)->get_field_value<N>());
    }

    /**
     * @brief get the string of the fields
     * @return the string of the field
     */
    template <size_t N>
    typename std::enable_if<(N < field_count), string>::type
    get_field_str() const {
        return std::get<N>(fields_).str();
    }

    /**
     * @brief get the fields' value in string format
     * @return an array of strings containing the fields' values
     */
    str_array get_str_fields() const {
        str_array res;
        iterate_fields(res);
        return res;
    }
};
} // namespace pms
#endif
