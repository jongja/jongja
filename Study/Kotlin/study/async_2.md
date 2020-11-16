# Lazily started async

이전 async를 통해 동시에 바로 실행하는 것을 다루었는데 이번에는 LAZY를 사용하여 바로 실행하지 않도록 설정할 수 있다. 예제를 통해 확인하면 다음과 같다.  

## Code 1

```
fun main() = runBlocking {
	val time = measureTimeMillis{
		val one = async (start = CoroutineStart.LAZY) {doSomethingUsefulOne() }
		val two = async (start = CoroutineStart.LAZY) {doSomethingUsefulTwo() }
		one.start()
		two.start()
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

첫 번째 실행은 `start()`를 넣어서 실행했을 경우 위와 같이 1초의 결과가 나오는 것을 확인할 수 있다. 하지만 만약 해당 `one.start()`와 `two.start()`를 하지않고 실행하게 되면 **두 개의 coroutine은 동시에 실행되지 않아** 2초의 결과를 가지게 된다.  
이에 대한 이유는 `LAZY`를 사용하게 된다면 `await()`를 만났을 경우 실행이 되게 된다. 따라서 `println`내부의 `one.await()`를 만나 첫 번째 coroutine이 실행되게 되고 `two.await()`를 만나게 되어 두 번째 coroutine를 실행하게 되기 때문이다.  

하지만 해당 async를 사용하는 부분에 있어서는 주의해야할 점이 존재한다.  

## Code 2

```
fun main() {
	try {
		val time = measureTimeMillis{
			val one = somethingUsefulOneAsync()
			val two = somethingUsefulTwoAsync()
		
			println("my exception")
			throw Exception("my exceptions")

			runBlocking {
				println("The answer is ${one.await() + two.await()}")
			}
		}
		println("Completed in $time ms")
	} catch (e : Exception) {
	}

	runBlocking {
		delay(100000)
	}
}

fun somethingUsefulOneAsync() = GlobalScope.async {
	println("start, somethingUsefulOneAsync")
	val res = doSomethingUsefulOne()
	println("end, somethingUsefulOneAsync")
	res^async
}

fun somethingUsefulTwoAsync() = GlobalScope.async {
	println("start, somethingUsefulTwoAsync")
	val res = doSomethingUsefulTwo()
	println("end, somethingUsefulTwoAsync")
	res^async
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
my exceptions
start, somethingUsefulOneAsync
start, somethingUsefulTwoAsync
end, somethingUsefulOneAsync
end, somethingUsefulTwoAsync
(Not terminated..)
```
  
위의 코드의 예상되는 결과는 exception이 발생하게 되어 두 개의 coroutine이 취소가 되어 출력이 되지 않아야 하지만 두개의 coroutine이 모두 실행되어 `delay(100000)`이 실행되어 종료가 되지 않는 모습을 확인할 수 있다.  
이에 대한 이유는 해당 coroutine은 GlobalScope에서 실행되고 있는 부분이기 때문에 어디서든 사용할 수 있는 일반 함수이다. 따라서, Kotlin에서는 해당 부분에 대해 주의 하라고 나와있다.  
  
## Code 3

```
fun main() = runBlocking {

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

```
