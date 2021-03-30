# Prolix Coding Style
A formalization of my preferred coding style.

This way of coding should be compatible with pretty much any language, with
Python being a notable exception.

## 0. Rationale
As the name implies, the Prolix coding style is verbose. If code length is an
issue for you, I would not recommend it.

Prolix makes it very easy to see what element belongs in what group. It also
forbids reliance on implicit operator priority, making complex operations much
easier to read.

## 1. Definitions
### 1.0. Groups
**Definition:**
A *group* is a value or a list of *groups* potentially separated by *separators*
or by *operators*.

**Example:**
```c
if (fun_a(param_a, param_b) && ~fun_b(param_c) && fun_c())
{
   do_something();
}
```
The *groups* in the code above are:
* `(fun_a(param_a, param_b) && ~fun_b(param_c) && fun_c())`
* `fun_a(param_a, param_b)`
* `~fun_b(param_c)`
* `fun_b(param_c)`
* `fun_c()`
* `fun_a`
* `fun_b`
* `fun_c`
* `param_a`
* `param_b`
* `param_c`
* `(param_a, param_b)`
* `(param_c)`
* `()`
* `{ do_something(); }`
* `do_something()`
* `do_something`

#### 1.1. Qualifying Groups
A *qualifying group* is a *group* that suffixes a *group* in order to modify its
semantics.

**Example:**
```c
if (fun_a(param_a[0][a + b], param_b) && ~fun_b(param_c) && fun_c())
{
   do_something();
}
```
The *qualifying groups* in the code above are:
* `(param_a[0][a + b], param_b)`
* `(param_c)`
* `()`
* `[0]`
* `[a + b]`

Note: function call arguments are *qualifying groups*, function definition and
declaration arguments are **not**.

#### 1.2. Instruction Groups
An *instruction group* is a *group* that returns no value.

**Example:**
```c
if (fun_a(param_a[0][a + b], param_b) && ~fun_b(param_c) && fun_c())
{
   do_something();
}
```
The only *instruction group* in the code above is:
* `{ do_something(); }`

Notes:
* The pre and post components of a `for` are not considered to be *instruction
  groups*.
* Cases of a `switch` each form their own *instruction block*.

#### 1.3. Separator
A *separator* is a symbol that is put in between *groups* yet does not merge
the groups it separates.

**Example:**
```c
if (fun_a(param_a[0][a + b], param_b) && ~fun_b(param_c) && fun_c())
{
   do_something();
}
```
The *separators* in the code above are:
* `,`
* `;`

#### 1.4. Non-Unary Operator
An *non-unary operator* is a symbol that is put in between *groups* in infix
languages in order to merge them into a larger group.

**Example:**
```c
if (fun_a(param_a[0][a + b], param_b) && ~fun_b(param_c) && fun_c())
{
   do_something();
}
```
The *non-unary operators* in the code above are:
* `+`
* `&&`

#### 1.5. Unary Operator
An *operator* is a symbol that prefixes or suffixes *groups* in infix languages
in order to affect their value.

**Example:**
```c
if (fun_a(param_a[0][a + b++], param_b) && ~fun_b(param_c) && fun_c())
{
   do_something();
}
```
The *unary operators* in the code above are:
* `~`
* `++`

#### 1.6. Delimiters
*Groups* have *delimiters*. These may be implicit or explicit. A *delimiter* is
a symbol that marks the start of the *group* or its end. *Delimiters* are
considered to be part of the *group* they define. They usually come in pair,
with a specific symbol to indicate the *group* starting and another indicating
it closing.

**Example:**
```c
if (fun_a(param_a[0][a + b], param_b) && ~fun_b(param_c) && fun_c())
{
   do_something();
}
```
The *delimiters* in the code above are:
* `(` `)`
* `[` `]`
* `{` `}`

#### 1.7. Spacing
Are considered not next to each other to symbols separated by either a space,
tab, or newline.

## 2. Coding Rules

#### 2.0. Code for Humans
* When given a choice between a solution that is efficient and one that is
  readable by a human, prefer the human readable one unless the need for
  efficiency is critical.

#### 2.1. Restricting Keywords
* Always give as much information as possible, even when this makes the code
  verbose.
* Always use as much restricting keywords as possible.
* Assume that if a restricting keyword is absent, that is because it could not
  be added.

