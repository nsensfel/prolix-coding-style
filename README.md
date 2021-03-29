# Prolix Coding Style
A formalization of my preferred coding style.

This way of coding should be compatible with pretty much any language, with
Python being a notable exception.

## Rationale
As the name implies, the Prolix coding style is verbose. If code length is an
issue for you, I would not recommend it.

Prolix makes it very easy to see what element belongs in what group. It also
forbids reliance on implicit operator priority, making complex operations much
easier to read.

## Type conversions
Never use implicit conversions.

## Restriction
Always use the most restrictive mode possible for arguments, even if this means
indicating more modifiers.

Generally, indicate the keywords corresponding to restrictions that match what
is done with the variable, even if the code would work without them. Once this
is done, you can assume any restriction being absent from something as an
indication that this thing is used in a way that does not allow such a
restriction. For example, in Java, every variable should be `final` unless it
is modified.  Thus, upon seeing that a variable is not `final`, one should
expect it is likely to be modified by something.

## Argument order in functions
Arguments used to return results should be last when possible. The order of
inputs should put the subject of modifications last. For example, adding a new
element at a certain index to a set should be in the `elem, index, set` order.

If a function has to return more than one value and tuples are not available in
the language, then use arguments instead, with the actual return value being
either a success indicator or no return value at all.

## Indentation Type
Prolix does not impose a particular type of indentation. Tabulation or space
are both acceptable, as long as what constitutes a level of indentation is
consistent thorough the project.

## Length limits
* Code line: Avoid going beyond the 79th column (i.e. 80 characters per line)
  whenever possible.
* Name: Do not feel constrained by any length limit when naming something.
* Function: isolate logical blocks into separate functions whenever possible.

## Naming conventions
As a general rule, use very descriptive name. Think *anti-assembly*: long,
self-explaining names are preferred to short, confusing names.

Generally, names are in lowercase and use underscores to separate words.
Constants use are in uppercase and underscores.
In OOP languages, classes are named without underscores and use a capital
letter for the first character of each word.

Starting anything with an underscore generally indicate a hack and it should be
expected that this thing may change its behavior or name without warning.

If the language supports anonymous variables, these should be as descriptive as
they can.

## Import/Export statements
Regroup import statement by library (the more general the library, the higher
it should be) leaving an empty line to separate each group. The elements of a
group should be sorted alphabetically.

## Blocks
Blocks are list of elements within braces, brackets, chevrons, parentheses, or
other punctuation pairs of this kind. These punctuation pairs have to be
present even if the language allows their omission, unless the block
semantically defined by its indentation level. Prolix uses the same rules for
all punctuation pairs, with some exceptions here and there.

In order to specify some exceptions:
* **Qualifying blocks:** blocks that qualify an element (e.g. index in an array,
  class parameters, function call parameter lists).
* **Instruction blocks:** blocks that contain sequences of instructions whose
  returned valued is not being used.

A block has its opening punctuation and closing punctuation on the same column,
unless this block is **not** an *instruction block* and both it and whatever
keywords are part of the construct fit on a single *code line*.
If the block is on multiple lines, the closing punctuation does not
share its line with anything else. If the block is on multiple lines and the
language uses infix notations, the opening punctuation does not share its line
with anything else.  If the block is on multiple lines and the language uses
prefix notations, the opening punctuation is immediately followed by the prefix
operator and nothing else is present on that line.  If the block is on multiple
lines, the indentation level is incremented past the opening punctuation and
decremented for the closing punctuation.

With the exception of *instruction blocks*, lists of elements with a single
value may omit the punctuation pairs if the language permits it.

With the exception of *qualifying blocks*, if a block shares its line with
other things, a space separates it from whatever other elements are on the
line. This space is not present for unary operators.

Blocks cannot contain different non-unary operations. Thus, to chain different
non-unary operations, sub-blocks have to be created. This makes it impossible to
rely on operator priority for non-unary operations.

Nothing can go under the current indentation level except for the block's
closing punctuation. Thus, things like labels and comments are indented.


Note:
* Commas are attached to the block that precedes them.
* The pre and post operations of a `for` are not considered to be *instruction
  blocks*.
* An acceptable exception to these rules is considering `else if` as a single
  keyword, thus not requiring the `if` to be a separate block from the `else`.
* Another exception is the `switch` structure: first level labels within it
  each define an *instruction block* through indentation.
* The rules in this section do in fact specify that non-unary infix operators
  are not attached to their arguments and there is thus a either a space or a
  newline.

## Inline operator sequence
Given `OP` and operator that returns a value, and `G{0..2}` groups that return
values:

* If the sequence fits in the *code line*:
```
G0 OP G1 OP G2
```
* If the sequence does not fit in the *code line*, but `OP G1` and `OP G2` do:
```
G0
OP G1
OP G2
```
* If the sequence does not fit in the *code line* and neither does `OP G2`, but
`OP G1` does fit:
```
G0
OP G1
OP
G2
```

* If none fit in the *code line*:
```
G0
OP
G1
OP
G2
```

Note that if the entire sequence cannot fit in the *code line*, there cannot be
more than one instance of `OP` for that sequence on the same line. This would
thus be forbidden:
```
G0 OP G1
OP G2
```

## Logical separations in instruction blocks
If the language allows separate declaration and definition (e.g. C, Java, but
not C++), declare (without defining) all variables at the start of the function.

No more than one instruction per line.

Do not declare variables of a different type on the same line (this also
forbids declaring pointers and non-pointers on the same line).

Separate declarations, assignments, function call, and loop/conditional/jump
structures with an empty line.
