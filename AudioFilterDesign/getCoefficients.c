#include<math.h>
#include"getCoefficients.h"
void get_IIR(float* a, float* b, float gain_db, float gain_lin, float inv_slope,
    float K, Shelf filter) {
    /* --------------------
    -------BASE BOOST------
    -------------------- */
    if ((gain_db > 0) && filter == Bass_Shelf) {
        b[0] = (1 + sqrtf(gain_lin) * inv_slope * K + gain_lin * K*K) / (1 + inv_slope * K + K*K);
        b[1] = (2 * (gain_lin * K*K - 1)) / (1 + inv_slope * K + K*K);
        b[2] = (1 - sqrtf(gain_lin) * inv_slope * K + gain_lin * K*K) / (1 + inv_slope * K + K*K);
        a[1] = (2 * (K*K - 1)) / (1 + inv_slope * K + K*K);
        a[2] = (1 - inv_slope * K + K*K) / (1 + inv_slope * K + K*K);
    }
    /* --------------------
    -------BASE CUT------
    -------------------- */
    else if ((gain_db < 0) && filter == Bass_Shelf) {

        b[0] = (1 + inv_slope * K + K*K) / (1 + inv_slope * sqrtf(gain_lin) * K + gain_lin * K*K);
        b[1] = (2 * (K*K - 1)) / (1 + inv_slope * sqrtf(gain_lin) * K + gain_lin * K*K);
        b[2] = (1 - inv_slope * K + K*K) / (1 + inv_slope * sqrtf(gain_lin) * K + gain_lin * K*K);
        a[1] = (2 * (gain_lin * K*K - 1)) / (1 + inv_slope * sqrtf(gain_lin) * K + gain_lin * K*K);
        a[2] = (1 - inv_slope * sqrtf(gain_lin) * K + gain_lin * K*K) / (1 + inv_slope * sqrtf(gain_lin) * K + gain_lin * K*K);
    }
    /* --------------------
    ------TREBLE BOOST-----
    -------------------- */
    else if ((gain_db > 0) && filter == Treble_Shelf) {
        b[0] = (gain_lin + inv_slope * sqrtf(gain_lin) * K + K*K) / (1 + inv_slope * K + K*K);
        b[1] = (2 * (K*K - gain_lin)) / (1 + inv_slope * K + K*K);
        b[2] = (gain_lin - inv_slope * sqrtf(gain_lin) * K + K*K) / (1 + inv_slope * K + K*K);
        a[1] = (2 * (K*K - 1)) / (1 + inv_slope * K + K*K);
        a[2] = (1 - inv_slope * K + K*K) / (1 + inv_slope * K + K*K);
    }
    /* --------------------
        ------TREBLE CUT-----
        -------------------- */
    else if((gain_db < 0) && filter == Treble_Shelf) {
        b[0] = (1 + inv_slope * K + K*K) / (gain_lin + inv_slope * sqrtf(gain_lin) * K + K*K);
        b[1] = (2 * (K*K - 1)) / (gain_lin + inv_slope * sqrtf(gain_lin) * K + K*K);
        b[2] = (1 - inv_slope * K + K*K) / (gain_lin + inv_slope * sqrtf(gain_lin) * K + K*K);
        a[1] = (2 * ((K*K) / gain_lin - 1)) / (1 + inv_slope / sqrtf(gain_lin) * K + (K*K) / gain_lin);
        a[2] = (1 - inv_slope / sqrtf(gain_lin) * K + (K*K) / gain_lin) / (1 + inv_slope / sqrtf(gain_lin) * K + (K*K) / gain_lin);
    }
}