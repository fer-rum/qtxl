#pragma once

#include <QString>

namespace qtxl {

/**
 * @brief The IsQStringConvertible class provides a minimal outline for
 * everything that can be converted to a QString.
 */
class IsQStringConvertible {

public:
    virtual QString toQString() const = 0;
};

}
