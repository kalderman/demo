clean=false
clobber=false
test=false
compiler="Visual Studio 15 2017 Win64"

while [ "$#" -gt 0 ]; do
  case "$1" in
    -c) compiler=$2; shift 2;;
    -clean) clean=true; shift 1;;
    -clobber) clobber=true; clean=true; shift 1;;
    -test) test=true; shift 1;;
    -h) echo "Usage:";
        echo "       -c: Specify compiler (default: ${compiler}).";
        echo "       -clean: Removes build artifacts.";
        echo "       -clobber: Cleans and updates dependencies.";
        echo "       -test: Executes unit tests.";
        exit 0;;
    -*) echo "Error: unknown option $1" >&2; exit 1;;
  esac
done

if [ ${clean} = true ]; then
  echo "Removing build artifacts"
  rm -rf build
  mkdir build
fi

if [ ${clobber} = true ]; then
  echo "Removing dependencies"
  rm -rf deps
  mkdir deps

  echo "Get dependencies"
  cd deps
  git clone --depth 1 --branch 3.3.4 https://github.com/glfw/glfw
  git clone --depth 1 --branch v3.1.0 https://github.com/cginternals/glbinding
  git clone --depth 1 --branch v2.13.7 https://github.com/catchorg/Catch2
  cd ..
fi

echo "Build"
cd build
cmake -G ''"${compiler}"'' -std=c++17 .. && cmake --build .

if [ ${test} = true ]; then
    echo "Test"
    make test
fi