ParseTime
=========
By Daniel Pearson <daniel@nanoo.org>

ParseTime is a simple Python extension module that simply wraps the parsetime()
function that is used internally by the familiar "at" command that is typically
found on Unix systems. This allows a programmer to parse a complicated
expression that represents a particular point in time. ParseTime was originally
created for the sole purpose of developing the sleeptill command, which was, in
turn, merely created to allow the user to schedule one-time jobs that should be
executed in the foreground of a terminal (instead of in the background, as is
done by "at"). You could, of course, use the plain old "sleep" command to do
the same thing, if you were willing to perform some rather annoying arithmetic
instead of the familiar syntax of the "at" command.

INSTALLATION

The library code from a lex implementation must be available to build this
module. Installing flex should satisfy this requirement on Unix systems. I
don't know of any lex implementations for Windows or MacOS Classic, so if you
want to build this on those platforms, you're on your own.

Your Python installation must also include the tools required for building
Python extension modules (i.e. distutils). Many Linux distributions put these
tools in a package that is separate from the main Python package. For instance,
on Debian the "python-dev" package must be installed.

After unpacking the source distribution archive, run the command "python
setup.py install" as root. If you are on a Unix system and you don't want to
install the module system-wide, use "python setup.py install --home=~" instead.
See Installing Python Modules for more advanced information on how to install
third-party Python modules.

USAGE

This Python module contains only a single function, named "parsetime". It
accepts a variable number of string arguments which are joined to form a time
specification expression. This expression is evaluated and (if valid) will be
returned in the form of an integer that counts the number of seconds between
the beginning of the epoch and the time specified. The syntax of a time
specification is the same as that used for the arguments to the "at" command
that is commonly found on Unix systems.

For example:
>>> import parsetime
>>> parsetime.parsetime('7AM Mar 24 2000')
953874000
>>> import time
>>> time.ctime(parsetime.parsetime('7AM Mar 24 2000'))
'Fri Mar 24 07:00:00 2000'
>>> time.ctime(parsetime.parsetime('7AM', 'Mar', '24', '2000'))
'Fri Mar 24 07:00:00 2000'
>>> time.ctime(parsetime.parsetime('4pm + 3 days'))
'Sun Jan 4 16:00:00 2004'
>>> time.ctime(parsetime.parsetime('next week'))
'Thu Jan 8 19:54:00 2004'
>>> time.ctime(parsetime.parsetime('3:15pm next Tuesday'))
'Tue Jan 6 15:15:00 2004'

CREDITS

I (Daniel Pearson) can only take credit for the code in parsetime.c, which
merely binds the function to Python, and for the minimal work involved in
extracting the time-parsing code from the rest of the "at" source code. The
code that does the real hard work was written by the authors of "at", Thomas
Koenig and David Parsons.

Copyright (C) 2003 Daniel Pearson <daniel@nanoo.org>
Copyright: 1993, 1994, 1995, 1996, 1997 (c) Thomas Koenig
           1993 (c) David Parsons

This program is free software, and can be redistributed and/or modified under
the terms of the GNU General Public License (GPL).
