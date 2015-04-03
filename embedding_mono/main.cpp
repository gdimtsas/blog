#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  mono_set_dirs("./mono/lib",
                "./mono/etc");
  mono_config_parse(NULL);

  MonoDomain* monoDomain = mono_jit_init_version("embedding_mono_domain",
                                                 "v4.0.30319");

  MonoAssembly* assembly = mono_domain_assembly_open(monoDomain, "Example.dll");
  MonoImage* monoImage = mono_assembly_get_image(assembly);

  // find the Entity class in the image
  MonoClass* entityClass = mono_class_from_name(monoImage, "Example", "Entity");

  // allocate memory for one Entity instance
  MonoObject* entityInstance = mono_object_new(monoDomain, entityClass);

  // find the the default(parameterless) constructor method
  MonoMethod* constructorMethod = mono_class_get_method_from_name(entityClass, ".ctor", 0);

  // and finally invoke it
  MonoObject* exception = NULL;
  mono_runtime_invoke(constructorMethod, entityInstance, NULL, &exception);

  // find the Process method that takes one parameter
  MonoMethod* processMethod = mono_class_get_method_from_name(entityClass, "Process", 1);

  // create a MonoString that will be passed to the Process method as an argument
  MonoString* name = mono_string_new(mono_domain_get(), "Giorgos");
  void* args[1];
  args[0] = name;
  exception = NULL;

  // invoke the method
  mono_runtime_invoke(processMethod, entityInstance, args, &exception);

  // check for any thrown exception
  if(exception)
    {
      std::cout << mono_string_to_utf8(mono_object_to_string(exception, NULL)) << std::endl;
    }

  // shutdown mono
  mono_jit_cleanup(monoDomain);

  return 0;
}
