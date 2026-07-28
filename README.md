*This project has been created as part of the 42 curriculum by demane.*

# CPP Module 06

## Description

**CPP Module 06** explores C++ casts and type identification. The goal is to convert scalar string literals, serialize pointers safely with `reinterpret_cast`, and identify dynamic types with `dynamic_cast` — all under C++98 constraints.

This module contains three exercises:

| Exercise | Focus |
|----------|--------|
| **ex00 — Conversion of scalar types** | `ScalarConverter::convert` — char / int / float / double |
| **ex01 — Serialization** | `Serializer` — `serialize` / `deserialize` via `uintptr_t` |
| **ex02 — Identify real type** | `Base` + `A`/`B`/`C`; identify by pointer and by reference |

### Overview

- Scalar conversion detects the literal type and prints all four representations, handling overflows, non-displayable chars, and pseudo-literals (`nan`, `+inf`, …).
- Serialization must round-trip a `Data*` through an integer type without using C-style casts.
- Type identification must work even when the dynamic type is unknown at compile time.

## Instructions

### Requirements

- A C++ compiler supporting **C++98**
- `make`

### Compilation

```bash
cd ex00   # or ex01 / ex02
make
make clean / fclean / re
```

Flags: `-Wall -Wextra -Werror -std=c++98`.

### Execution

```bash
./convert 42
./convert 42.0f
./convert nan
./exec        # ex01 / ex02
```

## Classes & components

| Class | Role |
|-------|------|
| `ScalarConverter` | Non-instantiable utility; static `convert(std::string)` |
| `Serializer` | Static `serialize(Data*)` / `deserialize(uintptr_t)` |
| `Base` / `A` / `B` / `C` | Polymorphic hierarchy for RTTI identification |
| Helpers | `identify(Base*)` and `identify(Base&)` |

## Resources

### Documentation & references

- [static_cast](https://en.cppreference.com/w/cpp/language/static_cast), [reinterpret_cast](https://en.cppreference.com/w/cpp/language/reinterpret_cast), [dynamic_cast](https://en.cppreference.com/w/cpp/language/dynamic_cast)
- [string to number](https://en.cppreference.com/w/cpp/string/byte/strtod) — parsing scalars carefully
- [typeid](https://en.cppreference.com/w/cpp/language/typeid) — related RTTI mechanism
- [uintptr_t](https://en.cppreference.com/w/cpp/types/integer)
- 42 subject: *CPP Module 06*

### Use of AI

AI assistance was used for:

- Drafting and formatting this `README.md` according to the 42 curriculum requirements
- Clarifying wording and structuring documentation sections

No AI-generated code was submitted as a substitute for personal implementation. The C++ sources were written and validated by the student.

---

*42 Paris — Common Core*
