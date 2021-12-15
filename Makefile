.PHONY: clang build

default: build

NEBULA_THIRDPARTY_ROOT:=/opt/vesoft/third-party/2.0
TOOLSET_BIN_PATH:=/opt/vesoft/toolset/clang/10.0.0/bin

clang:
	cmake -E make_directory build; \
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=on \
			-DNEBULA_THIRDPARTY_ROOT=$(NEBULA_THIRDPARTY_ROOT) \
			-DCMAKE_C_COMPILER=$(TOOLSET_BIN_PATH)/clang \
			-DCMAKE_CXX_COMPILER=$(TOOLSET_BIN_PATH)/clang++ \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
			-DCMAKE_BUILD_TYPE=Debug \
			-DENABLE_TESTING=on \
			-DENABLE_COVERAGE=on \
			-DENABLE_ASAN=off \
			-DBUILD_SHARED_LIBS=ON \
			-DGRAPHBLAS_ROOT=$$HOME/Workspace/GraphBLAS/install \
			-DLAGRAPH_ROOT=$$HOME/Workspace/LAGraph/build/install \
			-GNinja \
			-B build;

build:
	ninja -C build -j25
