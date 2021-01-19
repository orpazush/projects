/*******************************************************************************
 * 					written by : Orpaz Houta							       *
 * 					review : chanan        						               *
 * 					Last update : 3.8.20								       *
 ******************************************************************************/
#include <stdio.h>  /* printf */
#include <malloc.h> /* malloc */ 

#define NEW(type)   (malloc(sizeof(type)))


/*--------------------Typedef & Structs (Virtual Tables)----------------------*/
typedef void (*v_dtor_t)(void *const this);
typedef void (*v_display_t)(void *const this);
typedef void(*v_wash_t)(void *const this, int minutes);


/* optimization - Taxi & specialTaxi has the same 
   struct as Public, so there is no need to create another type */
typedef struct VTLPublicTransport 
{
    v_dtor_t m_dtor;
    v_display_t m_display;
} VTLPublicTransport;

typedef struct VTLMinibus
{
    v_dtor_t m_dtor;
    v_display_t m_display;
    v_wash_t m_wash;
}VTLMinibus;

/*-------------------------------Structs (Classes)----------------------------*/
typedef struct PublicTransport
{
    const VTLPublicTransport *pvt;
    int m_license_plate;
}PublicTransport;

typedef struct Minibus
{
    PublicTransport m_transport;
    int m_numSeats;
}Minibus;

typedef struct Taxi
{
    PublicTransport m_transport;
}Taxi;

typedef struct SpecialTaxi
{
    Taxi m_taxi;
}SpecialTaxi;

/* advanced */
typedef struct PublicConvoy
{
    PublicTransport m_transport;
    PublicTransport *m_pt1;
    PublicTransport *m_pt2;
    Minibus m_m;
    Taxi m_t;
} PublicConvoy;

/*---------------------------Methods-like Declaration-------------------------*/
/*--------------------------Methods-like PublicTransport----------------------*/
void CtorPublicTransport(PublicTransport *const this);
void VDtorPublicTransport(PublicTransport *const this);
void CCtorPublicTransport(PublicTransport *const this, 
                          const PublicTransport *other);
void VdisplayPublicTransport(PublicTransport *const this);
void print_countPublicTransport(void);
int get_IDPublicTransport(void *const this);

/*------------------------------Methods-like Minibus--------------------------*/
void CtorMinibus(Minibus *const this);
void VDtorMinibus(Minibus *const this);
void CCtorMinibus(Minibus *const this, const Minibus *other);
void VdisplayMinibus(Minibus *const this);
void VwashMinibus(Minibus *const this, int minutes);

/*--------------------------------Methods-like Taxi---------------------------*/
void CtorTaxi(Taxi *const this);
void VDtorTaxi(Taxi *const this);
void CCtorTaxi(Taxi *const this, const Taxi *other);
void VdisplayTaxi(Taxi *const this);

/*----------------------------Methods-like SpecialTaxi------------------------*/
void CtorSpecialTaxi(SpecialTaxi *const this);
void VDtorSpecialTaxi(SpecialTaxi *const this);
void CCtorSpecialTaxi(SpecialTaxi *const this, const SpecialTaxi *other);
void VdisplaySpecialTaxi(SpecialTaxi *const this);

/*----------------------------Methods-like PublicConvoy-----------------------*/
void CtorPublicConvoy(PublicConvoy *const this);
void VDtorPublicConvoy(PublicConvoy *const this);
void CCtorPublicConvoy(PublicConvoy *const this, const PublicConvoy *other);
void VdisplayPublicConvoy(PublicConvoy *const this);

/*-------------------------------Global Functions-----------------------------*/
void Print_InfoPublicTransport(PublicTransport *const transport);
void Print_InfoMinibus(Minibus *const minibus);
PublicTransport Print_InfoInt(int i);
void taxi_display(Taxi s);

/*-------------------------------Static Variables-----------------------------*/
static int s_count = 0;

static const VTLPublicTransport VPublicTransport = {
                                (v_dtor_t)&VDtorPublicTransport,
                                (v_display_t)&VdisplayPublicTransport};

static const VTLMinibus VMinibus = {(v_dtor_t)&VDtorMinibus, 
                                    (v_display_t)&VdisplayMinibus,
                                    (v_wash_t)&VwashMinibus};

static const VTLPublicTransport VTaxi = {(v_dtor_t)&VDtorTaxi, 
                                         (v_display_t)&VdisplayTaxi};

static const VTLPublicTransport VPublicConvoy = {(v_dtor_t)&VDtorPublicConvoy, 
                                            (v_display_t)&VdisplayPublicConvoy};

