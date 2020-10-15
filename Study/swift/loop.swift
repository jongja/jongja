//for condtion
//for i in 1...10 { // ...=> 범위 연산자
//    print(i)
//}
//
//for i in stride(from: 1, to: 10, by: 2){ //from 1 to 10 as plus2
//    print(i)
//}
//
//for i in stride(from: 10, to: 1, by: -2){ //from 10 to 1 as minus 2
//    print(i)
//}

for i in 1...9{
    for j in 1...9{
        print("\(i) X \(j) = \(i*j)"); //string interpolation
    }
}
//whlie loop
var i = 0

while i < 10 {
    i += 1
    print(i)
}
i=0
repeat {
    i += 1
    print(i)
} while i < 10
