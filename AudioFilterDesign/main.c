
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"getCoefficients.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
static void printUsage(void)
{
    printf("  Design a digital IIR filter for audio signal processing.\n");
    printf("  Usage: AudioFiterDesign Fs Fc gain slope type [fx] [Q value]\n");
    printf("  fx=1 will return fixed point coefficients of IIR filter and the default value of Q is 15\n");
    printf("  type of filter: \n");
    printf("  bass_Shelf =%d\n", Bass_Shelf);
    printf("  Treble_Shelf =%d\n", Treble_Shelf);
    exit(0);
}
static void printResult(float* a, float* b) {
    printf("The IIR filter coefficients are: \n");
    for (int i = 0; i < 3; i++)
        printf("a[%d] = %f, ", i, a[i]);
    printf("\n");
    for (int i = 0; i < 3; i++)
        printf("b[%d] = %f, ", i, b[i]);
}

int main(int argc, char* argv[]) {
    float Fs, Fc, gain, slope;
    short fx, Q;
    Shelf type;
    if (argc < 6)
    {
        printf(" Not enough input arguments!\n");
        printUsage();
        return -1;
    }
    printf("argc= %d\n", argc);
    Fs = atof(argv[1]);
    printf("Fs=%f\n", Fs);
    Fc = atof(argv[2]);
    printf("Fs=%f\n", Fc);
    gain = atof(argv[3]);
    printf("gain=%f\n", gain);
    slope = atof(argv[4]);
    printf("slope=%f\n", slope);
    type = atoi(argv[5]);
    printf("type =%d\n", type);
    
    if (argc>6)
    {
        fx = atoi(argv[6]);
    }
    if (argc > 7)
    {
        Q = atoi(argv[7]);
        printf("Q value = %d\n", Q);
    }
    else {
        Q = 15;
        printf("Q value = %d\n",Q);
    }

    float K = tan((M_PI * Fc) / Fs);
    float V0 = pow(10,gain/20); // 10^(gain/20);
    float m = 1 / slope;
    // Invert gain if a cut
    if (V0 < 1) 
        V0=1/V0;
    float a[2];
    a[0] = 1;
    float b[2];
    get_IIR(&a[1],&b, gain, V0, m, K, type);
    printResult(a, b);
    return 0;
}

