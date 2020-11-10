# Time Out

Time out은 주어진 시간을 줌으로써 launch된  coroutine을 가지고 cancel을 진행하는 것이 아닌 coroutine에게 timeout을 줌으로써 자동으로 종료되게 되는 방법이다.  

## Code 1

```
import kotlinx.coroutines.*

fun main() = runBlocking{
	withTimeout(timeMillis: 1300L) {
		repeat(times: 1000){ i ->
			println(msg: "I'm sleeping $i ...")
			delay(timeMillis: 500L)
		}
	}
}
```
### Result
```
I'm sleeping 0 ... 
I'm sleeping 1 ... 
I'm sleeping 2 ... 
Exception in thread "main" kotlinx.coroutines.TimeoutCancellationException: Timed out wating for 1300 ms
...
```
위의 결과를 보면 TimeoutCancellationException이 발생하게 된다. 이는 main에서 발생했기때문에 발생한 exception이라고 볼 수 있다. 이를 해결하기 위하여 `withTimeout`대신 `withTimeoutOrNull`을 사용하여 결과값이 NULL을 배출하도록 한다.  

## Code 2

```
import kotlinx.coroutines.*

fun main() = runBlocking{
	val result = withTimeoutOrNull(timeMillis: 1300L) {
		repeat(times: 1000){ i ->
			println(msg: "I'm sleeping $i ...")
			delay(timeMillis: 500L)
		}
	}
	println(msg: "Result is $result")
}
```
### Result
```
I'm sleeping 0 ... 
I'm sleeping 1 ... 
I'm sleeping 2 ... 
Result is null
...
```
