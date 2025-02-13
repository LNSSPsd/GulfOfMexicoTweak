TARGET := iphone:clang:latest:7.0
ARCHS := arm64 arm64e
INSTALL_TARGET_PROCESSES = Maps


include $(THEOS)/makefiles/common.mk

TWEAK_NAME = gulfofmexicotweak

gulfofmexicotweak_FILES = Tweak.cpp
gulfofmexicotweak_CFLAGS = -fobjc-arc

include $(THEOS_MAKE_PATH)/tweak.mk
