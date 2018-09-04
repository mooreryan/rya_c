/**
 * @file
 * @author Ryan Moore
 * @brief I'm the header for the seq functions.
 */

#ifndef _RYA_SEQ_H
#define _RYA_SEQ_H

#include <stdlib.h>

/**
 * @brief Light wrapper for fasta sequences.
 */
typedef struct rya_seq_t
{
  size_t id_len;
  size_t seq_len;

  char* id;
  char* seq;
} rya_seq;

/**
 * @brief Make a new rya_seq
 * @param id
 * @param seq
 * @param id_len
 * @param seq_len
 * @retval NULL on errors of if params are bad/NULL
 * @retval a new malloc'd rya_seq
 * @note Caller must free the return value using rya_seq_free()
 */
rya_seq*
rya_seq_new_from_id_seq_len(char* id,
                            char* seq,
                            size_t id_len,
                            size_t seq_len);

/**
 * @brief Free a rya seq.
 * @param rseq
 * @remark I won't try and dereference a NULL pointer.
 */
void
rya_seq_free(rya_seq* rseq);

#endif // _RYA_SEQ_H
