python-parsetime
================

python-parsetime is a simple Python wrapper around parsetime.c from UNIX "at" command.
This implementation was taken from FreeBSD with modifications made to handle more cases.

Installation
============

To build the C version 'parsetime' for use on the command line:

    make

To build the Python C extension module:

    python setup.py build

This package should otherwise be available in PyPI and can be install via:

    pip instll python-parsetime

Usage
=====
The parsetime module contains a single function `parsetime`. The `parsetime`
function takes a single string argument for the time specification string and
returns the evaluated time in epoch seconds.

    >>> import parsetime
    >>> parsetime.parsetime('AM Mar 24 2000')
    953874000
    >>> import time
    >>> time.ctime(parsetime.parsetime('11AM Nov 11 1918'))
    'Mon Nov 11 11:00:00 1918'
    >>> time.ctime(parsetime.parsetime('5PM Jan 11 2015 + 20min'))
    'Sun Jan 11 17:20:00 2015'
    >>> time.ctime(parsetime.parsetime('5PM Jan 11 2015 + 20.5min'))
    'Sun Jan 11 17:20:30 2015'

Credits
=======
parsetime.c was copied from FreeBSD's "at" implementation.

> Copyright (C) 1993, 1994 Thomas Koenig
>
> Copyright (C) 1993       David Parsons
