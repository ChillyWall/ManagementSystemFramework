#include <gtest/gtest.h>
#include <pms/DateTime.hpp>

TEST(TestComp, TestDateTime) {
    pms::Date d1(2020, 8, 25);
    pms::Date d2(2022, 8, 25);
    pms::Date d3(2022, 10, 25);
    pms::Date d4(2022, 10, 27);

    ASSERT_TRUE(d1 < d2);
    ASSERT_TRUE(d2 < d3);
    ASSERT_TRUE(d3 < d4);

    pms::Time t1(10, 30, 30);
    pms::Time t2(12, 30, 30);
    pms::Time t3(12, 31, 30);
    pms::Time t4(12, 31, 31);

    ASSERT_TRUE(t1 < t2);
    ASSERT_TRUE(t2 < t3);
    ASSERT_TRUE(t3 < t4);

    pms::DateTime dt1(2024, 12, 26, 23, 29, 30);
    pms::DateTime dt2(2024, 12, 26, 23, 29, 31);
    pms::DateTime dt3(2024, 12, 27, 23, 30, 30);

    ASSERT_TRUE(dt1 < dt2);
    ASSERT_TRUE(dt2 < dt3);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
