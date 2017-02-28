#include <Test_QxStringId.h>

#include <QxStringId.h>

using namespace qtxl;
using namespace qtxl::test;

QTEST_MAIN(Test_QxStringId)

void
Test_QxStringId::test_defaultConstructor() {

    using Representation = QxStringId::Representation;

    QxStringId defaultConstructed{};

    QString globalRepresentation    = defaultConstructed.toQString(Representation::GlobalRepresentation);
    QString localRepresentation     = defaultConstructed.toQString(Representation::LocalRepresentation);

    // Default constructed Elements are always invalid
    QVERIFY(!defaultConstructed.isValid());

    // Representations of invalid QxStringIds are always null
    QVERIFY(globalRepresentation.isNull());
    QVERIFY(localRepresentation.isNull());

    // Invalid elements have a level < 0
    QVERIFY(defaultConstructed.level() < 0);

    QVERIFY(!defaultConstructed.isRoot());
}

void
Test_QxStringId::test_rootElement() {

    QxStringId rootId = QxStringId::rootId;

    // Root Id is always valid
    QVERIFY2(rootId.isValid(),      "RootId should return 'true' for isRoot()");
    QVERIFY2(rootId.isRoot(),       "RootId should return 'true' for isRoot()");
    QVERIFY2(rootId.level() == 0,   "RootId should return '0' for level()");
}
