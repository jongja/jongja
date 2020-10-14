var toDoDic = [17: "play", 25: "Watch Movies", 28: "Travel"]
//var toDoDic: Dictionary<Int, String> = [17: "play", 25: "Watch Movies", 28: "Travel"] //original ver.

toDoDic[1] = "jongja"
print(toDoDic)

toDoDic.removeValue(forKey: 1)
print(toDoDic)

for (key, value) in toDoDic {
    print("key : \(key), value : \(value)")
}

for key in toDoDic.keys {
    print(key)
}

for value in toDoDic.values {
    print(value)
}

toDoDic.removeAll()
print(toDoDic)
