from setuptools import find_packages, setup

package_name = 'ur_motion_manager'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ali',
    maintainer_email='ali@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
    'console_scripts': [
        'motion_manager_node = ur_motion_manager.motion_manager_node:main',
        'motion_manager_node2 = ur_motion_manager.motion_manager_node2:main', #Ajouté le 16/04
        'teach_node = ur_motion_manager.teach_node:main',
    ],
},

)
