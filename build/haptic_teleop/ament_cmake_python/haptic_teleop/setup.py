from setuptools import find_packages
from setuptools import setup

setup(
    name='haptic_teleop',
    version='0.0.0',
    packages=find_packages(
        include=('haptic_teleop', 'haptic_teleop.*')),
)