For example, in Java, every variable should be `final` unless it is modified.
Thus, upon seeing that a variable is not `final`, one should expect there is at
least one possible execution that will lead to it being modified.
 
#### 2.2. Type Conversions
Most languages will automatically infer necessary type conversions. This is
sometimes useful but often dangerous. In order to keep most of the useful
conversions but to ensure dangerous ones are removed, the following rule is
applied:
* Unless the type conversion involves an object being cast to a class that this
  object either belongs to or inherits from, all type conversions must be made
  explicit.

#### 2.3. Indentation
There is no rule about what constitutes a level of indentation, other than it
should ensure a increment of column. Tabulation or spaces are both acceptable,
as long as what constitutes a level of indentation is consistent thorough the
project.

The only way to change the indentation level is to enter a *group* definition or
leave a *group* definition. These may at most change the indentation level by
one, and have to decrease the indentation level on exit if they incremented it
upon entering. *Groups* use a different indentation level if, and only if, they
are defined over multiple lines. The *delimiters* of the *group* use the
indentation level in place outside the *group*.

Nothing can ignore the current indentation level.

The inside of *groups* that are defined on a single line do not have
indentation. The elements of a *group* that is defined over multiple line all
have the same level of indentation.

The keywords that precede a group are 
**Examples:**
* The following is allowed:
```c
void some_function (int a, int b)
{
   some_other_function
   (
      some_other_function_with_a_particularly_long_name(),
      a + b,
      rand() + b
   );
}
```
* The following is **forbidden**:
```c
void some_function (int a, int b)
{
   some_other_function
   (
      some_other_function_with_a_particularly_long_name(),
      a + b, rand() + b
   );
}
```
* The following is **forbidden**:
```c
void some_function (int a, int b)
{
   some_other_function(some_other_function_with_a_particularly_long_name(), a +
      b, rand() + b);
}
```

#### 2.4. Length Limits
* **Code line:** Avoid going beyond the 79th column (i.e. 80 characters per line)
  whenever possible.
* **Name:** Do not feel constrained by any length limit when naming something.
* **Function:** isolate logical blocks into separate functions whenever possible.

#### 2.5. Naming Conventions
As a general rule, use very descriptive name. Think *anti-assembly*: long,
self-explaining names are preferred to short, confusing names.

* **Class Names:** `[0-9A-Za-z]+`, with each word starting with a capital
  letter.
* **Constant Names:** `[0-9A-Z_]+`, with an underscore between words.
* **Everything Else:** `[0-9a-z_]+`, with an underscore between words.

Starting anything with an underscore indicates a hack. Those are instable and
can their meaning or disappear without warning.

If the language supports anonymous variables, these should be as descriptive as
they can.

#### 2.6. Operators Spacing
* *Non-unary operators* are not directly next to *delimiters* or *groups*.
* *unary operators* are directly next to *delimiters* or *groups*.
**Examples:**
* `a&&b` is **forbidden**.
* `a && b` is allowed.
* `a && ~b` is allowed.
* `a && ~ b` is **forbidden**.

#### 2.7. Operators and Groups
* Using different *non-unary operators* to merge multiple *groups* is forbidden.

**Examples:**
* `a && b || c && d` is **forbidden**.
* `(a[0] && b) || (c && d)` is allowed.
* `(a[0] && b) || (c && d) || a[1]` is allowed.
* `(a[0] && b) || (c && d) && a[1]` is **forbidden**.
* `(a[0] && b) || (c && d && a[1])` is allowed.
* `(a && ~b) || ~(c && d[e + f])` is allowed.

#### 2.8. Group Spacing
Any *group* that is not a *qualifying group* has *spacing* between it and any
keyword. If that *spacing* is a newline, the group is considered as being
defined over multiple lines.

*Qualifying groups* do not have *spacing* between them and the *group* they
qualify, unless the *qualifying group* does not fit on the line, in which case
they use a newline and become a multi-line *group*. *Qualifying
group* of multi-line *groups* are themselves multi-line. *Groups* with
multi-line *qualifying groups* themselves become multi-line *groups*.

