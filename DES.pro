TEMPLATE = subdirs

SUBDIRS += \
    UI/DEC \
    lib/Database \
    lib/WrapperENSDF \
    lib/ToolWidget

DEC.depends = WrapperENSDF Database ToolWidget
