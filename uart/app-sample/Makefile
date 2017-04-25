# 6Harmonics Inc.
# maintainer: Qige Zhao
# 2016.11.16 - 2017.03.14

include $(TOPDIR)/rules.mk

APP_NAME:=app-demo
PKG_NAME:=app-sample
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)_$(PKG_VERSION)-$(PKG_RELEASE)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Application sample of package
  MAINTAINER:=Qige Zhao <qigezhao@gmail.com>
#  DEPENDS:=+libiwinfo
endef

define Package/$(PKG_NAME)/description
  Application sample when start a new package.
  Including Makefile, base structure, description.
  And a startup main() function.
endef


define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

#define Build/Configure
#endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/usr/sbin

	$(INSTALL_CONF) $(PKG_BUILD_DIR)/$(PKG_NAME).conf 	$(1)/etc/config/$(APP_NAME)
	$(INSTALL_BIN) 	$(PKG_BUILD_DIR)/$(PKG_NAME).init 	$(1)/etc/init.d/$(APP_NAME)
	$(INSTALL_BIN) 	$(PKG_BUILD_DIR)/$(APP_NAME) 		$(1)/usr/sbin/$(APP_NAME)
endef

$(eval $(call BuildPackage,$(PKG_NAME)))



