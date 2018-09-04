#include "rya.h"
#include "rya_seq.h"

#include <stdlib.h>
#include <string.h>

rya_seq*
rya_seq_new_from_id_seq_len(char* id,
                            char* seq,
                            size_t id_len,
                            size_t seq_len)
{
  if (id == NULL || seq == NULL) {
    return NULL;
  }

  rya_seq* rseq = malloc(sizeof *rseq);
  if (rseq == NULL) {
    return NULL;
  }

#ifdef HAVE_STRNDUP
  rseq->id = strndup(id, id_len);
#else
  rseq->id = strdup(id);
#endif

  if (rseq->id == NULL) {
    rya_free(rseq);

    return NULL;
  }

#ifdef HAVE_STRNDUP
  rseq->seq = strndup(seq, seq_len);
#else
  rseq->seq = strdup(seq);
#endif

  if (rseq->seq == NULL) {
    rya_free(rseq->id);
    rya_free(rseq);

    return NULL;
  }

  rseq->id_len  = id_len;
  rseq->seq_len = seq_len;

  return rseq;
}

void
rya_seq_free(rya_seq* rseq)
{
  if (rseq != NULL) {
    rya_free(rseq->id);
    rya_free(rseq->seq);
    rya_free(rseq);
  }
}
