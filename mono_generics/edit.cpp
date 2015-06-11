#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <string>
#include <iostream>
 
void printMethodSignature(MonoMethod* method)
{
  std::cout << "method signature: "
            << mono_method_full_name(method , true) << std::endl;
}
 
void checkException(MonoObject* ex)
{
  if(ex)
    {
      std::cout << mono_string_to_utf8(mono_object_to_string(ex, NULL)) << std::endl;
      exit(1);
    }
}
 
int main()
{
  // point to the relevant directories of the Mono installation
  mono_set_dirs("./mono/lib",
                "./mono/etc");
 
  // load the default Mono configuration file in 'etc/mono/config'
  mono_config_parse(NULL);
 
  MonoDomain* monoDomain = mono_jit_init_version("mono_domain",
                                                 "v4.0.30319");
  MonoAssembly* monoAssembly = mono_domain_assembly_open(monoDomain,
                                                         "Example.dll");
  MonoImage* monoImage = mono_assembly_get_image(monoAssembly);
  MonoClass* testClass = mono_class_from_name(monoImage,
                                              "MonoGenerics",
                                              "TestClass");
 
  MonoAssembly* mscorlibAssembly = mono_domain_assembly_open(monoDomain,
                                                             "mono/lib/mono/4.0/mscorlib.dll");
 
  MonoImage* systemImage = mono_assembly_get_image(mscorlibAssembly);
 
  // find the MethodInfo class
  MonoClass* methodInfoClass = mono_class_from_name(systemImage,
                                                    "System.Reflection",
                                                    "MonoMethod");
 
  // find the MethodInfo.MakeGenericMethod(Type[]) method
  MonoMethod* makeGenericMethod = mono_class_get_method_from_name(methodInfoClass,
                                                                  "MakeGenericMethod",
                                                                  1);
  printMethodSignature(makeGenericMethod);
 
  // find GenericMethod method from our TestClass, the method that we want to invoke
  MonoMethod* genericMethod = mono_class_get_method_from_name(testClass,
                                                              "GenericMethod",
                                                              1);
  printMethodSignature(genericMethod);
 
  MonoReflectionMethod* monoReflectionMethod = mono_method_get_object(monoDomain,
                                                                      genericMethod,
                                                                      testClass);
 
  MonoType* monoType = mono_reflection_type_from_name("System.String", monoImage);
  MonoReflectionType* monoReflectionType = mono_type_get_object(monoDomain,
                                                                monoType);
 
  // create an array of Types, that will be the argument to MethodInfo.MakeGenericMethod(Type[])
  MonoObject* exception = NULL;
  MonoArray* array = mono_array_new(monoDomain, mono_class_from_mono_type(monoType), 1);
  mono_array_set(array, MonoReflectionType*, 0, monoReflectionType);
  void* makeGenArgs[1];
  makeGenArgs[0] = array;
 
  MonoObject* methodInfo = mono_runtime_invoke(makeGenericMethod, monoReflectionMethod, makeGenArgs, &exception);
  checkException(exception);
 
  MonoClass* monoGenericMethodClass = mono_object_get_class(methodInfo);
 
  // MethodHandle property of MethodInfo object
  MonoProperty* methodHandleProperty = mono_class_get_property_from_name(monoGenericMethodClass, "MethodHandle");
  MonoMethod* getMethodHandleMethod = mono_property_get_get_method(methodHandleProperty);
 
  MonoObject* methodHandle = mono_runtime_invoke(getMethodHandleMethod, methodInfo, NULL, &exception);
  checkException(exception);
 
  MonoMethod* specializedMethod = *(MonoMethod**) mono_object_unbox(methodHandle);
  printMethodSignature(specializedMethod);
 
  void* args[1];
  args[0] = mono_string_new(monoDomain, "Finally!");
  MonoObject* testClassInstance = mono_object_new(monoDomain, testClass);
  mono_runtime_invoke(specializedMethod, testClassInstance, args, &exception);
  checkException(exception);
 
  // shutdown mono
  mono_jit_cleanup(monoDomain);
 
  return 0;
}