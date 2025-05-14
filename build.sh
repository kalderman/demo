clean=false
clobber=false
test=false

while [ "$#" -gt 0 ]; do
  case "$1" in
    -clean) clean=true; shift 1;;
    -clobber) clobber=true; clean=true; shift 1;;
    -test) test=true; shift 1;;
    -h) echo "Usage:";
        echo "       -clean: Removes build artifacts.";
        echo "       -clobber: Cleans and updates dependencies.";
        echo "       -test: Executes unit tests.";
        exit 0;;
    -*) echo "Error: unknown option $1" >&2; exit 1;;
  esac
done

builddir='bin'

if [ ${clean} = true ]; then
  echo "Removing build artifacts"
  rm -rf ${builddir}
fi

if [ ${clobber} = true ]; then
  echo "Removing dependencies"
  conan remove "*" -c
fi

echo "Install dependencies"
conan install . --output-folder=${builddir} --build=missing -pr default

echo "Build"
cd ${builddir}

if [ ${test} = true ]; then
  cmake .. -DCMAKE_TOOLCHAIN_FILE=${builddir}/build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=RELEASE -DENABLE_COVERAGE=ON
  cmake --build .

  echo "Test"
  make coverage
else
  cmake .. -DCMAKE_TOOLCHAIN_FILE=${builddir}/build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
  cmake --build .
fi