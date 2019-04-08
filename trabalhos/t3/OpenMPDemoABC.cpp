#include <algorithm>
#include <iostream>
#include <string>
#include <omp.h>

class SharedArray {
private:
   char* array;
   int index;
   int size;
   bool critical; //controle para área crítica para substrituir mutex
public:
   SharedArray(int n, bool use) : size(n), index(0), critical(use) {
      array = new char[size];
      std::fill(array, array+size, '-');
   }
   ~SharedArray() {
      delete[] array;
   }
   void addChar(char c) {
      bool operation = false;
      if (critical) { 
         #pragma omp critical
         {
            operation = true;
         } 
      } else {
            operation = true;
      }

      if(operation){
         array[index] = c;
         spendSomeTime();
         index++;
      }
   }
    void do_operations(char c){
       
    }
    int countOccurrences(char c) {
        return std::count(array, array+size, c);
    }
    std::string toString() {
        return std::string(array, size);
    }
private:
   void spendSomeTime() {
      for (int i = 0; i < 10000; i++) {
         for (int j = 0; j < 100; j++) {
            
         }
      }
   }
};


class ArrayFiller {
private:
   static const int nThreads = 3;
   static const int nTimes = 20;
   SharedArray* array;

   omp_sched_t schedule_type;
   bool use_defined_chunk = true; //Se não for definido o chunk_size será = nTimes


   std::string schedule_types_strings[4] = { 
      "omp_sched_static", 
      "omp_sched_dynamic", 
      "omp_sched_guided", 
      "omp_sched_auto" 
   }; //Definição dos tipos de agendamento
public:
   ArrayFiller(bool critical, omp_sched_t schedule) : schedule_type(schedule) {
      array = new SharedArray(nThreads * nTimes, critical);
   }
   ArrayFiller(bool critical, omp_sched_t schedule, bool use_chunk) : schedule_type(schedule), use_defined_chunk(use_chunk) {
      array = new SharedArray(nThreads * nTimes, critical);
   }
     void fillArrayConcurrently() {
      
      int chunk_size = use_defined_chunk ? nTimes : 1;
      omp_set_schedule(schedule_type, chunk_size);
      check_schedule();
      #pragma omp parallel num_threads(nThreads)
      {
         run('A' + omp_get_thread_num()); 
      }
   }
   void check_schedule(){
       omp_sched_t schedule_kind;
       int chunck_size;
       omp_get_schedule(&schedule_kind, &chunck_size);
       std::cout << "\tshedule_type: "<< schedule_types_strings[schedule_kind -1] << ", chunk_size: ";
       (!use_defined_chunk && schedule_kind != omp_sched_static) ? std::cout << " (default)" << std::endl : std::cout << std::endl;
   }
   void printStats() {
      std::cout << array->toString() << std::endl;
      for (int i = 0; i < nThreads; ++i)
         std::cout << (char) ('A'+i) << "=" 
                   << array->countOccurrences('A'+i) << " ";
      std::cout << std::endl;
   }
   ~ArrayFiller() {
      delete array;
   }
private:
   void run(char c) {
        #pragma omp for schedule(runtime)
        for (int i = 0; i < nThreads * nTimes; i++) {
            array->addChar(c);
        }
   }
};


int main() {
  
    std::cout << "STATIC" << std::endl;
    std::cout << "Caso 1.0 sem usar o CRITICAL, espera-se erro." << std::endl;
    ArrayFiller m10(false, omp_sched_static);
    m10.fillArrayConcurrently();
    m10.printStats();
    
    std::cout << "" << std::endl;
    std::cout << "Caso 1.1, usando o CRITICAL e sem a especificação do chunk = nTimes" << std::endl;
    ArrayFiller m11(true, omp_sched_static);
    m11.fillArrayConcurrently();
    m11.printStats();
    
    std::cout << "" << std::endl;
    std::cout << "Caso 1.2, usando o CRITICAL e chunk = 1" << std::endl;
    ArrayFiller m12(true, omp_sched_static, false);
    m12.fillArrayConcurrently();
    m12.printStats();
    std::cout << "------------------------------------" << std::endl;
  
    std::cout << "DYNAMIC" << std::endl;
    std::cout << "Caso 2.0 sem usar o CRITICAL, espera-se erro." << std::endl;
    ArrayFiller m20(false, omp_sched_dynamic);
    m20.fillArrayConcurrently();
    m20.printStats();

    std::cout << "" << std::endl;
    std::cout << "Caso 2.1, usando o CRITICAL e sem a especificação do chunk = nTimes" << std::endl;
    ArrayFiller m21(true, omp_sched_dynamic);
    m21.fillArrayConcurrently();
    m21.printStats();

    std::cout << "" << std::endl;
    std::cout << "Caso 2.2, usando o CRITICAL e chunk = 1" << std::endl;
    ArrayFiller m22(true, omp_sched_dynamic, false);
    m22.fillArrayConcurrently();
    m22.printStats();

    std::cout << "------------------------------------" << std::endl;
  
    std::cout << "GUIDED" << std::endl;
    std::cout << "Caso 3.0 sem usar o CRITICAL, espera-se erro." << std::endl;
    ArrayFiller m30(false, omp_sched_guided);
    m30.fillArrayConcurrently();
    m30.printStats();
   

    std::cout << "" << std::endl;
    std::cout << "Caso 3.1, usando o CRITICAL e sem a especificação do chunk = nTimes" << std::endl;
    ArrayFiller m31(true, omp_sched_guided);
    m31.fillArrayConcurrently();
    m31.printStats(); 

    std::cout << "" << std::endl;
    std::cout << "Caso 3.2, usando o CRITICAL e chunk = 1" << std::endl;
    ArrayFiller m32(true, omp_sched_guided, false); 
    m32.fillArrayConcurrently();
    m32.printStats();

    std::cout << "------------------------------------" << std::endl;
    
    std::cout << "AUTO" << std::endl;
    std::cout << "Caso 5.0 sem usar o CRITICAL, espera-se erro." << std::endl;
    ArrayFiller m50(false, omp_sched_auto);
    m50.fillArrayConcurrently();
    m50.printStats();

     std::cout << "" << std::endl;
    std::cout << "Caso 5.1, usando o CRITICAL e sem a especificação do chunk = nTimes" << std::endl;
    ArrayFiller m51(true, omp_sched_auto);
    m51.fillArrayConcurrently();
    m51.printStats();   

    std::cout << "" << std::endl;
    std::cout << "Caso 5.2, usando o CRITICAL e chunk = 1" << std::endl;
    ArrayFiller m52(true, omp_sched_auto, false); 
    m52.fillArrayConcurrently();
    m52.printStats();
}
