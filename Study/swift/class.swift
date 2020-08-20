class Circle{
    var radius: Double //property
    let pi = 3.1415926535
    
    init(){
        radius = 10.0

    }
    init(radius: Double){
        self.radius = radius
    }
    
    func area() -> Double { // method
        return radius * radius * pi
    }
}
let circle = Circle.init(radius: 20)

var weight = Int.init(65) // == Int(65)
var evenNumber = [Int](arrayLiteral: 2,4,6,8)

// inheritance

class NoteBook {
    var name = ""
    func turnOn(){
        print("Booting...")
    }
}

class MacBook : NoteBook { //subclassing: MacBook, Superclass: Notebook
    var hasTouchBar = true
    var macOSVersion = "10.13"
    
    override func turnOn() {
        super.turnOn()
        print("\(name)'s current macOSVersion is \(macOSVersion)")
    }
    func turnOnTouchBar(){
        
    }
}

let macBook = MacBook()
macBook.name = "JongjaMac"
macBook.turnOn()

//Destructor

class Circlee{
    var radius = 0
    init(){
        print("Initializer called")
    }
    deinit {
        print("Deinitializer called")
    }
}
if true{
    var circle1 = Circlee()
}








