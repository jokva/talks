import setuptools
my_math = setuptools.Extension('my_package.math',
    sources = ['my_package/math/math.c'],
)

setuptools.setup(
    ext_modules = [my_math],
    name = 'my-project',
    version = '0.0.1',
    author = 'Mechazawa',
    license = 'BSD',
    packages = ['my_package', 'my_package.math'],
)
