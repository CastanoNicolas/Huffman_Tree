#ifndef COMPRESSION_FUN
#define COMPRESSION_FUN


int* frequencies_of_occurences(char* file_name);
huffman_tree* build_huffman_tree(int* frequencies);
#endif
