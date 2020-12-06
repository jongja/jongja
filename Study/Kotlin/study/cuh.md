# Coroutines under the hood (CUH)

어떻게 코틀린은 JVM에서 동작하는 걸까? 이 부분에 대한 이야기를 진행한다. 결국 Kotlin도 regular code이다. Compiler는 Kotlin으로 작성된 코드를 **Continuation Passing Style (CPS)**로 전환하게 된다.
예를 들어 다음과 같은 코드가 있다고 하자.

```
fun postItem(item: Item) {
	val token = requestToken()
	val post = creatPost(token, item)
	processPost(post)
}
```

이렇게 순차적으로 되어있는 함수들은 Kotlin에서는 비동기처리까지 완료하게 되어 진행하게 되는데 어떤일이 Kotlin에서 일어나는 것일지 확인해 보자.  
Java/JVM에서는 위의 함수가 다음과 같이 Continuation Passing Style (CPS)로 변하게 되고 마지막에 `Continuation<post>`라는 parameter가 뒤에 붙게 된다.  
```
Object createPost(Token token, Item item, Continuation<post> cont { _ }
```

위의 `postItem`을 Compiler가 compile하게 되면 내부적으로 다음과 같이 label을 붙이게 된다. 이렇게 하게 된다면 아래의 suspend function에서 label을 통하여 suspend point를 잡을 수 있게된다.

```
suspend fun postItem(item: Item) {
	switch (label) {
		case 0:
			val token = requestToken(sm)
		case 1:
			val post = createPost(token, item, sm)
		case 2:
			processPost(post, sm)
	}
}
```

따라서 이 함수를 실행하게 된다면 label을 통하여 재개할 수 있는 지점이 생기는 것이다. 위에서 switch문은 이해를 돕기 위하여 사용한 것이지 실제로 switch문을 사용하는 것은 아니다. 이것이 비동기 처리를 Kotlin이 처리할 수 있는 비밀이라고 할 수 있다. 뒤쪽에 보면 sm이라는 새로운 parameter가 붙는 것을 볼 수 있는데 이게 아까 `Continuation<post>`를 의미한다. 따라서 중단되었을때 sm의 값이 suspend되고 resume될경우 해당 sm의 값이 바뀌며 작업을 수행하게 되는 것이다.  

