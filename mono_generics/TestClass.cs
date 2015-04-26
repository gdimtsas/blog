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
      return method.MakeGenericMethod(type).MethodHandle.Value;
    }
  }
}
