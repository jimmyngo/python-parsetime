#include <Python.h>
#include <time.h>
#include "parsetime.h"

static PyObject *
parsetime_parsetime(PyObject *self, PyObject *pytimestring)
{
    int argc = 2;
    char *argv[argc];
    const char *timestring;
    time_t result;

    if (!PyArg_ParseTuple(pytimestring, "s", &timestring)) {
        return NULL;
    }

    argv[0] = "parsetime";
    argv[1] = (char*)timestring;

    result = parsetime(argc, argv);
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
