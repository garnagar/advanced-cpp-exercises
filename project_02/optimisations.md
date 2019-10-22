# Optimisations \newline Advanced Programming Lab Excercise 02

## 1 Count Sort

### 1.1 Incrementation
Incrementation or decrematation in the style `var++` was replaced by `++var`. This way the value is returned before incrementation and thus less memory is used.

This change didn't have any significat effect on execution time. Probably because returned variables are not used anywhere in the code and so compler didn't include them in the first place. The change was left in a final code as it is a better coding practise.

### 1.2 Loop Unrolling
Middle loop in the function was unrolled. We cosider two cases: If the `range` is even, we can unroll the loop and do "two iterations in one". If it's odd we make first step and than unroll rest of the loop.

This change saves in the example code ca. 0.1 ms of execution time.

Unrolling first and third loop didn't have any effect on the execution time. It's probably because this has already been done by the compiler as the loops are simple. 
