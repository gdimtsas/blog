using System;

namespace Example
{
  public class Entity
  {
    private int Id;
    private String Name;

    public Entity(String Name)
    {
      this.Name = Name;
      System.Console.WriteLine("Entity " + Name + " constructed");
    }

    ~Entity()
    {
      System.Console.WriteLine("Entity " + Name + " destructed");
    }

    public void Process()
    {
      throw new NotImplementedException("Not implemented yet");
    }

    public String GetName()
    {
      return Name;
    }
  }
}
