#include <array>
#include <gtest/gtest.h>
#include <pms/BasicItem.hpp>
#include <pms/fields.hpp>
#include <pms/types.hpp>
#include <string>

using namespace pms;
using std::array;
using std::string;

/**
 * @class Prisoner
 * @brief an example of item class
 */
class Prisoner : public BasicItem<5, TextField, BooleanField, DateField,
                                  TextField, IntegerField> {
private:
    // a type alias for the base class
    using Base = BasicItem<5, TextField, BooleanField, DateField, TextField,
                           IntegerField>;
    // the field names
    static const constexpr array<c_string, Base::get_field_count()>
        field_names = {"name", "in_reading", "admision_time", "student_id",
                       "education_system"};

public:
    using Base::BasicItem;
    Prisoner() = default;
    Prisoner(const Prisoner& rhs) = default;
    Prisoner(Prisoner&& rhs) noexcept = default;

    /**
     * @brief REQUIRED, to get the names of fields
     * @return the array of names of the fields
     */
    static constexpr array<const char*, get_field_count()> get_field_names() {
        return field_names;
    }

    /**
     * @brief REQUIRED, to get the type of the item
     * @return a c-style string containing the type of the item
     */
    static constexpr const char* type() {
        return "Prisoner";
    }
};

TEST(TestItemValue, TestBasicItem) {
    DateField df(Date(2024, 9, 1));
    Prisoner prisoner(TextField("郭金锋"), BooleanField(true), df,
                      TextField("2024303424"), IntegerField(4));
    ASSERT_EQ(prisoner.get_field_count(), 5);
    ASSERT_EQ(prisoner.get_field_value<0>(), string("郭金锋"));
    ASSERT_EQ(prisoner.get_field_value<1>(), true);
    Date value = prisoner.get_field_value<2>();
    ASSERT_EQ(value.year, 2024);
    ASSERT_EQ(value.month, 9);
    ASSERT_EQ(value.day, 1);
    ASSERT_EQ(prisoner.get_field_value<3>(), string("2024303424"));
    ASSERT_EQ(prisoner.get_field_value<4>(), 4);
}

TEST(TestItemStr, TestBasicItem) {
    Prisoner prisoner(TextField("郭金锋"), BooleanField(true),
                      DateField(Date(2024, 9, 1)), TextField("2024303424"),
                      IntegerField(4));
    ASSERT_EQ(prisoner.get_field_str<0>(), string("郭金锋"));
    ASSERT_EQ(prisoner.get_field_str<1>(), string("true"));
    ASSERT_EQ(prisoner.get_field_str<2>(), string("2024-09-01"));
    ASSERT_EQ(prisoner.get_field_str<3>(), string("2024303424"));
    ASSERT_EQ(prisoner.get_field_str<4>(), string("4"));

    array<string, 5> str_arr(prisoner.get_str_fields());
    ASSERT_EQ(str_arr.at(0), string("郭金锋"));
    ASSERT_EQ(str_arr.at(1), string("true"));
    ASSERT_EQ(str_arr.at(2), string("2024-09-01"));
    ASSERT_EQ(str_arr.at(3), string("2024303424"));
    ASSERT_EQ(str_arr.at(4), string("4"));

    array<c_string, 5UL> str_names(prisoner.get_field_names());
    array<c_string, 5UL> field_names({"name", "in_reading", "admision_time",
                                      "student_id", "education_system"});
    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(str_names.at(i), field_names.at(i));
    }
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
