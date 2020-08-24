# Attack Description

This execution file was compiled using [Mastik](https://cs.adelaide.edu.au/~yval/Mastik/), a cache side channel framework.  \
Mastik makes it easy to execute various types of cache side channel attacks with a simple setup and compilation

```
FF_attack : FLUSH+FLUSH attack
FR_attack : FLUSH+RELOAD attack
PP_attack : PRIME+PROBE attack
stress.sh : command > stress --vm 2 --cpu 2 --io 4
loop_code : infinity loop code
```

# Usage
just type this..
```
./FF_attack
```

### Reference Papers
[FLUSH+RELOAD](https://www.usenix.org/node/184416.) \
[FLUSH+FLUSH](https://gruss.cc/files/flushflush.pdf) \
[PRIME+PROBE](http://palms.ee.princeton.edu/system/files/SP_vfinal.pdf)
