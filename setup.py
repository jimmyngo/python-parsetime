#!/usr/bin/env python

from distutils.core import setup, Extension
import sys

if sys.version < '2.2.3':
    from distutils.dist import DistributionMetadata
    DistributionMetadata.classifiers = None
    DistributionMetadata.download_url = None

parsetime = Extension('parsetime',
                      define_macros=[('PYTHON_MODULE', None)],
                      sources=['parsetimemodule.c', 'parsetime.c'])

setup(name='python-parsetime',
      version='2.0.6',
      author='Jimmy Ngo',
      author_email='jingo@linkedin.com',
      url='https://github.com/jimmyngo/python-parsetime',
      download_url='https://github.com/jimmyngo/python-parsetime',
      description='Parse for at time strings.',
      long_description='''Parsetime is a parser for string in the at
      time format. It is a light Python wrapper around modified version
      of parsetime from FreeBSD.
      ''',
      license='Apache License 2.0',
      classifiers=['Development Status :: 5 - Production/Stable',
            'Intended Audience :: Developers',
            'License :: OSI Approved :: Apache Software License',
            'Natural Language :: English',
            'Programming Language :: C',
            'Programming Language :: Python',
            'Topic :: Software Development :: Libraries :: Python Modules', ],
      ext_modules=[parsetime],
)
