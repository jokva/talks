import skbuild
skbuild.setup(
    name = 'my-project',
    version = '0.0.1',
    author = 'J Kvalsvik',
    license = 'BSD',
    packages = ['my_package', 'my_package.math'],
)
