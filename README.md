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

## Indentation Type
Prolix does not impose a particular type of indentation. Tabulation or space
are both acceptable, as long as what constitutes a level of indentation is
consistent thorough the project.

## Length limits
* Code line: Avoid going beyond the 79th column (i.e. 80 characters per line)
  whenever possible.
* Name: Do not feel constrained by any length limit when naming something.
* Function: isolate logical blocks into separate functions whenever possible.

## Blocks
Blocks are list of elements within braces, brackets, chevrons, parentheses, or
other punctuation pairs of this kind. These punctuation pairs have to be present
even if the language allows their omission. Prolix uses the same rules for all
punctuation pairs, with some exceptions here and there.

In order to specify some exceptions:
* **Qualifying blocks:** blocks that qualify an element (e.g. index in an array,
  class parameter).
* **Instruction blocks:** blocks that contain sequences of instructions whose
  returned valued is not being used.

A block has its opening punctuation and closing punctuation on the same column,
unless this block is not an *instruction block* and it fits on a single *code
line*.
If the block is on multiple lines, the closing punctuation does not share its
line with anything else.
If the block is on multiple and the language uses infix notations, the opening
punctuation does not share its line with anything else.
If the block is on multiple and the language uses prefix notations, the opening
punctuation is immediately followed by the prefix operator and nothing else
is present on that line.

```c
if (short_exit_condition())
{
   return 0;
}

if (single_line_condition())
{
   just_one_function_call();
}

if
(
   first_element_of_this_condition_with_many_elements()
   && second_element_of_condition_with_many_elements()
)
{
   return 0;
}

if
(
   (
      first_element_of_this_condition_with_many_elements()
      && second_element_of_condition_with_many_elements()
   )
   ||
   (
      third_element_of_this_condition_with_many_elements()
      && fourth_element_of_condition_with_many_elements()
   )
)
{
   return 0;
}
```
