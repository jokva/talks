import setuptools
my_math = setuptools.Extension('my_package.math',
    sources = ['my_package/math/math11.cpp'],
    extra_compile_args = ['-std=c++11'],
)

setuptools.setup(
    ext_modules = [my_math],
    name = 'my-project',
    version = '0.0.1',
    author = 'J Kvalsvik',
    license = 'BSD',
    packages = ['my_package', 'my_package.math'],
)
