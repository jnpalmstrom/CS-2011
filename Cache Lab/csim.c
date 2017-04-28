/** csim.c 
 * Program to simulate the functionalities of a cache memory
 *
 * @author Jack Palmstrom
 * @author Haiau Duong
 */

// Name: Jack Palmstrom
// Name: Haiau Duong
// Team: jnpalmstrom-hkduong
// Date: 4/26/2017

// --------------- Header Files --------------- //
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
// -------------------------------------------- //


// Initialization of variables found in csim-ref disassembly
int verbosity = 0;
int S = 0;
int B = 0;

int s = 0;
int E = 0;
int b = 0;

int hit_count = 0;
int miss_count = 0;
int eviction_count = 0;

struct cached_item {
  int val_bit;
  long long tag;
  int lru_counter;
};

struct cached_item ** cache = NULL;
long long set_index_mask = 0;
long long lru_counter = 0;

// Function Calls found in csim-ref disassembly
void printUsage(char* name);
void initCache();
void replayTrace(char * trace_file);
void freeCache();


/** Main function takes in command line arguments and runs functions
 *  to simulate a cache and report the number of hits, misses, and evictions.
 * @param argc The count of inputted arguments to the command line
 * @param argv The character array of the command line input
 * @return 0 indicates a success, while 1 indicates an error
 */
int main(int argc, char * argv[]) {
  
  char *trace_file = NULL;
  char any_option = 0; // Set option to zero
	
  while ((any_option = getopt(argc, argv, "s:E:b:t:vh")) != -1) {
    
    switch (any_option) {
    
    case 's':
      s = atoi(optarg); // Converts s (character string) from command line to an int
      break;
			
    case 'E':
      E = atoi(optarg); // Converts E (character string) from command line to an int
      break;
			
    case 'b':
      b = atoi(optarg); // Converts b (character string) from command line to an int
      break;
			
    case 't':
      trace_file = optarg; // Stores the info from optarg to trace_file 
      break;
			
    case 'v':
      verbosity = 1; // Sets verbosity to 1 if verbose flag is set to ON
      break;
			
    default:
      printUsage(argv[0]);
      return 1; // Error
    }
  }

  // Checks that none of the command line inputs are zero
  if (s == 0 || E == 0 || b == 0 || trace_file == 0) {
    printf("%s: Please input all necessary command line arguments.\n", argv[0]);
    printUsage(argv[0]);
    return 1; // Error
  }

  // Calculates the number of sets and the block size based off inputs
  S = 1 << s;  // Derived from formula S = 2^s
  B = 1 << b;  // Derived from formula B = 2^b

// Call function to simulate cache memory
  initCache();
  replayTrace(trace_file);
  freeCache();

  printSummary(hit_count, miss_count, eviction_count);
  return 0; // Success
}


/** Function prints how to provide command line arguments to this
 *  cache memory simulation program as well as the purpose of each argument 
 * @param name The name of the program provided as the first command line arg
 */
void printUsage(char* name) {

  printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", name);
  puts("Options:\n");
  puts("  -h         Print this help message.\n");
  puts("  -v         Optional verbose flag.\n");
  puts("  -s <num>   Number of set index bits.\n");
  puts("  -E <num>   Number of lines per set.\n");
  puts("  -b <num>   Number of block offset bits.\n");
  puts("  -t <file>  Trace file.\n");
  puts("\nExamples:\n");
  printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", name);
  printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", name);

  exit(0); // Success
}


/** This function initializes space in memory for a cache
 *
 */
void initCache() {

  int index; // Initialize counting variable

  
  cache = malloc(S * sizeof(*cache));
  
  for (index = 0; index < S; index++) {
    cache[index] = calloc(E, sizeof(*cache[index])); 
  }
  set_index_mask = S - 1;
}


/** Indicates whether the given address is located in the cache memory by finding 
 *  if it is a hit, miss, or eviction
 * @param address The memory address of what you are searching the cache for  
 */
void accessData(long long address){

  int index; // Initialize counting variable
  long long set = (address >> b) & set_index_mask; 
  long long tag = (address >> (s + b)); 

  for (index = 0; index < E; index++) {
	
    if ((cache[set][index].tag == tag) & (cache[set][index].val_bit != 0)) {

      hit_count = hit_count + 1; // Increment hit if the tags matched and something valid is stored there
      
      // Print out the hit if verbosity flag is turned ON	
      if (verbosity) {
	printf("hit ");
      }

      lru_counter++;
      cache[set][index].lru_counter = lru_counter;
      return;
    }
  }

  long long min_addr_lru = 0xFFFFFFFF;
  int evicted_line = 0;
	
  miss_count++; // Increment the miss count if the condition above fails

  // Print out the miss if verbosity flag is turned ON 
  if (verbosity) {
    printf("miss ");
  }
  
  for(index = 0; index < E; index++) {
    
    if (cache[set][index].lru_counter < min_addr_lru) {
      evicted_line = index;
      min_addr_lru = cache[set][index].lru_counter;
    }
  }

  if (cache[set][evicted_line].val_bit == 1) {
    
    eviction_count++; // Increment the eviction count if the line is already used

    // Print out the eviction if verbosity flag is turned ON
    if (verbosity) {
      printf("eviction ");
    }
  }

  lru_counter++; // Increment the least recently used (LRU) count by 1

  cache[set][evicted_line].val_bit = 1;
  cache[set][evicted_line].tag = tag;
  cache[set][evicted_line].lru_counter = lru_counter;
}


/** checks whether the trace_file is valid and what kind of 
 * @param trace_file Memory traces created by valgrind with each 
 * line denoting one or two memory accesses 
 *
 */
void replayTrace(char* trace_file){

  // Open up the trace file in read mode
  FILE *f = fopen(trace_file, "r");
  char buffer[500]; // Set the size of the buffer

// Checks the file contains data
  if (f == NULL) {
    printf("%s: No such file or directory!", trace_file);
    return;
  }

  while(fgets(buffer, 500, f)) {

    unsigned long long address = 0;
    int length = 0;
    
    // Doesn't look at I because it indicates instruction fetches
    if ((buffer[1] == 'S') | (buffer[1] == 'L') | (buffer[1] == 'M')) {
      
      sscanf(buffer + 2, "%llx, %d", &address , &length);

      if (verbosity) {
	printf("%c %llx, %d ", buffer[1], address, length);
      }
      accessData(address);
    }

    if (buffer[1] == 'M') {
      accessData(address);
    }

    printf("\n");
  }
  fclose(f); // Close the file upon completion
}

/** This function frees space in memory that was allocated to the cache
 *
 */
void freeCache() {

  int index; // Initialize counting variable
  
  for(index = 0; index < S; index++) {
    free(cache[index]);
  }
  free(cache);
}


