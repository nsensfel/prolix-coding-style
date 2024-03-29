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

#### 1.8. Member Access
`(WIP)`

*Member accesses* correspond to accessing [...]

## 2. Coding Rules

#### 2.0. Code for Humans
* When given a choice between a solution that is efficient and one that is
  readable by a human, prefer the human readable one unless the need for
  efficiency is critical.

* Don't rely on automated inference, specify what you expect to have so that
  people don't have to think about what should happen. It'll also make software
  able to tell you when you make wrong assumptions.

#### 2.1. Restricting Keywords
* Always give as much information as possible, even when this makes the code
  verbose.
* Always use as much restricting keywords as possible.
* Assume that if a restricting keyword is absent, that is because it could not
  be added.

For example, in Java, every variable should be `final` unless the object it
refers to (or its value, in the case of a primitive) is changed.
Thus, upon seeing that a variable is not `final`, one should expect there is at
least one possible execution that will lead to it changing which object it
refers to.

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

Indentations tabs, if used, should only be present between the start of a line
and its first non-tab character. Use spaces to align content past that point.

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
 * The only thing allowed to share a line with the *delimiter* of a multi-line
   *group* is a *separator* (and the identation).

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
* The rules in this section do in fact specify that non-unary infix operators
  are not attached to their arguments and there is thus a either a space or a
  newline.

#### 2.14. Logical Separations in Instruction Groups
`(WIP)`

If the language allows separate declaration and definition (e.g. C, Java, but
not C++), declare (without defining) all variables at the start of the function.

No more than one instruction per line.

Do not declare variables of a different type on the same line (this also
forbids declaring pointers and non-pointers on the same line).

Separate statements of a different kind by an empty line. For example, put an
empty line before an assignment if it follows a declaration.

Any statement following a multi-line statement should be preceded by an empty
line (i.e. keep an empty line after any multi-line statement if it isn't the end
of the instruction group).

#### 2.15. Compatibility
The code should be written using ASCII characters. Non-ASCII characters outside
of their use as a value or when commenting is forbidden.

#### 2.16. Constant Literals
Avoid unnamed constant literals (e.g. magic numbers) when possible.

In order to help readability, specify the name of the argument using a comment
when passing a constant literal to a function call.

#### 2.17. Do not Ignore Warnings
* Always compile with as much warnings enabled as possible.
* Consider all warnings as errors.
* In case of false positive, disable check for that particular instance, not
  for the whole compilation.

#### 2.18. Member Accesses Spacing
There is no spacing between a *member accesses* and its parent *group*.

#### 2.19. Unary Operators Disambiguation
* If a *group* has both a *unary operator* prefixing it and a *unary operator*
  suffixing it, there is a risk of ambiguity. If the order in which the
  operators are performed relies on a priority defined by the language
  disambiguation through explicit group delimiters must be implemented.
* If a prefix *unary operator* is applied to a *group* with a *member access*
  and the order between *member access* and application of the *unary operator*
  only depends on the priority defined by the language and not typing,
  disambiguation through explicit group delimiters must be implemented.

### 3. Special Cases
#### 3.0. Indentation Exceptions
* If the left side of an assignment cannot fit in the line, it goes to a new
  line and creates its own incremented indentation level before the *group*
  becomes a multi-line one. If the *group* can fit in that new line, the *group*
  does not become a multi-line *group*.
* The same rule as above applies to the argument of a `return` statement.
* `else if` is considered to be a single keyword and is thus exempts from the
  need to have an `else { if [...] }` construct.
