# Basic of Kotlin 1

## Code 1
```
import kotlinx.coroutines.*

fun main() {
	GlobalScope.launch {
		delay(1000L)   // 1 second delay 
		println("World!")
	}
	
	println("Hello,")
	Thread.sleep(2000L)  // 2 seconds delay
}
```

### Result 
```
Hello,
World!
```

위의 코드와 결과를 보면 조금 이상한 점을 볼 수 있는데, 코드상으로는 `World! Hello,` 가 나와야 할 것 같지만 결과를 보면 아니다.  

#### GlobalScope
object(객체)이다. Life time이 프로그램 전체를 가진 객체이다. 프로그램이 끝날때까지 돌아간다. 아래설명하는 builder를 생성하기 위해서는 scope가 필요하다.  

#### launch
Coroutine의 builder. coroutine 생성하고 coroutine을 반환한다.  

따라서 `GlobalScope.launch`는 프로그램 끝날때까지 돌아가는 coroutine을 의미한다고 볼 수 있다.  

본질적으로 coroutine은 light-weight thread이다. 따라서 `GlobalScope.launch`를 `Thread`로 바꾸면 같은 동작을 한다.  

----  

## Code 2
```
import kotlinx.coroutines.*

fun main() {
	GlobalScope.launch {
		delay(1000L)   // 1 second delay 
		println("World!")
	}
	
	println("Hello,")
	runBlocking {
		delay(2000L)
	}
}
```

### Result 
```
Hello,
World!
```

이번 코드의 결과 역시 같은 모습을 볼 수 있는데 Code 1과의 차이점이라면 `runBlocking`을 사용한 것이다. Code 1에서 `Thread.sleep`을 `delay`로 바꾸게 된다면 오류가 발생하게 되는데, 이는 `delay`는 **suspend** 함수이기에 coroutine scope안에서 실행되거나 다른 **suspend** 함수에서 사용되어야 하기 때문이다.  
따라서 이 부분을 `runBlocking`이라는 다른 coroutine builder를 사용하면 blocking coroutine을 return하게 되어 같은 결과를 내게 되는 것이다.  

## Code 3
```
import kotlinx.coroutines.*

fun main() {
	runBlocking {
	 	GlobalScope.launch {
			delay(1000L)   // 1 second delay 
			println("World!")
		}
	
		println("Hello,")
		delay(2000L)
	}
}
```

### Result 
```
Hello,
World!
```
이 역시 결과가 같은데, 위의 코드들과 다른점을 볼 수 있다면 이전부분을 runBlocking으로 감싸는 것이다. 이렇게 되게 되면 runBlocking의 안에 있는 함수가 모두 돌아갈때 까지 main thread는 return할 수 없게 된다.

