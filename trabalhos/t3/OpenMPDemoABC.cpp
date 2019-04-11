#include <iostream>
#include <string>
#include <omp.h>
#include <algorithm>

using namespace std;

class ArrayFiller{
 private:
   char *array;
   int chunk = 0;
   int nThreads = 0;
   int nTimes = 0;
   int size = 0;
   int index = 0;

 public:
   ArrayFiller(int nThreads, int nTimes, int chunk){
      this->nThreads = nThreads;
      this->nTimes = nTimes;
      this->chunk = chunk;
      this->size = this->nThreads * this->nTimes;
      array = new char[size];
      fill(array, array + size, '-');
      omp_set_num_threads(nThreads);
   }
   ~ArrayFiller(){
      delete array;
   }
   void spendSomeTime(){
      for (int i = 0; i < 10000; i++){
         for (int j = 0; j < 100; j++){
            // These loops shouldn't be removed by the compiler
         }
      }
   }
   void addChar(char c, char *array, bool exclusaoMutua){
      if (exclusaoMutua){
         #pragma omp critical
         {
            array[index] = c;
            //spendSomeTime();
            index++;
         }
      }else{
         array[index] = c;
         //spendSomeTime();
         index++;
      }
   }
   void fillArrayStaticChunk(){
      int i;
      #pragma omp parallel for shared(array) schedule(static, chunk)
      for (i = 0; i < size; i++)
         //addChar('A' + omp_get_thread_num(), array, true);
         array[i] = 'A'+ omp_get_thread_num();
   }

   void fillArrayStatic(){
      #pragma omp parallel for shared(array) schedule(static)
      for (int i = 0; i < size; i++)
         //addChar('A' + omp_get_thread_num(), array, true);
         array[i] = 'A'+ omp_get_thread_num();
   }
   void fillArrayDynamicChunk(){
      #pragma omp parallel for shared(array) schedule(dynamic, chunk)
      for (int i = 0; i < size; i++)
         //addChar('A' + omp_get_thread_num(), array, true);
         array[i] = 'A'+ omp_get_thread_num();
   }
   void fillArrayDynamic(){
      #pragma omp parallel for shared(array) schedule(dynamic)
      for (int i = 0; i < size; i++)
         //addChar('A' + omp_get_thread_num(), array, true);
         array[i] = 'A'+ omp_get_thread_num();
   }
   void fillArrayGuidedChunk(){
      #pragma omp parallel for shared(array) schedule(guided, chunk)
      for (int i = 0; i < size; i++)
         //addChar('A' + omp_get_thread_num(), array, true);
         array[i] = 'A'+ omp_get_thread_num();
   }
   void fillArrayGuided(){
      #pragma omp parallel for shared(array) schedule(guided)
      for (int i = 0; i < size; i++)
         //addChar('A' + omp_get_thread_num(), array, true);
         array[i] = 'A'+ omp_get_thread_num();
   }
   void fillArrayRunTime(){
      #pragma omp parallel for shared(array)
      for (int i = 0; i < size; i++)
         //addChar('A' + omp_get_thread_num(), array, true);
         array[i] = 'A'+ omp_get_thread_num();
   }
   void fillArrayAuto(){
      #pragma omp parallel for shared(array) schedule(auto)
      for (int i = 0; i < size; i++)
         //addChar('A' + omp_get_thread_num(), array, true);
         array[i] = 'A'+ omp_get_thread_num();
   }

   void fillArrayStaticError(){
      #pragma omp parallel for shared(array) schedule(static)
      for (int i = 0; i < size; i++)
         //addChar('A' + omp_get_thread_num(), array, false);
         array[i] = 'A'+ omp_get_thread_num();
   }

   void printStats(){
      cout << string(array, size) << endl;
      for (int i = 0; i < nThreads; ++i)
         cout << (char)('A' + i) << "="
                   << countOccurrences('A' + i, array) << " ";
      cout << endl;
   }
   int countOccurrences(char c, char *array){
      return count(array, array + size, c);
   }
};

int main(int argc, char **argv){
   if ((argc != 4)){
      printf("Uso: %s <nthreads> <nTimes> <chunk>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   int nThreads = atoi(argv[1]);
   int nTimes = atoi(argv[2]); // nTimes = número de vezes que cada thread escreve no vetor
   int chunk = atoi(argv[3]);  // tamanho das "cargas" atribuídas pelo schedule às threads

   cout << "Cada Thread deve adicionar o seu char n vezes, n=" << nTimes << endl;
   cout << "Resultado correto deve totalizar nThreads x nTimes => " << nTimes * nThreads << endl;

   cout << "Caso 1: schedule static com chunk = " << chunk << endl;
   ArrayFiller m1(nThreads, nTimes, chunk);
   m1.fillArrayStaticChunk();
   m1.printStats();
   cout << endl;

   cout << "Caso 2: schedule static sem chunk "<< endl;
   ArrayFiller m2(nThreads, nTimes, chunk);
   m2.fillArrayStatic();
   m2.printStats();
   cout << endl;

   cout << "Caso 3: schedule dynamic com chunk = " << chunk << endl;
   ArrayFiller m3(nThreads, nTimes, chunk);
   m3.fillArrayDynamicChunk();
   m3.printStats();
   cout << endl;

   cout << "Caso 4: schedule dynamic sem chunk " << endl;
   ArrayFiller m4(nThreads, nTimes, chunk);
   m4.fillArrayDynamic();
   m4.printStats();
   cout << endl;

   cout << "Caso 5: schedule guided com chunk = " << chunk << endl;
   ArrayFiller m5(nThreads, nTimes, chunk);
   m5.fillArrayGuidedChunk();
   m5.printStats();
   cout << endl;

   cout << "Caso 6: schedule guided sem chunk " << endl;
   ArrayFiller m6(nThreads, nTimes, chunk);
   m6.fillArrayGuided();
   m6.printStats();
   cout << endl;

   cout << "Caso 7: schedule runtime " << endl;
   ArrayFiller m7(nThreads, nTimes, chunk);
   m7.fillArrayRunTime();
   m7.printStats();
   cout << endl;

   cout << "Caso 8: schedule auto " << endl;
   ArrayFiller m8(nThreads, nTimes, chunk);
   m8.fillArrayAuto();
   m8.printStats();
   cout << endl;

   cout << "Caso 9: schedule static sem chunk e sem exclusao mútua " << endl;
   ArrayFiller m9(nThreads, nTimes, chunk);
   m9.fillArrayStaticError();
   m9.printStats();
   cout << endl;
   
}
