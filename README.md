# Tortilla-lang
A statically typed, easy to read compiled language, with a soft/hard error system.

```

array input = [0, 10, -3, 2, -5]

func aboveZero (array nums) array {
  array output = []
  forEach i in nums:
    if i >= 0:
      output.push(i)
    end
  end
  return output
}

print(aboveZero(input))

```
Tortilla is currently being created. The above code cannot yet run.

Tortilla has:
* A 2-level error system: soft errors allow the code to run while hard errors stop compilation
* Class oriented, allowing for easy inheritance, and the ability to run code on instance creation
* Statically typed with a first-class generics system
* Message-based modifiable threads

Tortilla is a general purpose language which has helpful errors and a forgiving type system.
It compiles to the LLVM, allowing for connection to WASM and speed.

Tortilla is still in Version 0, with a completed Lexer, Parser, AST, and Name Checker written in Python and a Lexer written in C++.

## Roadmap
- V0 — Working compiler in C++ by 2027
- V0.5 — Full testing and concurrency
- V1 — Multiple distribution methods, public release (before Summer 2028)
- V2 — Standard libraries and more language additions

Link to incomplete documentation: https://github.com/spencerjw10/Tortilla-lang/blob/main/spec/Tortilla-spec.md
