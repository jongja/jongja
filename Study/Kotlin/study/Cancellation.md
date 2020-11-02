# Cancellation

Cancellation은 coroutine을 취소해주는 것을 이야기한다. 이는 굉장히 중요한 부분인데 하나의 coroutine은 memory와 resource를 차지하고 있기 때문이다. 

## Code 1

```
fun main() = runBlocking {
	val job = launch {
		repeat(times: 1000) { i ->
			println("job : I'm sleeping $i ..."
			delay(timeMillis: 500L)
		}
	}
	delay(timeMillis: 1300L)
	println(msg: "main: I'm tired of wating!")
	job.cancel()  // if using this function, cancell a coroutine
	job.join()
	println(msg: "main: Now I can quit.")
}
```

### Result
```
job : I'm sleeping 0 ...
job : I'm sleeping 1 ...
job : I'm sleeping 2 ...
main: I'm tired of wating!
job : I'm sleeping 3 ...
job : I'm sleeping 4 ...
main: Now I can quit.
```

위의 코드를 보면 원래는 0.5초 간격으로 1000번 불려야하는 coroutine이 3번 호출 되고 `job.cancel()`에 의하여 취소가 된 모습을 볼 수 있다. 이렇게 `launch`로인해 생성된 coroutine `job`은 `cancel()`을 통해 취소를 할 수 가 있다.  
하지만 모든 상황에서 coroutine을 취소할 수 있는 것은 아니다. coroutine이 취소 되기 위해서는 크게 두 가지 방법이 존재한다.  
  
1. Coroutine안에 cancellation에 **협조적인** code가 있어야 가능하다.  
2. 명시적으로 상태를 체크하는 `isActive`를 사용한다.  
  
먼저 협조적인 코드를 확인하기 위해 보면 다음과 같다.  
  
## Code 3

```
fun main() = runBlocking {
	val startTime = System.currentTimeMillis()
	val job = launch(Dispatchers.Default) {
		var nextPrintTime = startTime
		var i = 0
		while ( i < 5) {
			if(System.currentTimeMillis() >= nextPrintTime) {
				println(msg: "job: I'm sleeping $(i++) ...")
				nextPrintTime += 500L
			}
		}
	}
	delay(timeMillis: 1300L) 
	println(msg: "main: I'm tired of wating!")
	job.cancelAndJoin()
	println(msg: "main: Now I can quit.")
}
```
  
### Result
```
job : I'm sleeping 0 ...
job : I'm sleeping 1 ...
job : I'm sleeping 2 ...
main: I'm tired of wating!
job : I'm sleeping 3 ...
job : I'm sleeping 4 ...
main: Now I can quit.
```
위의 결과를 확인하면 cancellation이 제대로 되지 않은 것을 확인할 수 있다. 이는 cancellation에 협조적이지 않은 code라는 것을 보여주는 것이다. `Code 1`과 비교를 했을 경우 `delay`를 하지 않고 진행하게 되는데, `delay`는 suspend function으로 cancellation에 협조적인 함수이다. 따라서 이 코드에서 정상적으로 진행하기 위해서는 `delay()`나 `yield()`를 사용한다. 결과는 다음과 같다.  

## Code 2

```
fun main() = runBlocking {
	val startTime = System.currentTimeMillis()
	val job = launch(Dispatchers.Default) {
		try {
			var nextPrintTime = startTime
			var i = 0
			while ( i < 5) {
				if(System.currentTimeMillis() >= nextPrintTime) {
					yield()
					println(msg: "job: I'm sleeping $(i++) ...")
					nextPrintTime += 500L
				}
			}
		} catch (e: Exception) {
			kotlin.io.println("Exception [$e]")
		}
	}
	delay(timeMillis: 1300L) 
	println(msg: "main: I'm tired of wating!")
	job.cancelAndJoin()
	println(msg: "main: Now I can quit.")
}
```
  
### Result
```
job : I'm sleeping 0 ...
job : I'm sleeping 1 ...
job : I'm sleeping 2 ...
main: I'm tired of wating!
Exception [kotlinx.coroutines.JobCancellationException: StandaloneCoroutine was cancelled; job-StandaloneCoroutine {Cancelling}@16fad3cf]
main: Now I can quit.
```

Code 3은 위에서 언급한 `yield()`를 실제로 사용했을때의 code이다. 코드를 보면 try catch 구문으로 작성을 한 모습을 볼 수 있는데, 이는 `yield()`의 동작을 확인하기 위해서 넣은 것이다. 올바르게 3번째 메시지에서 yield()에 협조로 인해 exception이 발생하여 Cancell에 대한 메시지를 출력한 모습을 확인할 수 있다.  
  
다음은 두 번째 방법인 `isActive`를 사용하여 cancellation을 진행하는 방법을 본다.

## Code 4

```
fun main() = runBlocking {
	val startTime = System.currentTimeMillis()
	val job = launch(Dispatchers.Default) {
		var nextPrintTime = startTime
		var i = 0
		kotlin.io.println("isActive $isActive ...")
		while (isActive) {
			if(System.currentTimeMillis() >= nextPrintTime) {
				println(msg: "job: I'm sleeping $(i++) ...")
				nextPrintTime += 500L
			}
		}
		kotlin.io.println("isActive $isActive ...")
	}
	delay(timeMillis: 1300L) 
	println(msg: "main: I'm tired of wating!")
	job.cancelAndJoin()
	println(msg: "main: Now I can quit.")
}
```
### Result
```
isActive true ...
job : I'm sleeping 0 ...
job : I'm sleeping 1 ...
job : I'm sleeping 2 ...
main: I'm tired of wating!
isActive false ...
main: Now I can quit.
```

위의 결과를 통해 확인할 수 있듯 `job.cancelAndJoin()`을 통해 cancel의 신호를 받은 coroutine의 `isActive`가 `false`로 변해 무한 반복문을 탈출하는 모습을 확인할 수 있다.  

