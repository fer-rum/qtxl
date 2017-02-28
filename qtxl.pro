TEMPLATE = subdirs

SUBDIRS += \
    qtxl-lib \
    qtxl-test

CONFIG += ordered

qtxl-test.depends = qtxl-lib
