
#include "UEPyProperty.h"

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 25)

#include "PythonDelegate.h"
#include "PythonFunction.h"
#include "Components/ActorComponent.h"
#include "Engine/UserDefinedEnum.h"

#if WITH_EDITOR
#include "Runtime/AssetRegistry/Public/AssetRegistryModule.h"
#include "ObjectTools.h"
#include "UnrealEd.h"
#include "Runtime/Core/Public/HAL/FeedbackContextAnsi.h"

#include "Wrappers/UEPyFObjectThumbnail.h"
#endif

#include "Runtime/Core/Public/Misc/OutputDeviceNull.h"
#include "Runtime/CoreUObject/Public/Serialization/ObjectWriter.h"
#include "Runtime/CoreUObject/Public/Serialization/ObjectReader.h"
#include <string>



PyObject *get_fproperty_uclass(FProperty *property)
{
	UClass *u_class = nullptr;
	//ue_py_check(self);

	// why was I thinking this - not clear what I was trying to do here
	// return the UClass for an FProperty
	// or return UClass for a python wrapped FProperty??
	// obviously the return seems to be a python wrapped UClass object

	// not clear how to implement this
	// we may just have to check each FProperty class
	// and load the StaticClass of the appropriate UObject

	//u_class = (UClass *)property->ue_fproperty

	Py_RETURN_UOBJECT(u_class);
}


