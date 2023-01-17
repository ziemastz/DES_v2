TEMPLATE = subdirs

SUBDIRS += \
    UI/DEC \
    lib/WrapperENSDF
#lib/libENSDFReader

DEC.depends = WrapperENSDF
