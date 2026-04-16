from setuptools import find_packages
from setuptools import setup

setup(
    name='unity_robotics_ira2',
    version='0.0.0',
    packages=find_packages(
        include=('unity_robotics_ira2', 'unity_robotics_ira2.*')),
)
