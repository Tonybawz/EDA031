#ifndef CODING_H
#define CODING_H

class coding {
/* For any character c, encode(c) is a character different from c */
public:
static char encode(char c);
/* For any character c, decode(encode(c)) == c */
static char decode(char c);
};
#endif
