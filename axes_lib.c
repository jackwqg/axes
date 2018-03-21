#include <math.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

#define ARR_LEN(array, length) { length =  sizeof(array) / sizeof(array[0]); }

double mcBand[6] = {12890594.86, 8362377.87, 5591021, 3481989.83, 1678043.12, 0};
int llBand[6] = {75, 60, 45, 30, 15, 0};

double mc2LL[6][10] = {
    {1.410526172116255e-008, 8.983055096488720e-006, -1.99398338163310, 2.009824383106796e+002, -1.872403703815547e+002, 91.60875166698430, -23.38765649603339, 2.57121317296198, -0.03801003308653, 1.733798120000000e+007}, 
    {-7.435856389565537e-009, 8.983055097726239e-006, -0.78625201886289, 96.32687599759846, -1.85204757529826, -59.36935905485877, 47.40033549296737, -16.50741931063887, 2.28786674699375, 1.026014486000000e+007}, 
    {-3.030883460898826e-008, 8.983055099835780e-006, 0.30071316287616, 59.74293618442277, 7.35798407487100, -25.38371002664745, 13.45380521110908, -3.29883767235584, 0.32710905363475, 6.856817370000000e+006}, 
    {-1.981981304930552e-008, 8.983055099779535e-006, 0.03278182852591, 40.31678527705744, 0.65659298677277, -4.44255534477492, 0.85341911805263, 0.12923347998204, -0.04625736007561, 4.482777060000000e+006}, 
    {3.091913710684370e-009, 8.983055096812155e-006, 0.00006995724062, 23.10934304144901, -0.00023663490511, -0.63218178102420, -0.00663494467273, 0.03430082397953, -0.00466043876332, 2.555164400000000e+006}, 
    {2.890871144776878e-009, 8.983055095805407e-006, -0.00000003068298, 7.47137025468032, -0.00000353937994, -0.02145144861037, -0.00001234426596, 0.00010322952773, -0.00000323890364, 8.260885000000000e+005}
};

double ll2Mc[6][10] = {
    {-0.00157021024440, 1.113207020616939e+005, 1.704480524535203e+015, -1.033898737604234e+016, 2.611266785660388e+016, -3.514966917665370e+016, 2.659570071840392e+016, -1.072501245418824e+016, 1.800819912950474e+015, 82.5}, 
    {8.277824516172526e-004, 1.113207020463578e+005, 6.477955746671608e+008, -4.082003173641316e+009, 1.077490566351142e+010, -1.517187553151559e+010, 1.205306533862167e+010, -5.124939663577472e+009, 9.133119359512032e+008, 67.5}, 
    {0.00337398766765, 1.113207020202162e+005, 4.481351045890365e+006, -2.339375119931662e+007, 7.968221547186455e+007, -1.159649932797253e+008, 9.723671115602145e+007, -4.366194633752821e+007, 8.477230501135234e+006, 52.5}, 
    {0.00220636496208, 1.113207020209128e+005, 5.175186112841131e+004, 3.796837749470245e+006, 9.920137397791013e+005, -1.221952217112870e+006, 1.340652697009075e+006, -6.209436990984312e+005, 1.444169293806241e+005, 37.5}, 
    {-3.441963504368392e-004, 1.113207020576856e+005, 2.782353980772752e+002, 2.485758690035394e+006, 6.070750963243378e+003, 5.482118345352118e+004, 9.540606633304236e+003, -2.710553267466450e+003, 1.405483844121726e+003, 22.5}, 
    {-3.218135878613132e-004, 1.113207020701615e+005, 0.00369383431289, 8.237256402795718e+005, 0.46104986909093, 2.351343141331292e+003, 1.58060784298199, 8.77738589078284, 0.37238884252424, 7.45}
};

double ee = 0.00669342162296594323;
double a = 6378245.0;
double pi = 3.1415926535897932384626;

typedef struct {
    double lat;
    double lng;
} struct_coor;

double transformLati(double lat, double lng) {
    double ret = 0.0;
    ret = -100.0 + 2 * lng + 3.0 * lat + 0.2 * lat * lat + 0.1 * lng * lat + 0.2 * sqrt(fabs(lng));
    ret += (20.0 * sin(6.0 * lng * pi) + 20.0 * sin(2.0 * lng * pi)) * 2.0 / 3.0;
    ret += (20.0 * sin(lat * pi) + 40.0 * sin(lat / 3.0 * pi)) * 2.0 / 3.0;
    ret += (160.0 * sin(lat / 12.0 * pi) + 320 * sin(lat * pi / 30.0)) * 2.0 / 3.0;

    return ret;
}

