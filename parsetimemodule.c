#include <Python.h>
#include <time.h>
#include "parsetime.h"

static PyObject *
parsetime_parsetime(PyObject *self, PyObject *pytimestring)
{
    int ret_code = 0;
    int argc = 1;
    char *argv[1];
    const char *timestring;
    time_t result;

    if (!PyArg_ParseTuple(pytimestring, "s", &timestring)) {
        return NULL;
    }

    argv[0] = (char*)timestring;

    ret_code = parsetime(argc, argv, &result);
    if (ret_code == 0) {
        return Py_BuildValue("i", result);
    } else {
        PyErr_SetString(PyExc_ValueError, ErrorMessages[ret_code]);
        return NULL;
    }
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
