# Computor-v1

A polynomial equation solver written in C++ that solves equations of degree 0, 1, and 2 (linear and quadratic equations).

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Building the Project](#building-the-project)
- [Usage](#usage)
- [Code Architecture](#code-architecture)
  - [Main Entry Point](#main-entry-point)
  - [Parser Class](#parser-class)
  - [Polynome Class](#polynome-class)
  - [Solver Class](#solver-class)
- [Algorithm Details](#algorithm-details)
- [Examples](#examples)

## Overview

Computor-v1 is a program that takes a polynomial equation as input, parses it, reduces it to standard form, and solves it. It handles:
- **Degree 0**: Constant equations (e.g., `5 = 5` or `3 = 7`)
- **Degree 1**: Linear equations (e.g., `5 * X = 10`)
- **Degree 2**: Quadratic equations (e.g., `5 * X^2 + 4 * X - 9.3 = 0`)

For quadratic equations, it calculates and displays the discriminant and provides:
- Two real solutions (positive discriminant)
- One real solution (zero discriminant)
- Two complex solutions (negative discriminant)

## Features

- ✅ Parse polynomial equations with variables
- ✅ Reduce equations to standard form
- ✅ Calculate polynomial degree
- ✅ Solve linear equations (degree 1)
- ✅ Solve quadratic equations (degree 2)
- ✅ Handle complex number solutions
- ✅ Display solutions in simplified fraction form for complex numbers
- ✅ Robust error handling with regex validation
- ✅ Support for equations with terms on both sides of the equals sign

## Project Structure

```
.
├── main.cpp          # Entry point of the application
├── Parser.hpp        # Parser class header
├── Parser.cpp        # Parser implementation
├── Polynome.hpp      # Polynome class header
├── Polynome.cpp      # Polynome implementation
├── Solver.hpp        # Solver class header
├── Solver.cpp        # Solver implementation
└── Makefile          # Build configuration
```

## Building the Project

### Prerequisites
- C++ compiler with C++11 support or later
- Make

### Compilation

```bash
make
```

This will create an executable named `computor`.

### Other Make Commands

```bash
make clean   # Remove object files
make fclean  # Remove object files and executable
make re      # Clean and rebuild
```

## Usage

```bash
./computor "equation"
```

### Example

```bash
./computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
```

### Output Format

The program outputs:
1. **Reduced form**: The equation in standard form
2. **Polynomial degree**: The highest degree of the polynomial
3. **Solution(s)**: The solution(s) to the equation

## Code Architecture

### Main Entry Point

**File**: `main.cpp`

The main function orchestrates the entire solving process:

```cpp
int main(int ac, char **av)
```

**Flow**:
1. Validates command-line arguments (requires at least one equation string)
2. Creates instances of `Parser`, `Polynome`, and `Solver` classes
3. Executes the solving pipeline:
   - `parser.splitTerms()`: Tokenizes the input equation
   - `parser.parseTerms(poly)`: Parses and normalizes the equation
   - `solver.solveAndPrint(poly)`: Solves and displays the result
4. Catches and displays any exceptions thrown during processing

### Parser Class

**Files**: `Parser.hpp`, `Parser.cpp`

The Parser class handles the lexical analysis and parsing of polynomial equations.

#### Key Member Variables

- `polynome`: The input equation string
- `term`: The variable character (e.g., 'X')
- `ls`: Vector storing left-side terms
- `rs`: Vector storing right-side terms
- `termExpByCoef`: Map associating exponents with their coefficients
- `exponent`: The maximum exponent (degree) found

#### Key Methods

**`void splitTerms()`**

Tokenizes the equation into left-side (LS) and right-side (RS) terms:
- Removes all whitespace from the input
- Finds the equals sign position
- Splits terms by '+' and '-' operators
- Identifies the polynomial variable (e.g., 'X')
- Throws an error if no equals sign is found

**`void parseTerms(Polynome &poly)`**

Processes the parsed terms and populates the Polynome object:
- Merges left and right sides into a normalized form
- Negates right-side terms (moves them to the left)
- Calls `matchRegexAndDefinePolyDegree()` to extract coefficients
- Sets the polynomial degree and coefficients

**`void matchRegexAndDefinePolyDegree(std::vector<std::string> &vec)`**

Validates and extracts coefficient values:
- Uses regex to validate term formats
  - Numbers: `^[+-]?\d+(\.\d+)?$`
  - Terms: `^([+-]?\d+(?:\.\d+)?)\*([X])\^(\d+)$`
- Extracts coefficients for each exponent
- Accumulates coefficients for like terms
- Determines the polynomial degree (highest exponent)

### Polynome Class

**Files**: `Polynome.hpp`, `Polynome.cpp`

The Polynome class represents a polynomial equation and stores its properties.

#### Key Member Variables

- `normalizedPoly`: Vector of normalized term strings
- `a`: Coefficient of X² (degree 2)
- `b`: Coefficient of X¹ (degree 1)
- `c`: Coefficient of X⁰ (constant term)
- `degree`: The polynomial degree

#### Key Methods

**`void setCoefficients(double a, double b, double c)`**

Sets the quadratic coefficients a, b, and c for the equation ax² + bx + c = 0.

**`double getCoefficientA/B/C() const`**

Getter methods returning the respective coefficients.

**`void setNormalizedPolyValue(std::string str)`**

Adds a term to the normalized polynomial vector.

**`std::string getReducedForm() const`**

Generates the reduced form string for display:
- Creates a map of degrees to term strings
- Formats each term with proper signs
- Orders terms from highest to lowest degree
- Returns the equation in the format: "a * X^2 + b * X^1 + c * X^0 = 0"

**`std::string formatDouble(const std::string& str) const`**

Removes trailing zeros from decimal numbers for cleaner output.

**`void setDegree(size_t deg)` / `size_t getDegree() const`**

Setter and getter for the polynomial degree.

### Solver Class

**Files**: `Solver.hpp`, `Solver.cpp`

The Solver class implements the mathematical algorithms to solve polynomial equations.

#### Key Member Variables

- `x1`, `x2`: Real solutions
- `z1`, `z2`: Complex solutions
- `typeOfSolution`: String describing the solution type

#### Key Methods

**`void solveAndPrint(Polynome &polynome)`**

Main solving algorithm:

1. **Retrieves coefficients** from the Polynome object
2. **Prints the reduced form** of the equation
3. **Checks the degree**:
   - If degree > 2: Cannot solve (displays message)
   - If degree ≤ 2: Proceeds with solving

4. **Solving Logic**:

   **For Quadratic Equations (a ≠ 0)**:
   - Calculates discriminant: Δ = b² - 4ac
   - **Positive discriminant (Δ > 0)**: Two distinct real solutions
     ```
     x₁ = (-b + √Δ) / 2a
     x₂ = (-b - √Δ) / 2a
     ```
   - **Zero discriminant (Δ = 0)**: One real solution
     ```
     x = -b / 2a
     ```
   - **Negative discriminant (Δ < 0)**: Two complex solutions
     - Displays solutions in the form: `p/q ± ri/s`
     - Uses GCD to simplify fractions
     - Handles positive and negative denominators correctly

   **For Linear Equations (a = 0, b ≠ 0)**:
   - Solves: bx + c = 0
   - Solution: x = -c / b

   **For Constant Equations (a = 0, b = 0)**:
   - If c = 0: Any real number is a solution
   - If c ≠ 0: No solution

**`long long gcd_ll(long long x, long long y)`**

Helper function to calculate the Greatest Common Divisor (GCD) for simplifying complex number fractions.

## Algorithm Details

### Quadratic Formula

For equations of the form **ax² + bx + c = 0**, the program uses:

**Discriminant**: Δ = b² - 4ac

**Solutions**:
- If Δ > 0: Two real solutions using the quadratic formula
- If Δ = 0: One real solution: x = -b / 2a
- If Δ < 0: Two complex solutions: x = (-b ± i√|Δ|) / 2a

### Normalization Process

1. Parse left and right sides of the equation separately
2. Move all terms to the left side (negate right-side terms)
3. Combine like terms (same exponents)
4. Express in standard form: ax² + bx + c = 0

### Complex Number Display

For complex solutions, the program:
- Calculates the real and imaginary parts
- Simplifies fractions using GCD
- Formats output as: `real/denominator ± imaginary*i/denominator`

## Examples

### Example 1: Quadratic with Two Real Solutions
```bash
./computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
```
Output:
```
Reduced form: 9.3 * X^2 - 4 * X^1 - 4 * X^0 = 0
Polynomial degree: 2
Discriminant is strictly positive, the two solutions are:
0.905239
-0.475131
```

### Example 2: Quadratic with Zero Discriminant
```bash
./computor "1 * X^2 - 4 * X^1 + 4 * X^0 = 0"
```
Output:
```
Reduced form: 1 * X^2 - 4 * X^1 + 4 * X^0 = 0
Polynomial degree: 2
The solution is:
2
```

### Example 3: Quadratic with Complex Solutions
```bash
./computor "1 * X^2 + 1 * X^0 = 0"
```
Output:
```
Reduced form: 1 * X^2 + 1 * X^0 = 0
Polynomial degree: 2
Discriminant is strictly negative, the two complex solutions are:
0/1 + 1i/1
0/1 - 1i/1
```

### Example 4: Linear Equation
```bash
./computor "5 * X^1 + 3 * X^0 = 1 * X^0"
```
Output:
```
Reduced form: 5 * X^1 + 2 * X^0 = 0
Polynomial degree: 1
The solution is:
-0.4
```

### Example 5: Constant Equation (No Solution)
```bash
./computor "4 * X^0 = 8 * X^0"
```
Output:
```
No solution.
```

### Example 6: Identity (Infinite Solutions)
```bash
./computor "4 * X^0 = 4 * X^0"
```
Output:
```
Any real number is a solution.
```

---

## Error Handling

The program includes robust error handling:
- **Missing argument**: "Not Arg Enough!"
- **Missing equals sign**: "Parsing Err : Equal not exist"
- **Invalid term format**: "Parsing Err : [term]"
- **Degree > 2**: "The polynomial degree is strictly greater than 2, I can't solve."

## Technical Notes

- **Compiler**: C++ with `-Wall -Wextra -Werror` flags
- **Standard**: C++11 or later (uses `<regex>` and `<complex>`)
- **Libraries**: STL (string, vector, map, regex, cmath, complex, numeric)
- **Memory Management**: RAII principles with automatic cleanup

---

**Author**: abel-all  
**Repository**: Computor-v1  
**License**: Not specified
