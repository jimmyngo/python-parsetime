#!/usr/bin/env python

from distutils.core import setup, Extension
import sys

if sys.version < '2.2.3':
    from distutils.dist import DistributionMetadata
    DistributionMetadata.classifiers = None
    DistributionMetadata.download_url = None

parsetime = Extension('parsetime',
                libraries=['l'],
                define_macros=[('PYTHON_MODULE', None)],
                sources=['at.c', 'panic.c', 'parsetime.c', 'perm.c', 'posixtm.c', 'y.tab.c', 'lex.yy.c'],
                extra_compile_args=['-DHAVE_CONFIG_H',
                                    '-DVERSION=\"3.1.14\"',
                                    '-DETCDIR=\"/etc\"',
                                    '-DLOADAVG_MX=0.8',
                                    '-DDAEMON_USERNAME=\"daemon\"',
                                    '-DDAEMON_GROUPNAME=\"daemon\"',
                                    '-DLFILE=\"/var/spool/cron/atjobs/.SEQ\"'])

setup(name='python-parsetime',
      version='1.5',
      author='Daniel Pearson',
      author_email='daniel@nanoo.org',
      url='http://www.nanoo.org/parsetime/',
      download_url='https://github.com/jimmyngo/python-parsetime',
      description='A parser for date/time strings.',
      long_description='''
ParseTime is a simple Python extension module that simply wraps the parsetime()
function that is used internally by the familiar "at" command that is typically
found on Unix systems. This allows a programmer to parse a complicated
expression that represents a particular point in time.''',
      classifiers=['Development Status :: 5 - Production/Stable',
            'Intended Audience :: Developers',
            'License :: OSI Approved :: GNU General Public License (GPL)',
            'Natural Language :: English',
            'Programming Language :: C',
            'Programming Language :: Python',
            'Topic :: Software Development :: Libraries :: Python Modules', ],
      ext_modules=[parsetime],
)
