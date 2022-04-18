typedef enum
{
    Bass_Shelf,
    Treble_Shelf
} Shelf;
void get_IIR(float* a, float* b, float gain_db, float gain_lin, float inv_slope,
    float K, Shelf filter);