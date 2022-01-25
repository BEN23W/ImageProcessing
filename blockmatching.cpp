#include <python.h>
#include <thread.h>

static PyObject *GenError






PyMethodDef blockmatchMethods[] = {
	{ "run", (PyCFunction)py_blockmatch, METH_VARARGS, "Block matching (image_in, image_out, max_threads)" },
	{ NULL, NULL, 0, NULL }
};


static struct PyModuleDef blockmatchmodule = {
	PyModuleDef_HEAD_INIT,
	"blockmatch",   /* name of module */
	"blockmatch Module C++", /* module documentation, may be NULL */
	-1,       /* size of per-interpreter state of the module,
			  or -1 if the module keeps state in global variables. */
	blockmatchMethods
};

PyMODINIT_FUNC
PyInit_blockmatch(void)
{
	PyObject *m = PyModule_Create(&blockmatchmodule);

	if (m == NULL)
		return NULL;

	GenError = PyErr_NewException("blockmatch.error", NULL, NULL);
	Py_INCREF(GenError);
	PyModule_AddObject(m, "error", GenError);

	return m;

}