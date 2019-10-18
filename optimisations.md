# Advanced Programming Lab Excercise 02

## 1 Count Sort

### 1.1 Incrementation
Incrementation or decrematation in the style `var++` was replaced by `++var`. This way the value is returned before incrementation and thus less memory is used.

This change didn't have any significat effect on execution time. Probably because returned variables are not used anywhere in the code and so compler didn't include them in the first place.

### 1.2 Element access
Accessing elements using `[]` instaed of `.at()` was implemented.

It seems to have made execution sligtly faster.
