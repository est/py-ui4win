#include "stdafx.h"
#include<boost/python.hpp>

namespace bp = boost::python;

struct duistring_to_pystr {
	static PyObject *convert( const CDuiString &s );
	static PyTypeObject const* get_pytype();
};

struct duistring_from_pystr {
	static void *convertible( PyObject *object );
	static void construct( PyObject *object, boost::python::converter::rvalue_from_python_stage1_data *data );
};

void python_duistring_registration() {
	static bool executed = false;
	if ( !executed ) {
		executed = true;
		using namespace boost::python;

		converter::registry::push_back(
			duistring_from_pystr::convertible, duistring_from_pystr::construct,
			type_id< CDuiString >()
			);
		to_python_converter< CDuiString, duistring_to_pystr, false >();
	}
}

PyObject *duistring_to_pystr::convert( const CDuiString &s ) {
	return PyString_FromString( s.GetData());
}
PyTypeObject const *duistring_to_pystr::get_pytype() {
	return &PyString_Type;
}

void *duistring_from_pystr::convertible( PyObject *object ) {
	return object;
}

void duistring_from_pystr::construct( PyObject *object, boost::python::converter::rvalue_from_python_stage1_data *data ) {
	int len( PyString_Size( object ) );
	if ( len < 0 )
	{
		ATLASSERT(0);
	}
	char* ustr( new char[ len + 1 ] );
	memset(ustr, 0, len+1);
	strcpy(ustr, PyString_AsString( object ));
	if (strlen(ustr) != len )
	{
		ATLASSERT(0);
	}
	
	void *storage = reinterpret_cast<
		boost::python::converter::rvalue_from_python_storage< CDuiString >*
	>( data )->storage.bytes;
	new (storage) CDuiString( ustr );
	data->convertible = storage;
}

