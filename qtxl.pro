TEMPLATE = subdirs

SUBDIRS += \
    qtxl-lib \
    qtxl-test \
    qtxl-modular

CONFIG += ordered

qtxl-test.depends = qtxl-lib
qtxl-modular.depends = qtxl-lib
