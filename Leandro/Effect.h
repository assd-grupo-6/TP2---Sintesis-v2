#pragma once

#define AVERAGE_SIZE	50

typedef void effectCallback(
	void* soundBuffer,
	const unsigned int maxSoundBufferSize,
	const int sampleRate
);

typedef enum {E_PLAIN, E_ECO, E_LOWPASS}mode_t;

class Effect
{
public:
	// Effect parameters here

	Effect();
	~Effect();
	virtual effectCallback callback;
protected:
	unsigned int getBufferSize(float* buffer); //Da el tama�o del buffer hasta el elemento que contenga INFINITY
	unsigned int copyBuffer2in(float* buffer, float* in); //Copia el array Buffer al array in, y devuelve el tama�o del buffer hasta el elemento INFINITY
	unsigned int setBufferCrap2zero(float* buffer, unsigned int maxBufferSize); //Setea todo la mierda del buffer en 0, y devuelve el tama�o efectivo del buffer
	float getAverage();
	void setArray2zero(float* arr, unsigned int size);
	void pushBackandPop(float element);
	bool isEffectFinished();
	void restartAverage();
	float average[AVERAGE_SIZE];
	bool avgFull;
	unsigned int avgPtr;
};

class reverbEffect : public Effect
{
public:
	reverbEffect(mode_t mode = E_PLAIN, float delay = 0.5, float att = 0.5);  //Modo tipo plano, Eco, o lowpass. Tiempo de delay en segundos, attenuacion. (Valores sugeridos (E_PLAIN,0.5,0.5))
	~reverbEffect();
	void callback(void* soundBuffer, const unsigned int maxSoundBufferSize, const int sampleRate = 44e3);
protected:
	short int mode;
	float delay;
	float a;
	float* in;
};

class flangerEffect : public Effect {
public:
	flangerEffect(float fo = 0.5, float Mw = 5, float Mo = 1e-3, float g_fb =0.3, float g_ff = 0.9, const int sampleRate = 44e3);	// Frecuencia del LFO fo. (valores sugeridos (0.5,1e-3,5,0.3,0.9,sampleRate))
	~flangerEffect();
	void callback(void* soundBuffer, const unsigned int maxSoundBufferSize, const int sampleRate = 44e3);
protected:
	float fo;
	float Mo;
	float Mw;
	float g_fb;
	float g_ff;
	float* in;
private:
	float linearInterpolation(float num, float * in);
};

class vibratoEffect : public Effect {
public:
	vibratoEffect(float W = 1e3, float fo = 5, float M_avg = 10, const int sampleRate = 44e3); // W para la cual queremos que esto funcione, frecuencia del LFO fo, Distancia average (Valores sugeridos (1e3,5,0.5))
	~vibratoEffect();
	void callback(void* soundBuffer, const unsigned int maxSoundBufferSize, const int sampleRate = 44e3);
protected:
	float W;
	float fo;
	float* in;
	float* comodin;
	float M_avg;
private:
	float linearInterpolation(float num);
};

/*
class wahwahEffect : public Effect {
public:
	wahwahEffect(float damping, float width, float min_cutoff, float max_cutoff);
	effectCallback callback;
protected:
	float damping;
	float width;
	float min_cutoff;
	float max_cutoff;
};*/
