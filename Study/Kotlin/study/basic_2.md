# Basic of Kotlin 2

## Code 1
```
import kotlinx.coroutines.*

fun main() = runBlocking {
	GlobalScope.launch{
		delay(timeMillis: 1000L)
		println("World!")
	}
	
	println("Hello,")
	delay(timeMillisL 2000L)
}
```

### Result 
```
Hello,
World!
```

이전 Basic에서 runBlocking에 대해 설명했는데 해당 부분의 위의 Code 1과 표현할 수 있다. 하지만 이 표현법은 좋은 표현법이 아니다. 사실 delay안에 있는 숫자가 변경된다면 원하는 순서대로 출력이 안될 수 있기 때문이다.  
따라서 이를 해결하기 위하여 `job`을 사용하게 된다.

## Code 2
```
import kotlinx.coroutines.*

fun main() = runBlocking {
	var job = GlobalScope.launch{
		delay(timeMillis: 3000L)  // if we don't use job class, we can't get the result we want.
		println("World!")
	}
	
	println("Hello,")
	job.join()
}
```

### Result 
```
Hello,
World!
```
  
이렇게 원하는 결과를 얻을 수 있게 된다. 여기서 `var job`이 받는 `launch`가 반환하는 값은 `coroutine` 객체 이다.  
하지만 만약 `job.join()`을 사용하지 않게 된다면 coroutine은 실행되지 않은채 코드가 끝나버리게 된다. 이게 중요한 이유는 coroutine는 하나의 coroutine만 이용되는 것이 아닌 여러개가 이용되게 될 때 관리하기가 힘들어지게 된다.  
따라서 Kotlin에서는 이러한 것을 방지하기 위하여 **structured concurrency**를 이용하도록 한다.  

#### Structured Concurrency
구조적으로 관계를 만드는 것. `this`를 사용하거나 부모 coroutine의 child coroutine으로 넣어 child coroutine가 모두 끝날때까지 기다려주게 된다.  

## Code 3
```
import kotlinx.coroutines.*

fun main() = runBlocking {
	this.launch{  // Structured Concurrency
		delay(timeMillis: 3000L)  
		println("World!")
	}
	
	println("Hello,")
}
```

### Result 
```
Hello,
World!
```

위의 예제를 보면 `this`를 사용하여 `runBlocking`이라는 부모 coroutine의 child coroutine으로 만드는 모습을 확인할 수 있다. 이 경우에는 `Hello,`가 먼저찍히고 child coroutine가 실행되지 않았기 때문에 부모 coroutine인 `runBlocking`이 기다려주게 된다.  
이 때, `this.launch`가 아닌 `launch`로 적어도 같은 기능으로 동작하게 된다. 
  
만약 coroutine안에 있는 부분을 함수로 따로 빼서 추출하고 싶을 경우 다음과 같이 코드를 작성한다.   

## Code 4
```
import kotlinx.coroutines.*

fun main() = runBlocking {
	launch{  //   == this.launch
		myWorld()
	}
	
	println("Hello,")
}

fun myWorld() {
	delay(timeMillis: 3000L)    // ERROR!
	println("World!")
}

```
하지만 이 경우 delay에서 오류가 발생하게 된다. `delay`는 **suspend function**으로 써 **suspend function이나 coroutine에서 호출되어야 한다.** 따라서 함수 `func myWorld`는 suspend function으로 바꾸어줘야 올바르게 작동하게 된다.  
위의 예제의 올바른 표현 법은 `suspend fun myWorld()`가 된다.  
  
# Features of Coroutine

## Coroutines ARE light-weight
coroutine은 정말 가벼운 특징을 가지고있다. 이를 보기 위하여 다음 예제를 보자.  
  
```
fun main() = runBlocking {
	repeat(100_100){
		launch{
			delay(1000L)
			print(".")
		}
	}
}
```
위의 예제는 1초 뒤 100,000개의 coroutine을 통해 점을 찍는 함수라고 볼 수 있는데 결과를 보면 절대 버벅이지 않고 빠르게 동작하는 모습을 볼 수 있다. 만약 `launch`를 `thread`로 바꾸게 된다면 보다 버벅이는 현상을 볼 수 있는데 이만큼 **coroutine이 thread보다 상대적으로 가볍다는 것**을 알 수 있다.  

## Global coroutines are like daemon thread

Coroutine은 process가 끝나게 되면 thread 처럼 같이 끝나게 된다. 아래 예제를 보자.  

```
import kotlinx.coroutines.*

fun main() = runBlocking {
	GlobalScope.launch{  // Structured Concurrency
		repeat(1000){ i ->
			println("I'm sleeping $i ...")
			delay(500L)
		}
	}
	
	delay(1300L)
}
```
위의 함수를 보면 메인 함수는 1.3초 후에 종료되게 된다. 하지만 coroutine은 1000번 반복을 해야한다. 하지만 이 결과는 모두 출력되는 것이 아닌 메인 coroutine이 끝나게 되면 이후의 coroutine은 실행되지않고 끝나게 된다.  
