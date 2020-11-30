println("Controls in Kotlin")

// 1. if
val a = 10
val b = 20

var max = a
if(a < b) max = b
else max = a

println(max)

// 2. when
// when == switch
val x = 1
when(x){
    1 -> println("x == 1")
    2, 3 -> println("x == 2 or x == 3")
    in 4..7 -> println("Between 4 and 7")
    !in 8.. 10 -> println("Not between 8 and 10")
    else -> println("Default (same as default in switch")
}
// Additionally, we can use the return value of the when function to Function.
fun isOne(num : Int) = when (num){
    1 -> "Yes"
    else -> "No"
}
println(isOne(x)) // Yes

// 3. for

val tempArray : Array<String> = arrayOf("He", "el", "lo", " W", "or", "ld!")

for (word in tempArray){
    println(word)
}

for (i in 1..3){
    println(i)
}

for (i in 1..10 step 2){
    println(i)
}

for (i in 10 downTo 1 step 2){
    println(i)
}

// 4. while
var loop: Int = 1
while(loop > 0){ // Only insert Boolean type..
    loop--
    println("wow!")
}