FProperty* FProperty_New(FFieldVariant* scope, FFieldClass* f_class, FName name, EObjectFlags o_flags)
{
	//FArrayProperty *f_array = new FArrayProperty(self->ue_object, UTF8_TO_TCHAR(name), o_flags);

	// for the moment lets just do explicit ifs
	if (f_class == FBoolProperty::StaticClass())
	{
		FBoolProperty *f_prop = new FBoolProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FIntProperty::StaticClass())
	{
		FIntProperty *f_prop = new FIntProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FUInt32Property::StaticClass())
	{
		FUInt32Property *f_prop = new FUInt32Property(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FInt64Property::StaticClass())
	{
		FInt64Property *f_prop = new FInt64Property(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FUInt64Property::StaticClass())
	{
		FUInt64Property *f_prop = new FUInt64Property(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FFloatProperty::StaticClass())
	{
		FFloatProperty *f_prop = new FFloatProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FByteProperty::StaticClass())
	{
		FByteProperty *f_prop = new FByteProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FEnumProperty::StaticClass())
	{
		FEnumProperty *f_prop = new FEnumProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FStrProperty::StaticClass())
	{
		FStrProperty *f_prop = new FStrProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FNameProperty::StaticClass())
	{
		FNameProperty *f_prop = new FNameProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FTextProperty::StaticClass())
	{
		FTextProperty *f_prop = new FTextProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FArrayProperty::StaticClass())
	{
		FArrayProperty *f_prop = new FArrayProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FMapProperty::StaticClass())
	{
		FMapProperty *f_prop = new FMapProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FStructProperty::StaticClass())
	{
		FStructProperty *f_prop = new FStructProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FClassProperty::StaticClass())
	{
		FClassProperty *f_prop = new FClassProperty(*scope, name, o_flags);
		return f_prop;
	}
	else if (f_class == FObjectPropertyBase::StaticClass())
	{
		FObjectPropertyBase *f_prop = new FObjectPropertyBase(*scope, name, o_flags);
		return f_prop;
	}

	UE_LOG(LogPython, Error, TEXT("new property unimplemented property class %s for %s"), TCHAR_TO_UTF8(*f_class->GetName()), *name.ToString());

	return nullptr;
}

#if WITH_EDITOR
// strictly WITH_EDITORONLY_DATA
PyObject *py_ue_fproperty_set_metadata(ue_PyFProperty * self, PyObject * args)
{

	// not clear what to do here - we can have a valid python uobject wrapper
	// with invalid uobject - which is what ue_py_check is testing for
	// can we have a valid python fproperty wrapper with invalid fproperty??
	//ue_py_check(self);
	//if (!ue_is_pyfproperty(self))
	//	return PyErr_Format(PyExc_Exception, "fproperty_set_metadata: self is not FProperty");
	if (self->ue_fproperty == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFProperty is in invalid state");

	char *metadata_key;
	char *metadata_value;
	if (!PyArg_ParseTuple(args, "ss:set_metadata", &metadata_key, &metadata_value))
	{
		return NULL;
	}

	FProperty *f_property = (FProperty *)self->ue_fproperty;
	f_property->SetMetaData(FName(UTF8_TO_TCHAR(metadata_key)), UTF8_TO_TCHAR(metadata_value));

	Py_RETURN_NONE;
}

PyObject *py_ue_fproperty_get_metadata(ue_PyFProperty * self, PyObject * args)
{

	// not clear what to do here - we can have a valid python uobject wrapper
	// with invalid uobject - which is what ue_py_check is testing for
	// can we have a valid python fproperty wrapper with invalid fproperty??
	//ue_py_check(self);
	//if (!ue_is_pyfproperty(self))
	//	return PyErr_Format(PyExc_Exception, "fproperty_get_metadata: self is not FProperty");
	if (self->ue_fproperty == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFProperty is in invalid state");

	char *metadata_key;
	if (!PyArg_ParseTuple(args, "s:get_metadata", &metadata_key))
	{
		return NULL;
	}

	char *metadata_value = nullptr;

	FProperty *f_property = (FProperty *)self->ue_fproperty;
	FString value = f_property->GetMetaData(FName(UTF8_TO_TCHAR(metadata_key)));
	return PyUnicode_FromString(TCHAR_TO_UTF8(*value));

}

PyObject *py_ue_fproperty_has_metadata(ue_PyFProperty * self, PyObject * args)
{

	// not clear what to do here - we can have a valid python uobject wrapper
	// with invalid uobject - which is what ue_py_check is testing for
	// can we have a valid python fproperty wrapper with invalid fproperty??
	//ue_py_check(self);
	//if (!ue_is_pyfproperty(self))
	//	return PyErr_Format(PyExc_Exception, "fproperty_has_metadata: self is not FProperty");
	if (self->ue_fproperty == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFProperty is in invalid state");

	char *metadata_key;
	if (!PyArg_ParseTuple(args, "s:has_metadata", &metadata_key))
	{
		return NULL;
	}

	FProperty *f_property = (FProperty *)self->ue_fproperty;
	if (f_property->HasMetaData(FName(UTF8_TO_TCHAR(metadata_key))))
	{
		Py_INCREF(Py_True);
		return Py_True;
	}
	Py_INCREF(Py_False);
	return Py_False;
}

PyObject* py_ue_fproperty_get_name(ue_PyFProperty* self, PyObject* args) {
	if (self->ue_fproperty == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFProperty is in invalid state");


	FProperty* f_property = (FProperty*)self->ue_fproperty;
	return PyUnicode_FromString(TCHAR_TO_UTF8(*(f_property->GetName())));
}

PyObject* py_ue_fproperty_get_full_name(ue_PyFProperty* self, PyObject* args) {
	if (self->ue_fproperty == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFProperty is in invalid state");


	FProperty* f_property = (FProperty*)self->ue_fproperty;
	return PyUnicode_FromString(TCHAR_TO_UTF8(*(f_property->GetFullName())));
}

PyObject* py_ue_fproperty_get_class(ue_PyFProperty* self, PyObject* args) {
	if (self->ue_fproperty == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFProperty is in invalid state");


	FProperty* f_property = (FProperty*)self->ue_fproperty;
	Py_RETURN_FFIELDCLASS(f_property->GetClass());
}

PyObject* py_ue_fproperty_convert(ue_PyFProperty* self, PyObject* args) {
	if (self->ue_fproperty == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFProperty is in invalid state");


	FProperty* f_property = (FProperty*)self->ue_fproperty;
	return ue_py_convert_property(f_property, (uint8*)f_property, 0);
}

bool is_obj_uobject(PyObject* obj) {
	auto typeName = Py_TYPE(obj)->tp_name;
	return strcmp(typeName, "unreal_engine.UObject") == 0;
}

bool is_obj_struct(PyObject* obj) {
	auto typeName = Py_TYPE(obj)->tp_name;
	return strcmp(typeName, "unreal_engine.UScriptStruct") == 0;
}

uint8* get_obj_ptr(PyObject* obj) {
	if (is_obj_uobject(obj)) {
		auto p = (ue_PyUObject*)(obj);
		return (uint8*)p->ue_object;
	}
	else if (is_obj_struct(obj)) {
		auto p = (ue_PyUScriptStruct*)(obj);
		return p->u_struct_ptr;
	}
	return nullptr;
}

PyObject* py_ue_fproperty_set_length(ue_PyFProperty* self, PyObject* args) {
	if (self->ue_fproperty == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFProperty is in invalid state");


	FProperty* f_property = (FProperty*)self->ue_fproperty;
	auto f_array_property = CastField<FArrayProperty>(f_property);

	if (!f_array_property) {
		return PyErr_Format(PyExc_Exception, "FProperty is not FArrayProperty");
	}


	PyObject* obj_parent;
	int array_length;
	if (!PyArg_ParseTuple(args, "Oi:set_length", &obj_parent, &array_length))
	{
		return NULL;
	}

	uint8* ptr = get_obj_ptr(obj_parent);

	if (ptr == nullptr) {
		return PyErr_Format(PyExc_Exception, "Parent is not valid (%s)", Py_TYPE(obj_parent)->tp_name);
	}

	FScriptArrayHelper_InContainer helper(f_array_property, ptr, 0);

	helper.EmptyAndAddValues(array_length);
	Py_RETURN_TRUE;
}

PyObject* py_ue_fproperty_get_at_index(ue_PyFProperty* self, PyObject* args) {
	if (self->ue_fproperty == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFProperty is in invalid state");


	FProperty* f_property = (FProperty*)self->ue_fproperty;
	auto f_array_property = CastField<FArrayProperty>(f_property);

	if (!f_array_property) {
		return PyErr_Format(PyExc_Exception, "FProperty is not FArrayProperty");
	}

	PyObject* obj_parent;
	int index;
	if (!PyArg_ParseTuple(args, "Oi:get_at_index", &obj_parent, &index))
	{
		return NULL;
	}

	uint8* obj_ptr = get_obj_ptr(obj_parent);

	if (obj_ptr == nullptr) {
		return PyErr_Format(PyExc_Exception, "Parent is not valid (%s)", Py_TYPE(obj_parent)->tp_name);
	}

	FScriptArrayHelper_InContainer helper(f_array_property, obj_ptr, 0);

	auto inner_prop = f_array_property->Inner;

	uint8* ptr = helper.GetRawPtr(index);
	PyObject* item = ue_py_convert_property(inner_prop, ptr, 0);
	return item;
}

PyObject* py_ue_fproperty_add_key(ue_PyFProperty* self, PyObject* args) {
	if (self->ue_fproperty == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFProperty is in invalid state");


	FProperty* f_property = (FProperty*)self->ue_fproperty;
	auto f_map_property = CastField<FMapProperty>(f_property);

	if (!f_map_property) {
		return PyErr_Format(PyExc_Exception, "FProperty is not FMapProperty");
	}


	PyObject* obj_parent;
	PyObject* py_key;
	if (!PyArg_ParseTuple(args, "OO:add_key", &obj_parent, &py_key))
	{
		return NULL;
	}

	uint8* parent_ptr = get_obj_ptr(obj_parent);

	if (parent_ptr == nullptr) {
		return PyErr_Format(PyExc_Exception, "Parent is not valid (%s)", Py_TYPE(obj_parent)->tp_name);
	}

	FScriptMapHelper_InContainer helper(f_map_property, parent_ptr, 0);

	int32 hindex = helper.AddDefaultValue_Invalid_NeedsRehash();
	uint8* ptr = helper.GetPairPtr(hindex);

	if (!ue_py_convert_pyobject(py_key, f_map_property->KeyProp, ptr, 0)) {
		Py_RETURN_FALSE;
	}

	helper.Rehash();
	Py_RETURN_TRUE;
}

std::string ue_py_fproperty_util_get_type_as_str(FProperty* prop) {
	uint8* buffer = (uint8*)prop;
	int32 index = 0;

	std::string strType = "Uknown";

	if (auto casted_prop = CastField<FBoolProperty>(prop))
	{
		return "BoolProperty";
	}

	if(auto casted_prop = CastField<FIntProperty>(prop))
	{
		return "IntProperty";
	}

	if(auto casted_prop = CastField<FUInt32Property>(prop))
	{
		return "UInt32Property";
	}

	if(auto casted_prop = CastField<FInt64Property>(prop))
	{
		return "Int64Property";
	}

	// this is likely a bug - it was a FInt64Property before
	if(auto casted_prop = CastField<FUInt64Property>(prop))
	{
		return "UInt64Property";
	}

	if(auto casted_prop = CastField<FFloatProperty>(prop))
	{
		return "FloatProperty";
	}

	if(auto casted_prop = CastField<FDoubleProperty>(prop))
	{
		return "DoubleProperty";
	}

	if(auto casted_prop = CastField<FByteProperty>(prop))
	{
		return "ByteProperty";
	}

	if(auto casted_prop = CastField<FEnumProperty>(prop))
	{
		return "EnumProperty";
	}

	if(auto casted_prop = CastField<FStrProperty>(prop))
	{
		return "StrProperty";
	}

	if(auto casted_prop = CastField<FTextProperty>(prop))
	{
		return "TextProperty";
	}

	if(auto casted_prop = CastField<FNameProperty>(prop))
	{
		return "NameProperty";
	}

	if(auto casted_prop = CastField<FObjectPropertyBase>(prop))
	{
		return "ObjectProperty";
	}

	if(auto casted_prop = CastField<FClassProperty>(prop))
	{
		return "ClassProperty";
	}

	// try to manage known struct first
	if(auto casted_prop = CastField<FStructProperty>(prop))
	{
		
		if (auto casted_struct = Cast<UScriptStruct>(casted_prop->Struct))
		{
			if (casted_struct == TBaseStructure<FVector>::Get())
			{
				return "FVector";
			}
			if(casted_struct == TBaseStructure<FVector2D>::Get())
			{
				return "FVector2D";
			}
			if(casted_struct == TBaseStructure<FRotator>::Get())
			{
				return "FRotator";
			}
			if(casted_struct == TBaseStructure<FTransform>::Get())
			{
				return "FTransform";
			}
			if(casted_struct == FHitResult::StaticStruct())
			{
				return "FHitResult";
			}
			if(casted_struct == TBaseStructure<FColor>::Get())
			{
				return "FColor";
			}
			if(casted_struct == TBaseStructure<FLinearColor>::Get())
			{
				return "FLinearColor";
			} 
			return "UScriptStruct";
		}

		return "StructProperty";
	}

	if(auto casted_prop = CastField<FWeakObjectProperty>(prop))
	{
		return "WeakObjectProperty";
	}

	if(auto casted_prop = CastField<FMulticastDelegateProperty>(prop))
	{
		return "MulticastDelegateProperty";
	}

	if(auto casted_prop = CastField<FDelegateProperty>(prop))
	{
		return "DelegateProperty";
	}

	if(auto casted_prop = CastField<FArrayProperty>(prop))
	{
		strType = "ArrayProperty<";
		FScriptArrayHelper_InContainer array_helper(casted_prop, buffer, index);
		FProperty* array_prop = casted_prop->Inner;
		strType.append(ue_py_fproperty_util_get_type_as_str(array_prop));
		strType.append(">");

		return strType;
	}

	if(auto casted_prop = CastField<FMapProperty>(prop))
	{
		strType = "MapProperty<";
		FScriptMapHelper_InContainer map_helper(casted_prop, buffer, index);

		strType.append(ue_py_fproperty_util_get_type_as_str(map_helper.KeyProp));
		strType.append(",");
		strType.append(ue_py_fproperty_util_get_type_as_str(map_helper.ValueProp));

		strType.append(">");

		return strType;
	}

	if(auto casted_prop = CastField<FSetProperty>(prop))
	{
		strType = "SetProperty<";
		FScriptSetHelper_InContainer set_helper(casted_prop, buffer, index);

		FProperty* set_prop = casted_prop->ElementProp;
		strType.append(ue_py_fproperty_util_get_type_as_str(set_prop));
		strType.append(">");
		return strType;
	}

	return strType;
}

PyObject* ue_py_fproperty_get_type_as_str(ue_PyFProperty* self, PyObject* args) {
	if (self->ue_fproperty == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFProperty is in invalid state");


	FProperty* f_property = (FProperty*)self->ue_fproperty;
	auto strType = ue_py_fproperty_util_get_type_as_str(f_property);
	return PyUnicode_FromString(strType.c_str());
	// return PyUnicode_FromString(strType.c_str());
}

PyObject* py_ue_ffield_class_get_name(ue_PyFFieldClass* self, PyObject* args) {
	if(self->ue_ffieldclass == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFFieldClass is in invalid state");

	auto f_field_class = self->ue_ffieldclass;
	return PyUnicode_FromString(TCHAR_TO_UTF8(*(f_field_class->GetName())));
}

PyObject* py_ue_ffield_class_get_default_object(ue_PyFFieldClass* self, PyObject* args) {
	if (self->ue_ffieldclass == nullptr)
		return PyErr_Format(PyExc_Exception, "PyFFieldClass is in invalid state");

	auto f_field_class = self->ue_ffieldclass;
	auto f_field_class_default = (FProperty*)f_field_class->GetDefaultObject();
	Py_RETURN_FPROPERTY(f_field_class_default);
}



#endif

#endif
