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

# Checking Overlap

For some reason I feel like this comes up a lot. I think I can remember a few leetcode challenges that required bounds checking for overlap. Potentially to avoid redundant calculations.

## Part 1: Total Containment

For one (A) range to totally contain another range (B):

* B_left >= A_left
* B_right <= A_right

visually:

```
A_left --------------- A_right
      B_left-----B_right
```

The relationship needs to be commutative as well because of the
wording: if one range consumes another. Meaning `consumes(A,B)` should
return true if either A or B consumes the other. We'll use this later.

## Part 2: Any Overlap

Now we just want to check for any overlap, let's list the cases where A overlaps B.

```
//ranges are equivalent
A_left -------- A_right
B_left -------- B_right

//B_left is contained in A (B_left >= A_left && B_left <= A_right)
A_left -------- A_right
           B_left -------- B_right

//B_right is contained in A (B_right >= A_left && B_right <= A_right)
        A_left -------- A_right
B_left -------- B_right
```

The following [StackOverflow answer](https://stackoverflow.com/a/3269471/456809) explains things very succintly.

But in our case the check needs to be commutative as well.

## Commutative Property

Truth tables suck to write by hand, and we haven't even written the
other half of the truth table which is if A overlaps with B.

# C Learnings

Multidimensional Arrays: https://www.tutorialspoint.com/cprogramming/c_multi_dimensional_arrays.htm


