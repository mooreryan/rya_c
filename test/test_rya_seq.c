#include "unity.h"
#include "rya_seq.h"
#include "rya.h"

#include <string.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test___rya_seq_new_from_id_seq_len___shouldMakeNewRyaSeq(void)
{
  // Make a new seq from fasta.  I.e., just id and sequence.
  char* id = "seq1";
  char* seq = "actg";

  size_t id_len = strlen(id);
  size_t seq_len = strlen(seq);

  rya_seq* rseq = rya_seq_new_from_id_seq_len(id, seq, id_len, seq_len);

  TEST_ASSERT_EQUAL_STRING(id, rseq->id);
  TEST_ASSERT_EQUAL_STRING(seq, rseq->seq);
  TEST_ASSERT_EQUAL(id_len, rseq->id_len);
  TEST_ASSERT_EQUAL(seq_len, rseq->seq_len);

  rya_free(rseq->id);
  rya_free(rseq->seq);
  rya_free(rseq);
}

void test___rya_seq_new_from_id_seq_len___shouldReturnNullWithErrors(void)
{
  TEST_ASSERT_NULL(rya_seq_new_from_id_seq_len("seq1", NULL, 4, 4));
  TEST_ASSERT_NULL(rya_seq_new_from_id_seq_len(NULL, "ACTG", 4, 4));
}
