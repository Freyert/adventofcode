I think this one is a fairly simple case of tokenizing each line and then bounds checking each case.

Cases:

1. Does L contain R?
2. Does R contain L?

# Parsing the input

Generally, the problems require a lot of input parsing. Most languages have functions that allow you to easily split strings, but C is a little different.

I see a lot of recommendations to use something like [`strtok`](https://pubs.opengroup.org/onlinepubs/007904975/functions/strtok.html), but after reading the documentation it sounds like a function I would prefer never to use.

> If such a byte is found, it is overwritten by a null byte, which terminates the current token. The strtok() function saves a pointer to the following byte, from which the next search for a token shall start.

Basically, `strtok` modifies the current string, but the main issue for me is that `strtok` maintains secret internal state. So if I want to use `strtok` on multiple strings in parallel it would perform in unexpected ways.

I believe more modern libraries would make the state explicit through the use of a class or struct such as a "tokenizer" to store the state related to a particular string.

## Taking inspiration from `strtok`

If I want to split the string in place,  I can just replace `-` and `,` with `\0`.

Then I would track a `strlen` for the current string, jump back that far in memory, process the string into an int, jump forward again, and resume parsing the string.

# C Learnings

Multidimensional Arrays: https://www.tutorialspoint.com/cprogramming/c_multi_dimensional_arrays.htm


