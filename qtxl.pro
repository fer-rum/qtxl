TEMPLATE = subdirs

SUBDIRS += \
    qtxl-lib \
    qtxl-test

qtxl-test.depends = qtxl-lib
