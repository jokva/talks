import setuptools
my_math = setuptools.Extension('my_package.math',
    sources = ['my_package/math/math.c'],
)

setuptools.setup(
    name = 'my-project',
    version = '0.0.1',
    author = 'Mechazawa',
    license = 'BSD',
    ext_modules = [my_math],
    packages = ['my_package'],
)