double transformLong(double lat, double lng) {
        double ret = 0.0;
        ret = 300.0 + lng + 2.0 * lat + 0.1 * lng * lng + 0.1 * lng * lat + 0.1 * sqrt(fabs(lng));
        ret += (20.0 * sin(6.0 * lng * pi) + 20.0 * sin(2.0 * lng * pi)) * 2.0 / 3.0;
        ret += (20.0 * sin(lng * pi) + 40.0 * sin(lng / 3.0 * pi)) * 2.0 / 3.0;
        ret += (150.0 * sin(lng / 12.0 * pi) + 300.0 * sin(lng / 30.0 * pi)) * 2.0 / 3.0;

        return ret;
}

struct_coor axes_wgs84togcj02(double lat, double lng) {

    struct_coor coor ;
    double tmpLat = 0.0;
    double tmpLng = 0.0;
    double dLat = 0.0;
    double dLng = 0.0;
    double radlat = 0.0;
    double magic = 0.0;
    double sqrtMagic = 0.0;
    double mglat = 0.0;
    double mglng = 0.0;

    tmpLat = lat - 35.0;
    tmpLng = lng - 105.0;

    dLat = transformLati(tmpLat, tmpLng);
    dLng = transformLong(tmpLat, tmpLng);

    radlat = lat / 180.0 * pi;
    magic = sin(radlat);
    magic = 1 - ee * magic * magic;
    sqrtMagic = sqrt(magic);
    dLat = (dLat * 180.0) / ((a * (1 - ee)) / (magic * sqrtMagic) * pi);
    dLng = (dLng * 180.0) / (a / sqrtMagic * cos(radlat) * pi);
    mglat = lat + dLat;
    mglng = lng + dLng;
    coor.lat = mglat;
    coor.lng = mglng;

    return coor;
}

struct_coor axes_gcj02tobd09(double lat, double lng) {
    struct_coor coor;
    double x_pi = pi * 3000.0 / 180.0;
    double z = sqrt(lng * lng + lat * lat) + 0.00002 * sin(lat * x_pi);
    double theater = atan2(lat, lng) + 0.000003 * cos(lng * x_pi);
    double bdLat = z * sin(theater) + 0.006;
    double bdLng = z * cos(theater) + 0.0065;
    
    coor.lat = bdLat;
    coor.lng = bdLng;

    return coor;
}


double getLoop(double lng, double a, double b) {
    while (lng > b) {
        lng -= b - a;
    }

    while (lng < a) {
        lng += b - a;
    }

    return lng;
}

double getRange(double lat, double a, double b) {
    lat = max(lat, a);
    lat = min(lat, b);

    return lat;
}

struct_coor convertor(double lng, double lat, double *factor) {
    double x = factor[0] + factor[1] * fabs(lng);
    double tmp = fabs(lat) / factor[9];
    
    double y = factor[2] + factor[3] * tmp + factor[4] * pow(tmp, 2) + \
        factor[5] * pow(tmp, 3) + factor[6] * pow(tmp, 4) + \
        factor[7] * pow(tmp, 5) + factor[8] * pow(tmp, 6);

    x *= (x < 0 ? -1 : 1);
    y *= (y < 0 ? -1 : 1);

    struct_coor tmpCoor;
    tmpCoor.lng = x;
    tmpCoor.lat = y;

    return tmpCoor;
}

struct_coor axes_bd09toMc(double lng, double lat) {
    lng = getLoop(lng, -180, 180);
    lat = getRange(lat, -74, 74);

    int llBandLen = 0;
    ARR_LEN(llBand, llBandLen);
    double *pArr = NULL;
    int i = 0;
    for (i=0; i<llBandLen; i++) {
        if (lat >= llBand[i]) {
            pArr = ll2Mc[i];
            break;
        }
    }

    if (pArr) {
        for (i=llBandLen - 1; i>=0; i--) {
            if (lat <= -llBand[i]) {
                pArr = ll2Mc[i];
                break;
            }
        }
    }

    struct_coor coor = convertor(lng, lat, pArr);
    
    return coor;
}


