let dust = 155 //상수

if dust <= 30 {
    print("아 상쾌하다")
}
else if dust > 30 && dust <= 50 {
    print("뭐 이정도면 나쁘지 않군")
}
else if dust > 50 && dust <= 100 {
    print("아 안좋아")
}
else {
    print("최악..")
}

//switch function

let weather = "장마"

switch weather { //in swift, switch function not use 'break'
case "맑음":
    print("💕")
case "비", "장마": //can use multiple condition
    print("☔️")
default: //default condition must to write
    print("default")
}

