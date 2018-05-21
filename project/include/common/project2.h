/**
 * @file project2.h
 * @brief Function prototypes for project2.c
 * Contains function prototypes for project2, data processing, and stat dump
 * @author James Phillips
 * @date 7/17/2017
 */

 /**@brief Takes keyboard input, processes characters
  * Uses scanf to accept keyboard input, when termination character is entered,
  * Data is processed
  * @param
  * Inputs: None
  * @return - None
  */
void project2(void);

/**@brief Prints Processed Data from project2
 * Prints nice little table to see statistics from user input
 *
 * @param
 * Inputs: None
 * @return None
 */
void dump_statistics(void);

void process_data_kl25z(void);

void process_data(void);

void dump_statistics_kl25z(void);
