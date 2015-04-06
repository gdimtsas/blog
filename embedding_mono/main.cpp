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
  mono_config_parse(NULL);

  MonoDomain* monoDomain = mono_jit_init_version("embedding_mono_domain",
                                                 "v4.0.30319");

  MonoAssembly* assembly = mono_domain_assembly_open(monoDomain,
                                                     "Example.dll");
  MonoImage* monoImage = mono_assembly_get_image(assembly);

  // find the Entity class in the image
  MonoClass* entityClass = mono_class_from_name(monoImage,
                                                "Example",
                                                "Entity");

  // allocate memory for one Entity instance
  MonoObject* entityInstance = mono_object_new(monoDomain, entityClass);

  // find the the constructor method that takes one parameter
  MonoMethod* constructorMethod = mono_class_get_method_from_name(entityClass,
                                                                  ".ctor",
                                                                  1);

  // create a MonoString that will be passed to the constructor as an argument
  MonoString* name = mono_string_new(mono_domain_get(), "Giorgos");
  void* args[1];
  args[0] = name;

  // finally, invoke the constructor
  MonoObject* exception = NULL;
  mono_runtime_invoke(constructorMethod, entityInstance, args, &exception);

  // find the Process method that takes zero parameters
  MonoMethod* processMethod = mono_class_get_method_from_name(entityClass,
                                                              "Process",
                                                              0);
  exception = NULL;

  // invoke the method
  // if invoking static methods, then the second argument must be NULL
  mono_runtime_invoke(processMethod, entityInstance, args, &exception);

  // check for any thrown exception
  if(exception)
    {
      std::cout << mono_string_to_utf8(mono_object_to_string(exception, NULL))
                << std::endl;
    }

  // find the GetName method
  MonoMethod* getNameMethod = mono_class_get_method_from_name(entityClass,
                                                              "GetName",
                                                              0);
  exception = NULL;
  MonoString* ret = (MonoString*) mono_runtime_invoke(getNameMethod, entityInstance, NULL, &exception);
  char* c = mono_string_to_utf8(ret);
  std::cout << "Value of 'name' is " << c << std::endl;
  // free the memory allocated from mono_string_to_utf8 ()
  mono_free(c);

  // shutdown mono
  mono_jit_cleanup(monoDomain);

  return 0;
}
