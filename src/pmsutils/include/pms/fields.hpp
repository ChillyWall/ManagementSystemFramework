#ifndef PMS_FIELDS_HPP
#define PMS_FIELDS_HPP

#include <cstdint>
#include <fmt/base.h>
#include <fmt/format.h>
#include <stdexcept>
#include <string>

using std::string;
using Integer = std::int64_t;

template <typename T>
class BasicField {
private:
    T value_;

public:
    BasicField() {}

    /**
     * @brief the constructor with perfect forwarding to send args to value
     * @tparam V the type of value
     * @param val the value
     */
    template <typename... V>
    explicit BasicField(V&&... args) : value_(std::forward<V>(args)...) {}

    BasicField(const BasicField& rhs) = default;
    BasicField(BasicField&& rhs) noexcept : value_(std::move(rhs.value_)) {}
    ~BasicField() noexcept = default;

    BasicField& operator=(const BasicField& rhs) = default;
    BasicField& operator=(BasicField&& rhs) noexcept {
        value_ = std::move(rhs.value_);
        return *this;
    }

    /**
     * @brief get the value
     * @return the const reference of the value
     */
    const T& value() const {
        return value_;
    }

    /**
     * @brief get the value
     * @return the reference of the value
     */
    T& value() {
        return const_cast<T&>(static_cast<const BasicField*>(this)->value());
    }

    /**
     * @brief convert the value to string
     * @return the value string
     */
    virtual string str() const {
        return fmt::to_string(value_);
    }
};

using TextText = BasicField<string>;
using IntegerField = BasicField<Integer>;
using BooleanField = BasicField<bool>;

struct Date {
    Integer year;
    Integer month;
    Integer day;

    /**
     * @brief the default constructor, set the date to 0-01-01
     */
    Date() : year(0), month(1), day(1) {}

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
    DateTime(Integer y, Integer mon, Integer d, Integer h, Integer min,
             Integer sec)
        : Date(y, mon, d), Time(h, min, sec) {}
};

/**
 * @class DateField
 * @brief the field for date
 */
class DateField : BasicField<Date> {
public:
    using BasicField<Date>::BasicField;

    DateField(const DateField& rhs) = default;

    /**
     * @brief get the year
     * @return the year
     */
    Integer year() const {
        return BasicField<Date>::value().year;
    }

    /**
     * @brief get the month
     * @return the month
     */
    Integer month() const {
        return BasicField<Date>::value().month;
    }

    /**
     * @brief get the day
     * @return the day
     */
    Integer day() const {
        return BasicField<Date>::value().day;
    }

    /**
     * @brief get the date in specific format
     * @param fmt_str the format string, uses {0}, {1}, {2} to represent year,
     * month, and day
     * @return the date string
     */
    string str(const string& fmt_str) const {
        return fmt::format(fmt_str, year(), month(), day());
    }

    /**
     * @brief get the date in string type, formatted as "yy-mm-dd"
     * @return the date string
     */
    string str() const override {
        return str("{}-{}-{}");
    }
};

/**
 * @class TimeField
 * @brief the field for time
 */
class TimeField : BasicField<Time> {
public:
    using BasicField<Time>::BasicField;

    /**
     * @brief get the hour
     * @return the hour
     */
    Integer hour() const {
        return BasicField<Time>::value().hour;
    }

    /**
     * @brief get the minute
     * @return the minute
     */
    Integer minute() const {
        return BasicField<Time>::value().minute;
    }

    /**
     * @brief get the second
     * @return the second
     */
    Integer second() const {
        return BasicField<Time>::value().second;
    }

    /**
     * @brief get the time in specific format
     * @param fmt_str the format string, uses {0}, {1}, {2} to represent hour,
     * minute, and second
     * @return the time string
     */
    string str(const string& fmt_str) const {
        return fmt::format(fmt_str, hour(), minute(), second());
    }

    /**
     * @brief get the date in string type, formatted as "h:m:s"
     * @return the time string
     */
    string str() const override {
        return str("{:02}:{:02}:{:02}");
    }
};

/**
 * @class DateTimeField
 * @brief the field for date and time
 */
class DateTimeField : public BasicField<DateTime> {
public:
    using BasicField<DateTime>::BasicField;

    /**
     * @brief get the year
     * @return the year
     */
    Integer year() const {
        return BasicField<DateTime>::value().year;
    }

    /**
     * @brief get the month
     * @return the month
     */
    Integer month() const {
        return BasicField<DateTime>::value().month;
    }

    /**
     * @brief get the day
     * @return the day
     */
    Integer day() const {
        return BasicField<DateTime>::value().day;
    }

    /**
     * @brief get the hour
     * @return the hour
     */
    Integer hour() const {
        return BasicField<DateTime>::value().hour;
    }

    /**
     * @brief get the minute
     * @return the minute
     */
    Integer minute() const {
        return BasicField<DateTime>::value().minute;
    }

    /**
     * @brief get the second
     * @return the second
     */
    Integer second() const {
        return BasicField<DateTime>::value().second;
    }

    /**
     * @brief get the date time in specific format
     * @param fmt_str the format string, uses {0}, {1}, {2}, {3}, {4}, {5} to
     * represent year, month, day, hour, minute, and second
     * @return the date time string
     */
    string str(string fmt_str) const {
        return fmt::format(fmt_str, year(), month(), day(), hour(), minute(),
                           second());
    }

    /**
     * @brief convert the field to string, in format "y-m-d h:m:s"
     * @return the date time string
     */
    string str() const override {
        return str("{:04}-{:02}-{:02} {:02}:{:02}:{:02}");
    }
};

#endif
