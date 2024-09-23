# Style
Obey this style

## Names
* Function names and variable names are in snake_case
* Classes, structs, and namespaces are in PascalCase

## Braces
Allman Style

## Spacing
* All operators are have a space on both ends
* The condition after if, while, and for statements has one space
* No spaces between doc comment and definition

## Classes, Structs, and Namespaces
* Order: Public, protected, private
* Only exceptions are begin() and end() when class has its own iterator in private.
* If there is only static functions and no templates, use namespace
* Use structs for common mathematical objects or data can be use as a property
* For each access specifier group, put variables before functions

## Variable Naming
* Prepend member variables with m_

## Iterators
* Use LinkedIterator to iterate through linked lists
* Use std::vector begin() and end() if possible

## Conversions
* Arrays -> std::vector
* Comparator -> Use compare(A, B) { return A < B }
* Private classes that implement Comparable -> Implement compare function
* Iterator -> Implement C++ iterator
* Object or Generics -> Use templates with typename
* assert x -> Use assert(x)
* Exceptions -> Use error()
* Infinity -> Use std::numeric_limits::infinity()
* NaN -> Use std::numeric_limits::signaling_NaN()
* Math -> Use math functions from cmath
* String -> std::string
* boolean -> bool
* Remove final from fields and class declarations
* Instead use const on functions that don't change member variables
* equals() method implementation -> operator=() and operator!=()
* compareTo() method implementation-> operator<(), operator>(), operator<=(), and operator>=()
* Remove type checking
* this.field -> m_field (This is the only Hungarian Notation)
* this.function() -> function()
* toString() -> Implement to_string() and operator<<() functions
* Arrays.sort() -> std::sort()
* String splitting -> Use strtok()
* byte -> uint8_t

## Other
* If possible use smart pointers (ptr<T>)
* If possible use references