/* 
 *  parsetime.c - A Python module that wraps the time parsing function of at(1).
 *  Copyright (C) 2004-2005  Daniel Pearson
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <Python.h>
#include <time.h>
#include "parsetime.h"

static PyObject *
parsetime_parsetime(PyObject *self, PyObject *args)
{
    char **argv;
    int argc, i;
    time_t now;
    time_t result;
    PyObject * retval = NULL;

    argc = PyTuple_Size(args);
    if (!(argv = (char**) malloc(sizeof(char*)*(argc+1))))
        return PyErr_NoMemory();
    argv[argc] = NULL;
    for (i = 0; i < argc; i++)
        if ((argv[i] = PyString_AsString(PyTuple_GetItem(args, i))) == NULL)
            return NULL;

    if ((result = parsetime(time(&now), argc, argv)) != 0)
        retval = Py_BuildValue("i", result);
    free(argv);
    return retval;
}

static PyMethodDef ParseTimeMethods[] = {
  {"parsetime", parsetime_parsetime, METH_VARARGS,
   "Parse a date string into a time similar to that returned by time.time()."},
  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initparsetime(void)
{
    (void) Py_InitModule("parsetime", ParseTimeMethods);
}
