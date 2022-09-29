# Printf

This project is a remake of the mighty printf() function.

  - %c Prints a single character;
  - %s Prints a string (as defined by the common C convention);
  - %p The void * pointer argument has to be printed in hexadecimal format;
  - %d Prints a decimal (base 10) number;
  - %i Prints an integer in base 10;
  - %u Prints an unsigned decimal (base 10) number;
  - %x Prints a number in hexadecimal (base 16) lowercase format;
  - %X Prints a number in hexadecimal (base 16) uppercase format;
  - %% Prints a percent sign;
  
It also handles any combination of the flags:

  - '0' Left-pads the number with zeroes (0) instead of spaces when padding is specified;
  - '-' Left-justify within the given field width; Right justification is the default;
  - '*' Width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.
  - '.' Precision is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.
