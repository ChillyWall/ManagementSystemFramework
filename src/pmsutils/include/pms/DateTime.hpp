#ifndef PMS_DATETIME_HPP
#define PMS_DATETIME_HPP

#include <pms/types.hpp>

namespace pms {

struct Date {
    Integer year;
    Integer month;
    Integer day;

    /**
     * @brief the default constructor, set the date to 0-01-01
     */
    Date() : year(0), month(1), day(1) {}
    Date(const Date& rhs) = default;
    Date(Date&& rhs) noexcept = default;
    ~Date() noexcept = default;

    Date& operator=(const Date& rhs) = default;
    Date& operator=(Date&& rhs) noexcept = default;

    /**
     * @brief construct a date with year, month, this constructor will
     * also check the validity of the date
     * @param y the year
     * @param m the month
     * @param d the day
     */
    Date(Integer y, Integer m, Integer d) : year(y) {
        if (m <= 12 && m >= 1) {
            month = m;
        } else {
            throw std::invalid_argument("invalid month");
        }

        if (d <= 31 && d >= 1) {
            day = d;
        } else {
            throw std::invalid_argument("invalid day");
        }

        if (d == 31 && (m == 2 || m == 4 || m == 6 || m == 9 || m == 11)) {
            throw std::invalid_argument("invalid date");
        }

        if (d == 29 && m == 2 &&
            (y % 4 != 0 || (y % 100 == 0 && y % 400 != 0))) {
            throw std::invalid_argument("invalid date");
        }
    }
};

struct Time {
    Integer hour;
    Integer minute;
    Integer second;

    Time() : hour(0), minute(0), second(0) {}
    Time(const Time& rhs) = default;
    Time(Time&& rhs) noexcept = default;
    ~Time() noexcept = default;

    Time& operator=(const Time& rhs) = default;
    Time& operator=(Time&& rhs) noexcept = default;

    /**
     * @brief construct a time field with hour, minute, and second, this
     * constructor will also check the validity of the time
     * @param h the hour
     * @param m the minute
     * @param s the second
     */
    Time(Integer h, Integer m, Integer s) {
        if (h < 24 && h >= 0) {
            hour = h;
        } else {
            throw std::invalid_argument("invalid hour");
        }

        if (m < 60 && m >= 0) {
            minute = m;
        } else {
            throw std::invalid_argument("invalid minute");
        }

        if (s < 60 && s >= 0) {
            second = s;
        } else {
            throw std::invalid_argument("invalid second");
        }
    }
};

struct DateTime : public Date, public Time {
    DateTime() = default;
    DateTime(const DateTime& rhs) = default;
    DateTime(DateTime&& rhs) noexcept = default;

    DateTime(Integer y, Integer mon, Integer d, Integer h, Integer min,
             Integer sec)
        : Date(y, mon, d), Time(h, min, sec) {}

    ~DateTime() noexcept = default;

    DateTime& operator=(const DateTime& rhs) = default;
    DateTime& operator=(DateTime&& rhs) noexcept = default;
};
} // namespace pms
#endif
