#pragma once

#include <qtxl_global.h>

#include <QDate>

namespace qtxl {

class QTXLSHARED_EXPORT Version {

private:
    uint m_major;
    uint m_minor;
    uint m_patch;
    QDate m_date;

public:

    Version(uint major          = 0,
            uint minor          = 0,
            uint patch          = 0,
            QDate const& date   = QDate::currentDate());
    Version(QDate const& date);

    ~Version() = default;
    Version(Version const& other) = default;

    // --- Getters ---
    uint major() const;
    uint minor() const;
    uint patch() const;
    QDate date() const;

    // --- Operators ---
    bool operator==(Version const& other) const;
    bool operator!=(Version const& other) const;

    bool operator< (Version const& other) const;
    bool operator> (Version const& other) const;
    bool operator<=(Version const& other) const;
    bool operator>=(Version const& other) const;

    // --- Utility functions ---
    bool compatibleWith(Version const& other) const;
};

}
