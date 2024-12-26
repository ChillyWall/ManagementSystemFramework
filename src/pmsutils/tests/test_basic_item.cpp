#include <array>
#include <gtest/gtest.h>
#include <pms/BasicItem.hpp>
#include <pms/fields.hpp>
#include <pms/types.hpp>
#include <string>

using namespace pms;
using std::array;
using std::string;

template <typename T>
using arr = std::array<T, 5>;

/**
 * @class Student
 * @brief an example of item class
 */
class Student : public BasicItem<5, TextField, BooleanField, DateField,
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
    Student() = default;
    Student(const Student& rhs) = default;
    Student(Student&& rhs) noexcept = default;

    /**
     * @brief REQUIRED, to get the names of fields
     * @return the array of names of the fields
     */
    static constexpr array<c_string, get_field_count()> get_field_names() {
        return field_names;
    }

    /**
     * @brief get the name of the field
     * @param idx the index of the field
     * @return the c-style string containing the name of the field
     */
    static constexpr c_string get_field_name(size_t idx) {
        return field_names.at(idx);
    }

    /**
     * @brief REQUIRED, to get the type of the item
     * @return a c-style string containing the type of the item
     */
    static constexpr const char* type() {
        return "Student";
    }
};

arr<c_string> field_names({"name", "in_reading", "admision_time", "student_id",
                           "education_system"});
DateField df(Date(2024, 9, 1));
Student prisoner(TextField("郭金锋"), BooleanField(true), df,
                 TextField("2024303424"), IntegerField(4));
arr<c_string> values = {"郭金锋", "true", "2024-09-01", "2024303424", "4"};

TEST(TestItemValue, TestItem) {
    ASSERT_EQ(prisoner.get_field_count(), 5);
    ASSERT_EQ(prisoner.get_field_value<0>(), "郭金锋");
    ASSERT_EQ(prisoner.get_field_value<1>(), true);
    Date value = prisoner.get_field_value<2>();
    ASSERT_EQ(value.year, 2024);
    ASSERT_EQ(value.month, 9);
    ASSERT_EQ(value.day, 1);
    ASSERT_EQ(prisoner.get_field_value<3>(), "2024303424");
    ASSERT_EQ(prisoner.get_field_value<4>(), 4);
}

TEST(TestItemStr, TestItem) {
    ASSERT_EQ(prisoner.get_field_str<0>(), values.at(0));
    ASSERT_EQ(prisoner.get_field_str<1>(), values.at(1));
    ASSERT_EQ(prisoner.get_field_str<2>(), values.at(2));
    ASSERT_EQ(prisoner.get_field_str<3>(), values.at(3));
    ASSERT_EQ(prisoner.get_field_str<4>(), values.at(4));

    array<string, 5> str_arr(prisoner.get_field_strs());
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(str_arr.at(i), values.at(i));
    }
}

TEST(TestItemNames, TestItem) {
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(prisoner.get_field_name(i), field_names.at(i));
    }

    arr<c_string> str_names(prisoner.get_field_names());
    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(str_names.at(i), field_names.at(i));
    }
}

TEST(TestItemTypes, TestItem) {
    arr<c_string> types = {"Text", "Boolean", "Date", "Text", "Integer"};
    ASSERT_EQ(prisoner.get_field_type<0>(), types.at(0));
    ASSERT_EQ(prisoner.get_field_type<1>(), types.at(1));
    ASSERT_EQ(prisoner.get_field_type<2>(), types.at(2));
    ASSERT_EQ(prisoner.get_field_type<3>(), types.at(3));
    ASSERT_EQ(prisoner.get_field_type<4>(), types.at(4));

    arr<c_string> str_types(prisoner.get_field_types());
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(str_types.at(i), types.at(i));
    }
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
