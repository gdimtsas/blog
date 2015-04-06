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

  MonoDomain* monoDomain = mono_jit_init_version("cshard_bindings",
                                                 "v4.0.30319");

  MonoAssembly* assembly = mono_domain_assembly_open(monoDomain,
                                                     "Engine.dll");
  MonoImage* monoImage = mono_assembly_get_image(assembly);

  // find the Entity class in the image
  MonoClass* entityClass = mono_class_from_name(monoImage,
                                                "Engine",
                                                "Entity");


  // shutdown mono
  mono_jit_cleanup(monoDomain);

  return 0;
}
