#https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/CrossCompiling
# this one is important
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR $ENV{PJ_ARCH})
set(CONFIGURE_HOST $ENV{PJ_HOST})
#this one not so much
set(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
set(CMAKE_C_COMPILER "$ENV{PJ_CROSS}gcc")
set(CMAKE_CXX_COMPILER "$ENV{PJ_CROSS}g++")
message(">> CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(">> CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE $ENV{PJ_ARCH})
message(">> CPACK_DEBIAN_PACKAGE_ARCHITECTURE: ${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

# where is the target environment
set(CMAKE_FIND_ROOT_PATH)
list(APPEND CMAKE_FIND_ROOT_PATH $ENV{PJ_SYSROOT})
list(APPEND CMAKE_FIND_ROOT_PATH $ENV{SDK_ROOT_DIR})
message(">> CMAKE_FIND_ROOT_PATH: ${CMAKE_FIND_ROOT_PATH}")

# for libraries and headers in the target directories
# this is for cross compile
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

# make VERBOSE=1
#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_FLAGS "$ENV{CC_EXT} $ENV{CFLAGS}")
set(CMAKE_CXX_FLAGS "$ENV{CXX_EXT} $ENV{CXXFLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "$ENV{LDFLAGS}")
message(">> CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message(">> CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(">> CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")

# sysroot
#set(CMAKE_SYSROOT "/opt/fsl-imx-wayland/5.10-hardknott/sysroots/cortexa53-crypto-poky-linux")
#message(">> CMAKE_SYSROOT: ${CMAKE_SYSROOT_LINK}")

# openssl
set(OPENSSL_EXECUTABLE "$ENV{PJ_OPENSSL_EXECUTABLE}")
message(">> OPENSSL_EXECUTABLE: ${OPENSSL_EXECUTABLE}")

# PKG_CONFIG_PATH
# dpkg -L libssl1.1
# dpkg -L libcurl4
set(ENV{PKG_CONFIG_PATH} "$ENV{PJ_PKG_CONFIG}")
message(">> PKG_CONFIG_PATH: $ENV{PKG_CONFIG_PATH}")

# RPATH
message(">> PJ_INSTALL_RPATH: $ENV{PJ_INSTALL_RPATH}")
#set(CMAKE_EXE_LINKER_FLAGS -Wl,-rpath,$ENV{PJ_INSTALL_RPATH})
#set(CMAKE_BUILD_RPATH $ENV{PJ_INSTALL_RPATH})
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
#set(CMAKE_SKIP_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "$ENV{PJ_INSTALL_RPATH}")
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)