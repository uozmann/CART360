/* LED MATRIX PATTERNS == DESIGN FOUR CUSTOM PATTERNS 
 *  
   THERE ARE TWO WAYS THAT YOU CAN CONSTRUCT YOUR PATTERNS:
   a) DEFINE SET DATA FOR EACH ROW IN LED MATRIX (8 Rows of 8 LEDs = 64 LEDs)
*/

/* STORE ALL FOUR PATTERNS IN TWO DIMENSIONAL ARRAY - */
  byte splats[4][8] = {
  { /* PATTERN 1 */
    B00000000, // ROW 0 (8 LED DOTS)
    B11111111, // ROW 1 (8 LED DOTS) 
    B00000000, // ROW 2 (8 LED DOTS)
    B11111111, // ROW 3 (8 LED DOTS)
    B00000000, // ROW 4 (8 LED DOTS)
    B11111111, // ROW 5 (8 LED DOTS)
    B00000000, // ROW 6 (8 LED DOTS)
    B11111111  // ROW 7 (8 LED DOTS)
   },
   { /* PATTERN 2 */ 
    B10101010, // ROW 0 (8 LED DOTS)
    B10101010, // ROW 1 (8 LED DOTS) 
    B10101010, // ROW 2 (8 LED DOTS)
    B10101010, // ROW 3 (8 LED DOTS)
    B10101010, // ROW 4 (8 LED DOTS)
    B10101010, // ROW 5 (8 LED DOTS)
    B10101010, // ROW 6 (8 LED DOTS)
    B10101010  // ROW 7 (8 LED DOTS)
   },
   { /* PATTERN 3 */ 
    B00000000, // ROW 0 (8 LED DOTS)
    B00000000, // ROW 1 (8 LED DOTS) 
    B00100100, // ROW 2 (8 LED DOTS)
    B00111100, // ROW 3 (8 LED DOTS)
    B00111100, // ROW 4 (8 LED DOTS)
    B00100100, // ROW 5 (8 LED DOTS)
    B00000000, // ROW 6 (8 LED DOTS)
    B00000000  // ROW 7 (8 LED DOTS)
   },
   { /* PATTERN 4 */ 
    B11100111, // ROW 0 (8 LED DOTS)
    B11000011, // ROW 1 (8 LED DOTS) 
    B10000001, // ROW 2 (8 LED DOTS)
    B00000000, // ROW 3 (8 LED DOTS)
    B10000001, // ROW 4 (8 LED DOTS)
    B11000011, // ROW 5 (8 LED DOTS)
    B11100111, // ROW 6 (8 LED DOTS)
    B00011000  // ROW 7 (8 LED DOTS)
   }
  };

   byte splatsInverse[4][8] = {
  { /* PATTERN 1 */
    B11111111, // ROW 0 (8 LED DOTS)
    B00000000, // ROW 1 (8 LED DOTS) 
    B11111111, // ROW 2 (8 LED DOTS)
    B00000000, // ROW 3 (8 LED DOTS)
    B11111111, // ROW 4 (8 LED DOTS)
    B00000000, // ROW 5 (8 LED DOTS)
    B11111111, // ROW 6 (8 LED DOTS)
    B00000000 // ROW 7 (8 LED DOTS)
   },
   { /* PATTERN 2 */ 
    B01010101, // ROW 0 (8 LED DOTS)
    B01010101, // ROW 1 (8 LED DOTS) 
    B01010101, // ROW 2 (8 LED DOTS)
    B01010101, // ROW 3 (8 LED DOTS)
    B01010101, // ROW 4 (8 LED DOTS)
    B01010101, // ROW 5 (8 LED DOTS)
    B01010101, // ROW 6 (8 LED DOTS)
    B01010101  // ROW 7 (8 LED DOTS)
   },
   { /* PATTERN 3 */ 
    B11111111, // ROW 0 (8 LED DOTS)
    B11111111, // ROW 1 (8 LED DOTS) 
    B11011011, // ROW 2 (8 LED DOTS)
    B11000011, // ROW 3 (8 LED DOTS)
    B11000011, // ROW 4 (8 LED DOTS)
    B11011011, // ROW 5 (8 LED DOTS)
    B11111111, // ROW 6 (8 LED DOTS)
    B11111111  // ROW 7 (8 LED DOTS)
   },
   { /* PATTERN 4 */ 
    B00011000, // ROW 0 (8 LED DOTS)
    B00111100, // ROW 1 (8 LED DOTS) 
    B01111110, // ROW 2 (8 LED DOTS)
    B11111111, // ROW 3 (8 LED DOTS)
    B01111110, // ROW 4 (8 LED DOTS)
    B00111100, // ROW 5 (8 LED DOTS)
    B00011000, // ROW 6 (8 LED DOTS)
    B11100111  // ROW 7 (8 LED DOTS)
   }
  };
