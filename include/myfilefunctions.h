//count the number of lines, words and characters in the passed file stream ponter. Return 0 on success an -1 on failure.
int wordCount(FILE* file, int* lines, int* words, int* chars);

//Search lines containing search_str in a file, and fills the matches array. Return the count of matches and -1 in failure.
int mygrep(FILE* file, const char* search_str, char*** matches);
