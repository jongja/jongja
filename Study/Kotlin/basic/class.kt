// Class in Kotlin

// 1. Property
class Person(var name : String){
    init {
        println("This is constructor")
    }
}

// Property can be replaced getter() and setter() function in Java.
val person = Person("Jongja")
person.name = "JongHyeon" // setter()

println(person.name) // getter()

// 2. access restrictor
class A{
    val a = 1               // public
    private val b = 2       // private - Only available inside the current file
    protected val c = 3     // protected  - Only available in inherited classes
    internal val d = 4      // internal - Only available in same module   
}

// 3. inheritance

open class Animal{
    
}

class Dog : Animal(){
    
}

// 4. Abstraction Class
abstract class ParentClass{
    abstract fun func()
    fun func2(){
        
    }
}

class ChildClass : ParentClass(){
    override fun func(){
        println("Hello?")
    }
}

val a = ParentClass() // Error...
val b = ChildClass() // Okay!