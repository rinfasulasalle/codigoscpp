#include "iostream"
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>
using namespace std;

// VARIABLES A UTILIZAR
#define CANTIDAD_PRODUCTORES 5 /* CANTIDAD productores = CANTIDAD consumidores */
condition_variable condicion;
mutex _mutex;
deque<int> buffer;
//tamaño del bufer
const unsigned int tamanioMaxBuffer = 10;

//clase productor
class Productor{
	private:
		thread t;
		int k;
		void produce(){
			//numero maximo que produciran los productores e ira disminuyendo hasta 0
			int val=26;	//26 letras del abecedario
			while (val){
				unique_lock<mutex> locker(_mutex);
				condicion.wait(locker, [](){ return buffer.size() < tamanioMaxBuffer; });
				//agregamos la produccion al buffer
				buffer.push_back(val);
				cout <<"p"<< k << ": El Productor nmro " << k <<" produce: "<< val << endl;
				val--;
				locker.unlock();
				//notificamos al otro hilo que puede continuar
				condicion.notify_one();
			}
		}
	public:
		Productor(int id) {
			k = id;
			t = thread(&Productor::produce, this);
		}
		void join_thread(){
			t.join();
		}
};

//clase consumidor
class Consumidor {
	private:
		thread t;
		int k;
		void consume() {
			//los consumidores siempre consumen
			while (true){
				unique_lock<mutex> locker(_mutex);
				condicion.wait(locker, [](){ return buffer.size() > 0; });
				// val ultimo valor buffer
				int val = buffer.back();
				// consumidor consume el ultimo elemento
				buffer.pop_back();
				cout <<"c"<< k << ": L Consumidor nmro "<< k <<" consume:" << val << endl;
				locker.unlock();
				//notificamos a los otros hilos que pueden continuar
				condicion.notify_one();
			}
		}
	public:
		Consumidor(int id) {
			k = id;
			t = thread(&Consumidor::consume, this);
		}
		void join_thread(){
			t.join();
		}
};

int main(){
	//creo una lista de consumidores y productores
	Productor* productores[CANTIDAD_PRODUCTORES]; // listas tipo Productor puntero
	Consumidor* consumidores[CANTIDAD_PRODUCTORES];
	

	//inicializamos los productores y consumidores
	for (int i = 0; i < CANTIDAD_PRODUCTORES; i++)	{		
		productores[i] = new Productor(i);
		consumidores[i] = new Consumidor(i); 
	}

	//comenzamos a producir y consumir
	for (int i=0; i < CANTIDAD_PRODUCTORES; i++)	{
		productores[i]->join_thread();
		consumidores[i]->join_thread();
	}
	cout<<"Fin"<<endl;
	return 0;
}