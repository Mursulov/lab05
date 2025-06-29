## Изменение 
произошло глобальное измение репозитория 

переписаны тесты (test)
test.cpp
[тык](https://github.com/Mursulov/lab05/blob/main/test.cpp)
   
  был подключен субмодуль гугл тестов 

      git submodule add https://github.com/google/googletest.git && cd googletest && git checkout 7da55820cc32dedd6c1b048f2d4e13fdde5e8237 && cd .. && git add googletest && git commit -m "Add googletest as submodule" && git push origin main

был переделана деректория branking 

[тык](https://github.com/Mursulov/lab05/tree/main/banking)


был переписан build.yml 
name: CMake with Coverage

on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

env:
  BUILD_TYPE: Release
  COMPILER: g++-9
  COVERAGE_TOOL: lcov

jobs:
  build-and-test:
    name: Build and Test with Coverage
    runs-on: ubuntu-24.04

    steps:
    - name: Checkout repository
      uses: actions/checkout@v4
      with:
        submodules: recursive

    - name: Install dependencies
      run: |
        sudo apt-get update -qq
        sudo apt-get install -y \
          ${{env.COMPILER}} \
          ${{env.COVERAGE_TOOL}} \
          cmake \
          make

    - name: Create and prepare build directory
      run: |
        mkdir -p _build
        cd _build

    - name: Configure CMake
      working-directory: _build
      run: |
        cmake \
          -DCOVERAGE=ON \
          -DCMAKE_BUILD_TYPE=${{env.BUILD_TYPE}} \
          -DCMAKE_CXX_COMPILER=${{env.COMPILER}} \
          ..

    - name: Build project
      working-directory: _build
      run: cmake --build . --config ${{env.BUILD_TYPE}} --verbose

    - name: Execute tests
      working-directory: _build
      run: ./RunTest

    - name: Generate coverage data
      working-directory: _build
      run: |
        lcov --capture \
          --directory . \
          --output-file coverage.info \
          --ignore-errors mismatch,unused \
          --rc branch_coverage=1 \
          --rc geninfo_unexecuted_blocks=1

    - name: Filter coverage results
      working-directory: _build
      run: |
        lcov --remove coverage.info \
          '/usr/*' \
          '*/external/*' \
          '*/test/*' \
          '*/gtest/*' \
          '*/gmock/*' \
          --output-file filtered.info \
          --ignore-errors unused

    - name: Generate HTML report
      working-directory: _build
      run: |
        genhtml --branch-coverage \
          --title "Test Coverage Report" \
          --legend \
          --output-directory coverage \
          filtered.info \
          --ignore-errors unmapped,unused

    - name: Upload coverage report
      uses: actions/upload-artifact@v4
      with:
        name: coverage-report
        path: _build/coverage
        retention-days: 7

    - name: Upload coverage to Coveralls
      uses: coverallsapp/github-action@v2
      with:
        github-token: ${{ secrets.GITHUB_TOKEN }}
        path-to-lcov: _build/filtered.info

  

(я вынес test.cpp в основой деректорий из за того что я ловил баг в git action и он не мог нормально сделать biuldcmakelist (linux)
