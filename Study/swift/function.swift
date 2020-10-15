
func hello(name: String) -> String { //name(variable : type) -> return type
    let message = "Hello" + name
    return message
}

var jongja = "man"

var b = hello(name: jongja)
print(b) //print function is also function

var k: Float = 1

k + 0.03


//Code Snippet


func addTwoNumber(num1: Int, num2: inout Int) -> Int {
    return num1
}

//void function

func voidFunc(){ //no return types
    //nothing
}

func addNumbers(numbers: Int...)-> Int{ //multiple argument
    var sum = 0
    for nm in numbers{
        sum += nm
    }
    return sum
}
addNumbers(numbers: 1,2,3,4,5)

//print function

print("wow","jongja", separator: "...", terminator:"")
print("a")

func calculate(MultiplyFirstNumber num1: Int, bySecondNumber num2: Int) -> Int { //argument label
    return num1 * num2
}

calculate(MultiplyFirstNumber: 20, bySecondNumber: 10)

func call_by_value(num1: inout Int, num2: inout Int){
    let temp = num1
    num1 = num2
    num2 = temp
}

var va = 10
var vb = 20

call_by_value(num1: &va, num2: &vb)
print("va value: \(va)\nvb value: \(vb)")









