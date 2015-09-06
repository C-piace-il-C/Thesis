struct encParams
{
  int argc;
  char** argv;
};

void* encoding_thread(void* p)
{
  struct encParams* params = (struct encParams*)p;
  TAppEncTop* encoder = new TAppEncTop;
  encoder->create();
  encoder->parseCfg(params->argc, params->argv);
  encoder->encode(0);
  encoder->destroy();
  return(NULL);
}

/*
 * mergeBins(const char* file1, const char* file2)
 * this function merges file1 and file2 to one unique file
 * by placing the two contents together and deletes the
 * two files.
 */
void mergeBins(const char* file1, const char* file2);

// ==========================================================
// Main function
// ==========================================================
int main(int argc, char* argv[])
{
  [...]
  // Setup thread parameters
  TAppEncTop cTAppEncTop;
  encParams params;
  params.argc = argc;
  params.argv = argv0;
  
  // Start benchmark
  Double dResult;
  clock_t lBefore = clock();
  
  // Multithreaded encoding
  pthread_t encThread;
  pthread_create(&encThread, NULL, encoding_thread, (void*)&params);
  cTAppEncTop.create();
  cTAppEncTop.parseCfg(argc, argv1);
  cTAppEncTop.encode(frameCount_t0);
  cTAppEncTop.destroy();
  pthread_join(encThread, NULL);
  
  // End benchmark
  dResult = (Double)(clock()-lBefore) / CLOCKS_PER_SEC;
  printf("\n Total Time: %12.3f sec.\n", dResult);
  mergeBins("str0.bin", "str1.bin");
}


void mergeBins(const char* file1, const char* file2)
{
  char* destFilename = new char[strlen(file1) + 15];
  memcpy(destFilename, file1, strlen(file1) - 1);
  sprintf(destFilename + strlen(file1) - 1, "_merged.bin");

  printf("****** merge_dest: %s\n", destFilename);


  // Open bin0, bin1 and dest files
  FILE *dest, *bin0, *bin1;
  if((bin0 = fopen(file1, "rb")) == NULL)
  {
    perror("error opening bin0");
    return;
  }
  if((bin1 = fopen(file2, "rb")) == NULL)
  {
	fclose(bin0);
    perror("error opening bin1");
    return;
  }
  if((dest = fopen(destFilename, "wb")) == NULL)
  {
	fclose(bin0);
	fclose(bin1);
    perror("error opening dest");
    return;
  }

  // Merge bin0 and bin1 to dest
#define _BUFFSIZE_ 1000
  char* buffer = new char[_BUFFSIZE_];
  size_t bytesRead;
  do
  {
    bytesRead = fread(buffer, 1, _BUFFSIZE_, bin0);
    fwrite(buffer, bytesRead, 1, dest);
  } while (bytesRead == _BUFFSIZE_);
  fclose(bin0);
  do
  {
    bytesRead = fread(buffer, 1, _BUFFSIZE_, bin1);
    fwrite(buffer, bytesRead, 1, dest);
  } while (bytesRead == _BUFFSIZE_);
  fclose(bin1);
  fclose(dest);

  // Delete bin0 and bin1
  remove(file1);
  remove(file2);
}