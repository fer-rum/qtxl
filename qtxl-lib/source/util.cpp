#include <util.h>

using namespace qtxl;

ComparisonResult asComparisonResult(int returnValue){

    if(returnValue < 0){
        return ComparisonResult::Precedes;
    } else if(returnValue > 0){
        return ComparisonResult::Succeeds;
    } else {
        return ComparisonResult::Equals;
    }
}
