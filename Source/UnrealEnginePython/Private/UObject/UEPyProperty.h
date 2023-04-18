#pragma once



#include "UEPyModule.h"

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 25)
PyObject *get_fproperty_uclass(FProperty *);
FProperty* FProperty_New(FFieldVariant* scope, FFieldClass* f_class, FName name, EObjectFlags o_flags);
#if WITH_EDITOR
// strictly WITH_EDITORONLY_DATA
PyObject *py_ue_fproperty_set_metadata(ue_PyFProperty * self, PyObject * args);
PyObject *py_ue_fproperty_get_metadata(ue_PyFProperty * self, PyObject * args);
PyObject *py_ue_fproperty_has_metadata(ue_PyFProperty * self, PyObject * args);
PyObject* py_ue_fproperty_get_name(ue_PyFProperty* self, PyObject* args);
PyObject* py_ue_fproperty_get_full_name(ue_PyFProperty* self, PyObject* args);
PyObject* py_ue_fproperty_get_class(ue_PyFProperty* self, PyObject* args);
PyObject* py_ue_fproperty_convert(ue_PyFProperty* self, PyObject* args);

PyObject* py_ue_ffield_class_get_name(ue_PyFFieldClass* self, PyObject* args);
PyObject* py_ue_ffield_class_get_default_object(ue_PyFFieldClass* self, PyObject* args);
#endif
#endif