**Examples:**
* `if(a)` is **forbidden**.
* `if (a)` is allowed.
* The following is **forbidden**:
```c
if
(a_very_long_line_that_somehow && fits_only_if_the_if_keyword_is_absent_from_it)
```
* The following is allowed:
```c
if
(
   a_very_long_line_that_somehow
   && fits_only_if_the_if_keyword_is_absent_from_it
)
```
* The following is allowed:
```c
if
(
   an_array_with_an_very_long_name_yet_still_able_to_remain_on_one_line[0]
   &&
   an_array_with_a_smaller_name
   [
      yet_it_is_a_multiline_one
      + because_its_qualifying_group_is_too_long
   ]
   [
      multi_line_is_contagious
   ]
)
```
* The following is **forbidden**:
```c
if
(
   an_array_with_an_very_long_name_yet_still_able_to_remain_on_one_line[0]
   &&
   an_array_with_a_smaller_name
   [
      yet_it_is_a_multiline_one
      + because_its_qualifying_group_is_too_long
   ]
   [multi_line_is_contagious]
)
```
* The following is **forbidden**:
```c
if
(
   an_array_with_an_very_long_name_yet_still_able_to_remain_on_one_line[0]
   &&
   an_array_with_a_smaller_name
   [
      yet_it_is_a_multiline_one
      + because_its_qualifying_group_is_too_long
   ][multi_line_is_contagious]
)
```
#### 2.9. Separators Spacing
 * *Separators* are directly next to the end of the group that precedes them but
   not directly next to the start of the group that follows them.
 * The *separators* of a *group* defined over multiple lines are never on the
   same line.

**Examples:**
* `fun(a , b , c)` is **forbidden**.
* `fun(a ,b ,c)` is **forbidden**.
* `fun(a, b, c)` is allowed.
* `fun(a,b,c)` is **forbidden**.
* The following is **forbidden**:
```c
void my_fun ()
{
   fun_a(); fun_b();
}
```
* The following is allowed:
```c
void my_fun ()
{
   fun_a();
   fun_b();
}
```
* The following is **forbidden**:
```c
function_call
(
   function_a, function_b,
   90,         30
);
```
* The following is **forbidden**:
```c
function_call
(
   function_a, function_b, 90, 30
);
```
* The following is allowed:
```c
function_call
(
   function_a,
   function_b,
   90,
   30
);
```

#### 2.10. Delimiter Positioning
 * *Instruction group* *delimiters* have their opening and closing symbol on the
   same column.
 * *Groups* that are defined over multiple lines have their opening and closing
   symbol on the same column.
 * *Separators* are directly next to the end of the *group* that precedes them.
 * *Groups* defined over multiple lines have explicit *delimiters*.

Note:
* Cases of `switch` structures are exempt from having to use explicit
  *delimiters*.

#### 2.11. Non-Unary Operators in Multi-line Groups
* Operators of a *group* defined over multiple lines are placed at the start of
  the line, following the identation level. If the *group* that follows them can
  fit in the line that *group* shares the line with the operator.

**Examples**:
* The following is allowed:
```c
(
   my_fun_a()
   && my_fun_b(0, 1, 2, 3 + 4)
   &&
   my_fun_c
   (
      a_very_long_argument_in_order_to_reach_the_line_limit(0, false, 4),
      some_other_argument
   )
   && (a || b || c)
   &&
   (
      my_cond_1
      || my_fairly_long_condition
      ||
      my_condition_with_an_ridiculously_long_name_that_keeps_on_going_and_going
   )
)
```

#### 2.12. Argument Order
`(WIP)`

Arguments used to return results should be last when possible. The order of
inputs should put the subject of modifications last. For example, adding a new
element at a certain index to a set should be in the `elem, index, set` order.

If a function has to return more than one value and tuples are not available in
the language, then use arguments instead, with the actual return value being
either a success indicator or no return value at all.

#### 2.13. Import/Export statements
`(WIP)`

Regroup import statement by library (the more general the library, the higher
it should be) leaving an empty line to separate each group. The elements of a
group should be sorted alphabetically.


Note:
* An acceptable exception to these rules is considering `else if` as a single
  keyword, thus not requiring the `if` to be a separate block from the `else`.
* The rules in this section do in fact specify that non-unary infix operators
  are not attached to their arguments and there is thus a either a space or a
  newline.

#### 2.14. Logical separations in instruction blocks
`(WIP)`

If the language allows separate declaration and definition (e.g. C, Java, but
not C++), declare (without defining) all variables at the start of the function.

No more than one instruction per line.

Do not declare variables of a different type on the same line (this also
forbids declaring pointers and non-pointers on the same line).

Separate declarations, assignments, function call, and loop/conditional/jump
structures with an empty line.
