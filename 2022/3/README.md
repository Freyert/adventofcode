Generally, many of the advent of code problems seem possible to leverage bit masks to solve.

I'm playing catchup here and I'm not particularly great with bit masks, but I found this excellent solution from [@tsenart](https://github.com/tsenart).

Generally, I see the experienced folks with Advent of Code breaking it into two parts. The problems are often introduced this way as well.

# Part 1

We have:

1. A bunch of rucksacks.
2. Each ruck sack has two compartments.
3. Each compartment has the same number of items.
4. First half of each line is first compartment.
5. Second half of each line is second compartment.
6. Items are ascii a-z A-Z.

Identify the item type common to both compartments.

## Why Bit Masking?

I am attempting to do all exercises in C, which does not include an associative map or set type.

Plus, as pointed out in [fasterthanli.me day 3 blog](https://fasterthanli.me/series/advent-of-code-2022/part-3) there are major overheads with using sets and associative arrays.

In fact [bigocheatsheet.coom](https://www.bigocheatsheet.com/) shows that the worst case execution time for HashMaps is O(N). Many, including myself, conflate the _average_ runtime of HashMaps Θ(1) for its worst case.

All this to say: if you can replace a HashMap with a bitmask you will avoid a lot of extra overhead and perhaps actually have O(1) execution.


## What does bitmasking look like?

In this instance maybe a better term would be a "bit set", but at the 
core the "bit set" is implemented with "bit masking".

First, we need to identify what is _in_ the set and to explain how
this works I want to simplify the problem.

Let's imagine we have 4 characters in our "language" or list of possible
characters: a, b, c, d.

We could map each character to a bit in a 4-bit number:

```
0001 => a
0010 => b
0100 => c
1000 => d
```

If multiple bits are set, then that means each of those characters were present.

```
0101 => a & c
1100 => d & c
```

## Setting the bits in the set

The bit set sarts out empty: `0000`.

If we see an `a` we need to find some way to map `a` to the number `1` or `0001` in binary.

If `a` corresponds to `97` in the ascii table, we can subtract `96` from
the ascii values to achieve their position in the bit set.

```go
bitset := 0 // 0000
mask := 'a' - 96
bitset = bitset | mask // 0001 | 0000 => 0001
```

So using `|` (bitwise or) allows us too set individual bits by "oring" our bitset against a "mask".

## Checking the bits in the set

Conversely, if you want to see if a bit in the bit set is set, then you bitwise _and_ (`&`) against a mask.

```go
bitset := 1 //0001
mask := 1 << ('a' - 'a') //0001
bitset = bitset & mask // 0001 & 0001 => 0001
```

If the bit is not set you would see:

```go
bitset := 1 //0001
mask := 1 << ('b' - 'a') //0010
bitset = bitset & mask // 0001 & 0010 => 0000
```
That's generally how we can solve part 1. However, since I am solving in C there is always a part 0: parsing the input.

# Part 0

A few problems to solve:

1. Which function do we use to read the inputs?
2. We do not know the length of each line ahead of time so we need a clever way to switch between filling the set, and checking the set.

## Reading lines

Generally, if I were writing in Go I would reach for [bufio#Reader.ReadLine](https://pkg.go.dev/bufio#Reader.ReadLine), but when you write in C it really gets you thinking about memory.

What if someone decided to give me a billion characters on one line? Boom, majorly wasted memory. If I think about what I really need it is:

1. A 52 bit bit set to track which characters have been seen.
2. For part 2, I think a length 52 int array to track occurences.

This totally decouples memory from the input length. Super score! But... since the lines don't tell us how many elements to expect we can't know when to switch from compartment 1 processing to compartment 2 procesesing without counting the line length first.

### Handling unknown line lengths

We could put each line into a stack, get the length, pop to half to fill the bit set, then pop the rest to find the common element. However, we now have the whole line in memory, plus the overhead of a linked list based stack to accomodate an "uknown length" line.

Alternatively, I think using [fseek](https://pubs.opengroup.org/onlinepubs/007904975/functions/fseek.html) to seek to the start of the line after counting the length seems a better approach.

I believe [fseek](https://pubs.opengroup.org/onlinepubs/007904975/functions/fseek.html) would have very low memory overhead comparatively, but also have a low computational overhead as it seeks by an offset. Seeking by offset makes me think the access time would be similar to that of an array which also seeks by offset.

So what does our time complexity look like now?

```
O(N) count line length
+
O(N) check compartments
=
O(2N) or O(N)
```

Our memory complexity relates to the size of the input language and not the size of anyone unbound input. I'll say memory complexity is `O(L)`, but we know thee language is bounded which is a major plus.

## C Oddities

`fgets` will not read the last line if it doesn't have a `\n`.
https://stackoverflow.com/questions/2392549/fgets-is-omitting-the-last-line-in-c

`&^` in C: https://stackoverflow.com/questions/34459450/what-is-the-operator-in-golang/34459527#34459527

Bitwise operations on unsigned long long: https://stackoverflow.com/questions/26684351/bitwise-operations-on-unsigned-long-long-in-c
