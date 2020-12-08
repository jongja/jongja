// Interface in Kotlin (with class)

open class Animal{
    fun animal(){
        println("I'm animal!")
    }
}

interface Runnable{
    fun run()
    fun fastrun(){
        println("Quick run!!")
    }
}

class Human: Runnable{
    override fun run() {
        println("Run! Human!")
    }
}

interface Eatable{
    fun eat()
}

class Dog : Animal(), Runnable, Eatable{ // Collaboration of interface and class
    override fun eat(){
        println("Eat Dog!")
    }

    override fun run(){
        println("Run! Dog!")
    }
}

val puppy = Dog()
puppy.eat() // Eat Dog!
puppy.animal() // I'm animal!
puppy.run() // Run! Dog!