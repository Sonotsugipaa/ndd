<!-- This markdown document uses <br/> tags instead of double spaces,
   - because some editors (I'm looking at you, Visual Studio Code)
   - either remove all trailing whitespaces on save or none at all.
   - Modifying the document using double spaces instead of <br/>
   - *will* cause the file to brick at some point. -->

# ndd

## A simple command-line number representation converter, implemented in C++

`ndd` can be used to convert a number's representation on a whim, without having to pick a calculator or asking [Google](https://duckduckgo.com/). It's a standalone executable file, and only references the C++ standard library.

## Usage

`ndd` has 3 types of arguments, they can be placed anywhere, in any order, any number
of times; they are read from left to right. If `ndd` is used without arguments, a wall of text describing the syntax is printed out.

### Types of arguments

- **\[from=\<radix\>\]** <br/>
  *Example: from=16* <br/>
  The "from" argument sets the default radix to use on all remaining "number"
  arguments that are not represented with a prefix: <br/>
  For example, `from=20` will cause `1a` to be interpreted as a radix 20
  representation (= 30, radix 10), but `0x1a` will always be interpreted as a
  radix 16 representation (= 26, radix 10). <br/>
  - The default "from" radix is 10.
  - The \<radix\> part can itself use a different radix using a prefix, but the
    radix for representations without prefixes is always 10.

- **\[to=\<radix\>\]** <br/>
  *Example: to=16* <br/>
  The "to" argument follows the same rules and syntax of a "from" argument, but sets the
  default radix to use when printing out "number" arguments.

- **\<number\>** <br/>
  A number can be written as a positional representation using digits from 0 to z, where
  letters are case insensitive. <br/>
  If a number is written as-is, without any prefix, its radix is determined by the most
  recent "from" argument, or 10 if no such argument has been processed yet.

### Valid prefixes

| Prefix | Radix | Example (64) | Notes |
|---|:---|---|---|
| 0b | 2 | 0b1000000 | 0b is a known prefix, but it's not valid everywhere. |
| 0 | 8 | 0100, 000100 | Any number of `0` digits at the beginning will imply an octal representation. |
| 0o | 8 | 0o100 | |
| 0d | 10 | 0d64 | This prefix is almost never used, and, apparently, rarely valid. |
| 0x | 16 | 0x40 | |

Note that the letter in each prefix is, for `ndd`, case insensitive.

## Examples

These examples assume that `ndd` is running on a Unix-like system, and that
the executable file is in the search path; in this table outputs will be
separated by spaces, while the actual output will result in multiple lines.

| `ndd` shell command | Output (stdout) | Output (stderr) | Notes |
|:---|---|---|---|
| `ndd 0b101` | `5` | | |
| `ndd from=2 101` | `5` | | |
| `ndd from=16 0b101` | `5` | | |
| `ndd 5 to=2` | `5` | | `to=2` should come before the \<number\> argument. |
| `ndd 5 to=16` | `5` | | `to=16` should come before the \<number\> argument. |
| `ndd to=10 0b101 0x101` | `5 257` | | |
| `ndd to=10 from=2 101 from=16 101` | `5 257` | | |
| `ndd to=0b10 0b10` | `10` | | The "to" argument uses a prefix. |
| `ndd to=0x10 0x10` | `10` | | |
| `ndd to=010 from=8 10` | `10` | | |
| `ndd to=010 010` | `10` | | |
| `ndd this_is_nan 10 0b10` | | `10 2` | An invalid argument causes the following arguments to be printed to stderr. |
| `ndd 10 11 this_is_nan 0b10 0b11` | `10 11` | `2 3` | |
| `ndd to=36 35` | `z` | | Base 36 uses the whole English alphabet. |
| `ndd to=36 29234652 54903217` | `hello world` | | |
| `ndd from=36 hello world` | `29234652 54903217` | | |
