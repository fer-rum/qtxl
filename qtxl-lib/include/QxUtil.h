#pragma once

#include <QHash>
#include <QSet>

/*
 *  This header contains global utility functionality that did not fit anywhere
 * more specific.
 */

namespace qtxl {

/**
 * @brief The ComparisonResult enum provides symbolic names for the default way
 * of representing the result of a comparison:
 * <ul>
 * <li>If the comparing item preceeds the compared with item, the result is
 * &lt; 0 </li>
 * <li> If the comparing item and the compared with item are equal, the result
 * is 0 </li>
 * <li> If the comparing item succeeds the compared with item, the result is
 * &gt; 0 </li>
 * </ul>
 *
 * <p>
 * <b>Caution:</b> only compare ComparisonResults with each other.
 * Do <i>not</i> compare them directly with integer return values of other
 * functions since these retun values may adhere to the rules mentioned above
 * but be numerically different from the definitions of the enumeration value,
 * resulting in a false negative.
 * @see qtxl::asComparisonResult()
 */
enum ComparisonResult {
    Precedes    = -1,
    Equals       = 0,
    Succeeds    = 1
};

/**
 * @brief asComparisonResult transforms an integer that is the result of a
 * comparison function into a @see qtxl::ComparisonResult
 * @param retunValue is the integer value that was provided by the
 * comparison function.
 * @return the ComparisonResult that corresponds with the passed integer.
 */
ComparisonResult asComparisonResult(int retunValue);

/**
 * @brief keysforValue iterates through a given QHash and filters out all keys
 * that are associated with a specific value.
 * @param fromHash is the hash trhough which to iterate.
 * @param value is the value for which to filter. Values are compared by using
 * the operator==().
 * @return a set containing all keys whose associated values matched the
 * requested value.
 */
template <typename KeyType, typename ValueType>
QSet<KeyType> keysForValue(QHash<KeyType, ValueType> const& fromHash,
                           ValueType const& value);

}
