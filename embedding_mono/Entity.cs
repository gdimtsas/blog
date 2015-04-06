using System;

namespace Example
{
  public class Entity
  {
    private String name;

    public Entity(String name)
    {
      this.name = name;
      System.Console.WriteLine("I'm alive! My name is " + name);
    }

    ~Entity()
    {
      System.Console.WriteLine("I'm being finalized!");
    }

    public void Process()
    {
      throw new Exception("Oh no!");
    }

    public String getName()
    {
      return name;
    }
  }
}
