#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  // point to the relevant directories of the Mono installation
  mono_set_dirs("./mono/lib",
                "./mono/etc");

  // load the default Mono configuration file in 'etc/mono/config'
  mono_config_parse(nullptr);

  MonoDomain* monoDomain = mono_jit_init_version("embedding_mono_domain",
                                                 "v4.0.30319");

  // open our Example.dll assembly
  MonoAssembly* assembly = mono_domain_assembly_open(monoDomain,
                                                     "Example.dll");
  MonoImage* monoImage = mono_assembly_get_image(assembly);

  // find the Entity class in the image
  MonoClass* entityClass = mono_class_from_name(monoImage,
                                                "Example",
                                                "Entity");

  // allocate memory for one Entity instance
  MonoObject* entityObject = mono_object_new(monoDomain, entityClass);

  // find the constructor method that takes one parameter
  MonoMethod* constructorMethod = mono_class_get_method_from_name(entityClass,
                                                                  ".ctor",
                                                                  1);

  // create a MonoString that will be passed to the constructor as an argument
  MonoString* name = mono_string_new(mono_domain_get(), "Giorgos");
  void* args[1];
  args[0] = name;

  // finally, invoke the constructor
  MonoObject* exception = nullptr;
  mono_runtime_invoke(constructorMethod, entityObject, args, &exception);

  // find the Process method that takes zero parameters
  MonoMethod* processMethod = mono_class_get_method_from_name(entityClass,
                                                              "Process",
                                                              0);
  exception = nullptr;

  // invoke the method
  // if invoking static methods, then the second argument must be null
  mono_runtime_invoke(processMethod, entityObject, nullptr, &exception);

  // check for any thrown exception
  if(exception)
    {
      std::cout << mono_string_to_utf8(mono_object_to_string(exception, nullptr))
                << std::endl;
    }

  // find the GetName method
  MonoMethod* getNameMethod = mono_class_get_method_from_name(entityClass,
                                                              "GetName",
                                                              0);
  exception = nullptr;
  MonoString* ret = (MonoString*) mono_runtime_invoke(getNameMethod, entityObject, nullptr, &exception);
  char* c = mono_string_to_utf8(ret);
  std::cout << "Value of 'Name' is " << c << std::endl;
  // free the memory allocated from mono_string_to_utf8 ()
  mono_free(c);

  // find the Id field in the Entity class
  MonoClassField* idField = mono_class_get_field_from_name(entityClass, "Id");
  int value = 42;

  // set the field's value
  mono_field_set_value(entityObject, idField, &value);

  int result;
  mono_field_get_value(entityObject, idField, &result);
  std::cout << "Value of 'Id' is " << result << std::endl;

  // shutdown mono
  mono_jit_cleanup(monoDomain);

  return 0;
}
