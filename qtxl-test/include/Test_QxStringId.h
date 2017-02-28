#pragma once

#include <QObject>
#include <QTest>

namespace qtxl {
namespace test {

class Test_QxStringId :
        public QObject {
    Q_OBJECT

private slots:

    void test_defaultConstructor();
    void test_rootElement();
};

} // namespace test
} // namespace qtxl
