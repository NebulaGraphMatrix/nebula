.PHONY: gcc build release-build release

default: build

NEBULA_THIRDPARTY_ROOT:=/opt/vesoft/third-party/2.0
TOOLSET_BIN_PATH:=/opt/vesoft/toolset/gcc/9.3.0/bin

pre:
	source /opt/vesoft/toolset/gcc/9.3.0/enable; \
	export LD_LIBRARY_PATH=/opt/vesoft/toolset/gcc/9.3.0/lib64:$$LD_LIBRARY_PATH


release-build: pre
	ninja -C release-build -j30

release: pre
	cmake -E make_directory release-build; \
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=on \
			-DNEBULA_THIRDPARTY_ROOT=$(NEBULA_THIRDPARTY_ROOT) \
			-DCMAKE_C_COMPILER=$(TOOLSET_BIN_PATH)/gcc \
			-DCMAKE_CXX_COMPILER=$(TOOLSET_BIN_PATH)/g++ \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
			-DCMAKE_BUILD_TYPE=Release \
			-DCMAKE_INSTALL_PREFIX=$$PWD/install \
			-DENABLE_TESTING=off \
			-DENABLE_COVERAGE=off \
			-DENABLE_ASAN=off \
			-DBUILD_SHARED_LIBS=ON \
			-DGRAPHBLAS_ROOT=$$HOME/Workspace/GraphBLAS/release-install \
			-DLAGRAPH_ROOT=$$HOME/Workspace/LAGraph/release-install \
			-GNinja \
			-B release-build;


gcc: pre
	cmake -E make_directory build; \
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=on \
			-DNEBULA_THIRDPARTY_ROOT=$(NEBULA_THIRDPARTY_ROOT) \
			-DCMAKE_C_COMPILER=$(TOOLSET_BIN_PATH)/gcc \
			-DCMAKE_CXX_COMPILER=$(TOOLSET_BIN_PATH)/g++ \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
			-DCMAKE_BUILD_TYPE=Debug \
			-DCMAKE_INSTALL_PREFIX=$$PWD/install \
			-DENABLE_TESTING=off \
			-DENABLE_COVERAGE=off \
			-DENABLE_ASAN=off \
			-DBUILD_SHARED_LIBS=ON \
			-DGRAPHBLAS_ROOT=$$HOME/Workspace/GraphBLAS/release-install \
			-DLAGRAPH_ROOT=$$HOME/Workspace/LAGraph/release-install \
			-GNinja \
			-B build;

build: pre
	ninja -C build -j30
