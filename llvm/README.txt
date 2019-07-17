llvm目录下建立build
cd llvm
mkdir build & cd build

cmake -G "Unix Makefiles" -DLLVM_ENABLE_ASSERTIONS=On -DCMAKE_BUILD_TYPE=Release ../.
make -j4