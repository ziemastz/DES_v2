TEMPLATE = subdirs

SUBDIRS += \
    UI/DEC \
    lib/WrapperENSDF \
    lib/ToolWidget

DEC.depends = WrapperENSDF
