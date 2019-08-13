import setuptools
my_math = setuptools.Extension('my_package.math',
    sources = ['my_package/math/math11.cpp'],
    extra_compile_args = ['-std=c++11'],
)

setuptools.setup(
    name = 'my-project',
    version = '0.0.1',
    author = 'Mechazawa',
    license = 'BSD',
    ext_modules = [my_math],
    packages = ['my_package'],
)
