#include <Python.h>
#include <time.h>
#include "parsetime.h"

static PyObject *
parsetime_parsetime(PyObject *self, PyObject *pyargs)
{
    char *argv[1];
    const char *args;
    time_t result;

    if (!PyArg_ParseTuple(pyargs, "s", &args)) {
        return NULL;
    }
    argv[0] = args;
    result = parsetime(1, argv);
    return Py_BuildValue("i", result);
}

static PyMethodDef ParsetimeMethods[] = {
    {"parsetime", parsetime_parsetime, METH_VARARGS, "Parse at time syntax"},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

PyMODINIT_FUNC
initparsetime(void)
{
    (void) Py_InitModule("parsetime", ParsetimeMethods);
}
