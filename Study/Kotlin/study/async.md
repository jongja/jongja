# Composing Asyncronous Function

Suspend function은 coroutine에서 호출 될 경우 잠시 중단되는 함수를 말한다. Coroutine에서는 비동기 호출을하게 된다면 실행을 순서대로 하고 싶다면 일반 코드처럼 작성을 하면된다. Coroutin에서는 기본적으로 순차적으로 실행하게 된다. 아래 예제를 통해 확인하자.  

## Code 1

```
fun main() = runBlocking {
	val time = measureTimeMillis{
		val one = doSomethingUsefulOne()
		val two = doSomethingUsefulTwo()
		println("The answer is ${one + two}")
	}
	println("Completed in $time ms")
}

suspend fun doSomethingUsefulOne() : Int {
	println("doSomethingUsefulOne")
	delay(1000L)
	return 13
}

suspend fun doSomethingUsefulTwo() : Int {
	println("doSomethingUsefulTwo")
	delay(1000L)
	return 29
}
```

### Result
```
doSomethingUsefulOne
doSomethingUsefulTwo
The answer is 42
Completed in 2015 ms
```

위의 코드를 보면 coroutine을 통해 두 개의 함수 `doSomethingUsefulOne`와 `doSomethingUsefulTwo`가 동작을 하게되는데 이는 예시로써 네트워크 관련 코드라고 생각을 하게 된다면 해당 코드는 비동기 함수이다. 하지만 coroutine에서는 이러한 비동기 함수들을 순서대로 동작하게 하고싶다면 그냥 위의 코드처럼 일반 코드처럼 작성을 하게 된다.  
따라서 결과는 순차적으로 출력이 되는 것을 확인할 수 있다. 이를 통해 확인할 수 있는 coroutine의 특징은 다음과 같다.  

	- 비동기에 대한 처리를 간단하게 할 수 있다.  
	- Call back을 순차적으로 할 수 있다.  

위의 예제는 2초의 delay를 가지고 있는데, 만약 main thread에서 실행을 하게 된다면 coroutine이 아닌 환경에서는 모든 동작이 중단되고 2초의 delay후에 다시 동작이 재개 될 것이다. 하지만 위의 예제를 통해 알 수 있는 것은 coroutine을 실행하고 launch하게 된다면 주변의 동작이 멈추지 않고 delay를 진행한다는 것으로 이해할 수 있다.   
  
## Code 2

```
fun main() = runBlocking {
	val time = measureTimeMillis{
		val one = async { doSomethingUsefulOne() }
		val two = async { doSomethingUsefulTwo() }
		println("The answer is ${one.await() + two.await()}")
	}
	println("Completed in $time ms")
}

suspend fun doSomethingUsefulOne() : Int {
	println("doSomethingUsefulOne")
	delay(1000L)
	return 13
}

suspend fun doSomethingUsefulTwo() : Int {
	println("doSomethingUsefulTwo")
	delay(1000L)
	return 29
}
```

### Result
```
doSomethingUsefulOne
doSomethingUsefulTwo
The answer is 42
Completed in 1018 ms
```
  
Code 1을통해 기본적으로 coroutine은 일반적으로 코드를 작성하게 된다면 비동기 코드일 지라도 순차적으로 실행한다는 것을 보여주었다.  
위의 예제를 보게 된다면 `async`를 사용한 모습을 확인 할 수 있는데 이는 비동기동작을 명시하는 것이다. async를 사용하게 된다면 async를 사용한다면 함수를 실행시키고 바로 다음 line으로 이동하여 진행한 뒤, `await`을 사용하여 해당 사용한 함수를 기다린다는 것을 의미한다. 이렇게 되게 된다면 기존 code 1에서 보여주었던 것과 달리 1초만에 출력이 끝나게 된다.  

