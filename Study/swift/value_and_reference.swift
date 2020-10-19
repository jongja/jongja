func addTwoNumber(num1: Int, num2: inout Int) -> Int{
    num2 = 7
    return num1 + num2
}

var test1 = 10
var test2 = 20

_ = addTwoNumber(num1: test1, num2: &test2)