static const VTLPublicTransport VSpecialTaxi = {(v_dtor_t)&VDtorSpecialTaxi, 
                                            (v_display_t)&VdisplaySpecialTaxi};


/*---------------------------Methods-like Definitions-------------------------*/

/*--------------------------Methods-like PublicTransport----------------------*/
void CtorPublicTransport(PublicTransport *const this)
{
    this->pvt = &VPublicTransport;
    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

void VDtorPublicTransport(PublicTransport *const this)
{
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
    --s_count;
}

void CCtorPublicTransport(PublicTransport *const this, 
                          const PublicTransport *other)
{
    this->pvt = &VPublicTransport;
    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void VdisplayPublicTransport(PublicTransport *const this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

void print_countPublicTransport(void)
{
    printf("s_count: %d\n", s_count);
}

int get_IDPublicTransport(void *const this)
{
    PublicTransport *ptransport = (PublicTransport *)this;

    return ptransport->m_license_plate;
}

/*------------------------------Methods-like Minibus--------------------------*/
void CtorMinibus(Minibus *const this)
{
    CtorPublicTransport(&this->m_transport);
    this->m_transport.pvt = (VTLPublicTransport *)&VMinibus;
    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void CCtorMinibus(Minibus *const this, const Minibus *other)
{
    CCtorPublicTransport(&this->m_transport, &other->m_transport);
    this->m_transport.pvt = (VTLPublicTransport *)&VMinibus;
    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void VDtorMinibus(Minibus *const this)
{
    printf("Minibus::Dtor()\n");
    VDtorPublicTransport(&this->m_transport);
}

void VdisplayMinibus(Minibus *const this)
{
    printf("Minibus::display() ID:%d num seats:%d\n",
           get_IDPublicTransport(this), this->m_numSeats);
}

void VwashMinibus(Minibus *const this, int minutes)
{
    printf("Minibus::wash(""%d"") ID:%d\n", minutes, 
           get_IDPublicTransport(this));
}

/*--------------------------------Methods-like Taxi---------------------------*/
void CtorTaxi(Taxi *const this)
{
    CtorPublicTransport(&this->m_transport);
    this->m_transport.pvt = &VTaxi;
    printf("Taxi::Ctor()\n");
}

void CCtorTaxi(Taxi *const this, const Taxi *other)
{
    CCtorPublicTransport(&this->m_transport, &other->m_transport);
    this->m_transport.pvt = &VTaxi;
    printf("Taxi::CCtor()\n");
}

void VDtorTaxi(Taxi *const this)
{
    printf("Taxi::Dtor()\n");
    VDtorPublicTransport(&this->m_transport);
}

void VdisplayTaxi(Taxi *const this)
{
    printf("Taxi::display() ID:%d\n", 
           get_IDPublicTransport(&this->m_transport));
}

/*----------------------------Methods-like SpecialTaxi------------------------*/
void CtorSpecialTaxi(SpecialTaxi *const this)
{
    CtorTaxi(&this->m_taxi);
    this->m_taxi.m_transport.pvt = &VSpecialTaxi;
    printf("SpecialTaxi::Ctor()\n");
}

void CCtorSpecialTaxi(SpecialTaxi *const this, const SpecialTaxi *other)
{
    CCtorTaxi(&this->m_taxi, &other->m_taxi);
    this->m_taxi.m_transport.pvt = &VSpecialTaxi;
    printf("SpecialTaxi::CCtor()\n");
}

void VDtorSpecialTaxi(SpecialTaxi *const this)
{
    printf("SpecialTaxi::Dtor()\n");
    VDtorTaxi(&this->m_taxi);
}

void VdisplaySpecialTaxi(SpecialTaxi *const this)
{
    printf("Taxi::display() ID:%d\n", get_IDPublicTransport(&this->m_taxi.m_transport));
}

/*------------------------------Global DeFinitions----------------------------*/
void Print_InfoPublicTransport(PublicTransport *const transport)
{
    transport->pvt->m_display(transport);
}

void Print_InfoMinibus(Minibus *const minibus)
{
    const VTLMinibus *VTL = (const VTLMinibus *)minibus->m_transport.pvt;
    VTL->m_wash(minibus, 3);
}

PublicTransport Print_InfoInt(int i)
{
    PublicTransport tempPT;
    Minibus minibus;
    CtorMinibus(&minibus);
    printf("print_info(int i)\n");
    VdisplayMinibus(&minibus);
    CCtorPublicTransport(&tempPT, &minibus.m_transport);
    VDtorMinibus(&minibus);

    return tempPT;
}

void taxi_display(Taxi s)
{
    VdisplayTaxi(&s);
    VDtorTaxi(&s);
}


/*----------------------------------Advanced----------------------------------*/
/*
void CtorPublicConvoy(PublicConvoy *const this)
{
    CtorPublicTransport(&this->m_transport);
    this->m_transport.pvt = &VPublicConvoy;
    this->m_pt1 = NEW(Minibus);
    this->m_pt2 = NEW(Taxi);
    printf("PublicConvoy::Ctor()\n");
}

void CCtorPublicConvoy(PublicConvoy *const this, const PublicConvoy *other)
{
    CCtorPublicTransport(&this->m_transport, &other->m_transport);
    this->m_transport.pvt = &VPublicConvoy;
    this->m_pt1 = NEW(Minibus);
    *this->m_pt1 = *other->m_pt1;
    this->m_pt2 = NEW(Taxi);
    *this->m_pt2 = *other->m_pt2;
    this->m_m = other->m_m;
    this->m_t = other->m_t;

    printf("PublicConvoy::CCtor()\n");
}

void VDtorPublicConvoy(PublicConvoy *const this)
{
    free(this->m_pt1);
    this->m_pt1 = NULL;
    free(this->m_pt2);
    this->m_pt2 = NULL;
    printf("PublicConvoy::Dtor()\n");
    VDtorPublicTransport(&this->m_transport);
}

void VdisplayPublicConvoy(PublicConvoy *const this)
{
    printf("PublicConvoy::display() ID:%d\n",
           get_IDPublicTransport(&this->m_transport));
}
*/
/*----------------------------------------------------------------------------*/

int main()
{
    int i;
    PublicTransport tempPT;
    Minibus tempMB;
    Taxi tempTaxi;
    Minibus m;
    Minibus m2;
    PublicTransport *array[3];
    PublicTransport arr2[3];
    Minibus arr3[4];
    Taxi *arr4;
    SpecialTaxi st;

    CtorMinibus(&m);

    Print_InfoMinibus(&m);

    tempPT = Print_InfoInt(3);
    VdisplayPublicTransport(&tempPT);
    VDtorPublicTransport(&tempPT);

    array[0] = NEW(Minibus);
    CtorMinibus((Minibus *)array[0]);
    array[1] = NEW(Taxi);
    CtorTaxi((Taxi *)array[1]);
    array[2] = NEW(Minibus);
    CtorMinibus((Minibus *)array[2]);

    for (i = 0; i < 3; ++i)
    {
        array[i]->pvt->m_display(array[i]);
    }

    for (i = 0; i < 3; ++i)
    {
        array[i]->pvt->m_dtor(array[i]);
        free(array[i]);
    }

    CtorMinibus(&tempMB);
    CCtorPublicTransport(arr2, (PublicTransport *)&tempMB);
    VDtorMinibus(&tempMB);
    CtorTaxi(&tempTaxi);
    CCtorPublicTransport((arr2 + 1), (PublicTransport *)&tempTaxi);
    VDtorTaxi(&tempTaxi);
    CtorPublicTransport(arr2 + 2);

    for (i = 0; i < 3; ++i)
    {
        VdisplayPublicTransport(&arr2[i]);
    }

    Print_InfoPublicTransport(arr2);
    print_countPublicTransport();
    CtorMinibus(&m2);
    print_countPublicTransport();

    for (i = 0; i < 4; ++i)
    {
        CtorMinibus(arr3 + i);
    }

    for (i = 0; i < 4; ++i)
    {
        CtorTaxi(arr4 + i);
    }

    for (i = 3; 0 <= i; --i)
    {
        arr4[i].m_transport.pvt->m_dtor(arr4 + i);
    }
    free(arr4);

    printf("%d\n", ((1 > 2) ? 1 : 2));
    printf("%d\n", ((1 > (int)2.0) ? 1 : (int)2.0));

    CtorSpecialTaxi(&st);

    CCtorTaxi(&tempTaxi, (Taxi *)&st);
    taxi_display(tempTaxi);

    /*
    *PublicConvoy *ts1 = new PublicConvoy();
    PublicConvoy *ts2 = new PublicConvoy(*ts1);
    ts1->display();
    ts2->display();
    delete ts1;
    ts2->display(); // this crashes. fix the bug!
    delete ts2;*
*/

    VDtorSpecialTaxi(&st);

    for (i = 3; 0 <= i; --i)
    {
        VDtorMinibus(arr3 + i);
    }
    VDtorMinibus(&m2);
    for (i = 2; 0 <= i; --i)
    {
        VDtorPublicTransport(arr2 + i);
    }

    VDtorMinibus(&m);

    return 0;
}