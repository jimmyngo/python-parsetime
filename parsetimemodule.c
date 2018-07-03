#include <Python.h>
#include <time.h>
#include "parsetime.h"

struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

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

static PyMethodDef parsetime_methods[] = {
    {"parsetime", (PyCFunction)parsetime_parsetime, METH_VARARGS, "Parse at time syntax"},
    {NULL, NULL}
};

#if PY_MAJOR_VERSION >= 3

static int parsetime_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int parsetime_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}


static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "parsetime",
        NULL,
        sizeof(struct module_state),
        parsetime_methods,
        NULL,
        parsetime_traverse,
        parsetime_clear,
        NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
PyInit_parsetime(void)

#else
#define INITERROR return

void
initparsetime(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("parsetime", parsetime_methods);
#endif

    if (module == NULL)
        INITERROR;
    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException("parsetime.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
