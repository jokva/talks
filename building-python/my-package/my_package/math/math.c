#include <Python.h>

static PyObject *add(PyObject *self, PyObject *args) {
    int x, y;
    if (!PyArg_ParseTuple(args, "ii", &x, &y))
        return NULL;
    return PyLong_FromLong(x + y);
}

static PyMethodDef functions[] = {
    { "add", (PyCFunction) add, METH_VARARGS, "Add" },
    { NULL, },
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "math", // module name
    "module docstring",
    -1, // all state in global vars
    functions
};

PyMODINIT_FUNC PyInit_math(void) {
    return PyModule_Create(&module);
}
