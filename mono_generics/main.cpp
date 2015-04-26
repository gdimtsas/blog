#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/reflection.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/attrdefs.h>
#include <mono/metadata/blob.h>
#include <mono/metadata/class.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/exception.h>
#include <mono/metadata/image.h>
#include <mono/metadata/loader.h>
#include <mono/metadata/profiler.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/debug-helpers.h>
#include <string>
#include <iostream>

/*
  int main()
  {
  // point to the relevant directories of the Mono installation
  mono_set_dirs("./mono/lib",
  "./mono/etc");

  // load the default Mono configuration file in 'etc/mono/config'
  mono_config_parse(NULL);

  MonoDomain* monoDomain = mono_jit_init_version("embedding_mono_domain",
  "v4.0.30319");
  MonoAssembly* monoAssembly = mono_domain_assembly_open(monoDomain,
  "MonoGenerics.dll");
  MonoImage* monoImage = mono_assembly_get_image(monoAssembly);
  MonoClass* testClass = mono_class_from_name(monoImage,
  "MonoGenerics",
  "TestClass");
  MonoObject* testClassInstance = mono_object_new(monoDomain, testClass);

  // find GenericMember method
  MonoMethod* genericMethod = mono_class_get_method_from_name(testClass,
  "GenericMethod",
  1);

  MonoMethod* helperMethod = mono_class_get_method_from_name(testClass,
  "MakeGenericMethod",
  2);
  MonoReflectionMethod* monoReflectionMethod = mono_method_get_object(monoDomain,
  genericMethod,
  testClass);

  MonoType* monoType = mono_reflection_type_from_name("System.String", monoImage);
  MonoReflectionType* monoReflectionType = mono_type_get_object(monoDomain,
  monoType);

  void* helperArgs[2];
  helperArgs[0] = monoReflectionMethod;
  helperArgs[1] = monoReflectionType;

  MonoObject* exception = NULL;
  MonoObject* boxedResult = mono_runtime_invoke(helperMethod, NULL, helperArgs, NULL);
  MonoMethod* specializedMethod = *(MonoMethod**)mono_object_unbox(boxedResult);

  void* args[1];
  args[0] = mono_string_new(monoDomain, "Finally!");
  exception = NULL;
  mono_runtime_invoke(specializedMethod, testClassInstance, args, &exception);

  // shutdown mono
  mono_jit_cleanup(monoDomain);

  return 0;
  }
*/

int main()
{
  // point to the relevant directories of the Mono installation
  mono_set_dirs("./mono/lib",
                "./mono/etc");

  // load the default Mono configuration file in 'etc/mono/config'
  mono_config_parse(NULL);

  MonoDomain* monoDomain = mono_jit_init_version("embedding_mono_domain",
                                                 "v4.0.30319");
  MonoAssembly* monoAssembly = mono_domain_assembly_open(monoDomain,
                                                         "MonoGenerics.dll");
  MonoImage* monoImage = mono_assembly_get_image(monoAssembly);
  MonoClass* testClass = mono_class_from_name(monoImage,
                                              "MonoGenerics",
                                              "TestClass");


  //======

  // load the System.Reflection assembly
  MonoAssembly* systemAssembly = mono_domain_assembly_open(monoDomain,
                                                           "mono/lib/mono/4.5/mscorlib.dll");
  MonoImage* systemImage = mono_assembly_get_image(systemAssembly);

  // find the MethodInfo class
  MonoClass* methodInfoClass = mono_class_from_name(systemImage,
                                                    "System.Reflection",
                                                    "MonoMethod");

  // find the MethodInfo::MakeGenericMethod(Type) method
  MonoMethod* makeGenericMethod = mono_class_get_method_from_name(methodInfoClass,
                                                                  "MakeGenericMethod",
                                                                  1);

  // find GenericMember method
  MonoMethod* genericMethod = mono_class_get_method_from_name(testClass,
                                                              "GenericMethod",
                                                              1);

  MonoReflectionMethod* monoReflectionMethod = mono_method_get_object(monoDomain,
                                                                      genericMethod,
                                                                      testClass);

  MonoType* monoType = mono_reflection_type_from_name("System.String", monoImage);
  MonoReflectionType* monoReflectionType = mono_type_get_object(monoDomain,
                                                                monoType);

  MonoObject* exception = NULL;
  MonoArray* array = mono_array_new(monoDomain, mono_class_from_mono_type(monoType), 1);
  mono_array_set(array, MonoReflectionType*, 0, monoReflectionType);
  void* helperArgs[1];
  helperArgs[0] = array;

  MonoObject* boxedResult = mono_runtime_invoke(makeGenericMethod, monoReflectionMethod, helperArgs, &exception);
  if (exception)
    {
	  std::cout << mono_string_to_utf8(mono_object_to_string(exception, NULL)) << std::endl;
	  return 0;
    }
  MonoReflectionMethod* specializedMethod = *(MonoReflectionMethod**)mono_object_unbox(boxedResult);

  void* args[1];
  args[0] = mono_string_new(monoDomain, "Finally!");
  exception = NULL;
  MonoObject* testClassInstance = mono_object_new(monoDomain, testClass);
  //mono_runtime_invoke(specializedMethod, testClassInstance, args, &exception);

  // shutdown mono
  mono_jit_cleanup(monoDomain);

  return 0;
}
