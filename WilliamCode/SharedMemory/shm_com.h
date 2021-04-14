#define TEXT_SZ 2048

struct shared_use_st{
  //to tell the consumer when data has you been written
  int written_by_you;
  // transfer data 2K
  char some_text[TEXT_SZ];

};
