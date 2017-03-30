#include <QxUtil.h>

using namespace qtxl;

ComparisonResult
asComparisonResult(int returnValue){

    if(returnValue < 0){
        return ComparisonResult::Precedes;
    } else if(returnValue > 0){
        return ComparisonResult::Succeeds;
    } else {
        return ComparisonResult::Equals;
    }
}

template<typename KeyType, typename ValueType>
QSet<KeyType>
keysForValue(QHash<KeyType, ValueType> const& fromHash,
             ValueType const& value) {

    QSet<KeyType> results;

    QHashIterator<QString, int> iterator(fromHash);
    while (iterator.hasNext()) {
        iterator.next();
        if(iterator.value() == value){
            results.insert(iterator.key());
        }
    }

    return results;
}
