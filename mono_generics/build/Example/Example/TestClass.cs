using System;
using System.Reflection;

namespace MonoGenerics
{
  public class TestClass
  {
    public void GenericMethod<T>(T t)
    {
      Console.WriteLine(t);
    }

    public static IntPtr MakeGenericMethod(MethodInfo method, Type type)
    {
      MethodInfo specializedMethod = method.MakeGenericMethod(type);
      IntPtr ret = specializedMethod.MethodHandle.Value;
      return ret;
    }

    public static void Main()
    {

    }
  }
}
