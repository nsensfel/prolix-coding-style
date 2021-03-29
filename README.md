# Prolix Coding Style
A formalization of my preferred coding style.

This way of coding should be compatible with pretty much any language, with
Python being a notable exception.

## Rationale
As the name implies, the Prolix coding style is verbose and does not rely on
implicit language rules.

## Indentation style
The indentation style in Prolix is based on Allman's, but applies it to *every*
type of indentation and not just braces.

In effect: if a group of elements can stay in a single line, make it so.
Otherwise, the opening and closing markers of that group are on the same
indentation level.

Even if allowed by the language, the opening and closing markers should not be
omitted.

In order for the body of a structure to be on a single line (including its
opening and closing brace), the whole structure has to fit in that line.

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
