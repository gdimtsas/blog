using System;

namespace Example
{
  public class Entity
  {
    public Entity()
    {
      System.Console.WriteLine("I'm alive!");
    }

    ~Entity()
    {
      System.Console.WriteLine("I'm being finalized!");
    }

    public void Process(String name)
    {
      System.Console.WriteLine("Hello from C#! My name is " + name);
      throw new Exception("Oh no!");
    }
  }
}
