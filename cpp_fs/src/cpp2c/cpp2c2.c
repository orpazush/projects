/*******************************************************************************
 * 					written by : Orpaz Houta							       *
 * 					review :         						               *
 * 					Last update : 3.8.20								       *
 ******************************************************************************/
#include <stdio.h>  /* printf */
#include <malloc.h> /* malloc */

#define NEW(type)   (malloc(sizeof(type)))

typedef void(*v_dtor_t)(void *const this);
typedef void(*v_display_t)(void *const this);
typedef void(*v_wash_t)(void *const this, int minutes);

/*------------------------------ PublicTransport -----------------------------*/
typedef struct VTLPublicTransport
{
    v_dtor_t m_dtor;
    v_display_t m_display;
}VTLPublicTransport;

typedef struct PublicTransport
{
    const VTLPublicTransport *m_pvt;
    int m_license_plate;
}PublicTransport;

void VDtorPublicTransport(PublicTransport *const this);
void VdisplayPublicTransport(PublicTransport *const this);

static const VTLPublicTransport VPublicTransport = {
        (v_dtor_t)&VDtorPublicTransport,
        (v_display_t)&VdisplayPublicTransport};
static int s_count = 0;

void CtorPublicTransport(PublicTransport *const this)
{
    this->m_pvt = &VPublicTransport;
    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

void VDtorPublicTransport(PublicTransport *const this)
{
    --s_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void CCtorPublicTransport(PublicTransport *const this, const PublicTransport
*const other)
{
    this->m_pvt = &VPublicTransport;
    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void VdisplayPublicTransport(PublicTransport *const this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

void print_countPublicTransport()
{
    printf("s_count: %d\n", s_count);
}

int get_IDPublicTransport(PublicTransport *const this)
{
    return this->m_license_plate;
}

/*---------------------------------- Minibus ---------------------------------*/
typedef struct Minibus
{
    PublicTransport m_publicTransport;
    int m_numSeats;

}Minibus;

typedef struct VTLMinibus
{
    v_dtor_t m_dtor;
    v_display_t m_display;
    v_wash_t m_wash;
}VTLMinibus;

void VDtorMinibus(Minibus *const this);
void VdisplayMinibus(Minibus *const this);
void VwashMinibus(Minibus *const this, int minutes);

static const VTLMinibus VMinibus = {(v_dtor_t)&VDtorMinibus,
                                    (v_display_t)&VdisplayMinibus,
                                    (v_wash_t)&VwashMinibus};

void CtorMinibus(Minibus *const this)
{
    CtorPublicTransport(&this->m_publicTransport);
    this->m_publicTransport.m_pvt = (VTLPublicTransport *)&VMinibus;
    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void VDtorMinibus(Minibus *const this)
{
    printf("Minibus::Dtor()\n");
    this->m_publicTransport.m_pvt = &VPublicTransport;
    VDtorPublicTransport(&this->m_publicTransport);
}

void CCtorMinibus(Minibus *const this, const Minibus *const other)
{
    CCtorPublicTransport(&this->m_publicTransport, &other->m_publicTransport);
    this->m_publicTransport.m_pvt = (VTLPublicTransport *)&VMinibus;
    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void VdisplayMinibus(Minibus *const this)
{
    printf("Minibus::display() ID:%d num seats:%d\n",
           get_IDPublicTransport(&this->m_publicTransport), this->m_numSeats);
}

void VwashMinibus(Minibus *const this, int minutes)
{
    printf("Minibus::wash(""%d"") ID:%d\n", minutes,
           get_IDPublicTransport(&this->m_publicTransport));
}

/*------------------------------------ Taxi ----------------------------------*/
/*the vtable is the same as PublicTransport..*/
typedef struct Taxi
{
    PublicTransport m_publicTransport;
}Taxi;

void VDtorTaxi(Taxi *const this);
void VdisplayTaxi(Taxi *const this);

static const VTLPublicTransport VTaxi = {(v_dtor_t)&VDtorTaxi,
                                         (v_display_t)&VdisplayTaxi};


void CtorTaxi(Taxi *const this)
{
    CtorPublicTransport(&this->m_publicTransport);
    this->m_publicTransport.m_pvt = &VTaxi;
    printf("Taxi::Ctor()\n");
}

void VDtorTaxi(Taxi *const this)
{
    printf("Taxi::Dtor()\n");
    this->m_publicTransport.m_pvt = &VPublicTransport;
    VDtorPublicTransport(&this->m_publicTransport);
}

void CCtorTaxi(Taxi *const this, const Taxi *const other)
{
    CCtorPublicTransport(&this->m_publicTransport, &other->m_publicTransport);
    this->m_publicTransport.m_pvt = &VTaxi;
    printf("Taxi::CCtor()\n");
}

void VdisplayTaxi(Taxi *const this)
{
    printf("Taxi::display() ID:%d\n",
           get_IDPublicTransport(&this->m_publicTransport));
}

/*-------------------------------- PublicConvoy ------------------------------*/
/*the vtable is the same as PublicTransport..*/
typedef struct PublicConvoy
{
    PublicTransport m_publicTransport;
    PublicTransport *m_pt1;
    PublicTransport *m_pt2;
    Minibus m_m;
    Taxi m_t;
}PublicConvoy;

void VDtorPublicConvoy(PublicConvoy *const this);
void VdisplayPublicConvoy(PublicConvoy *const this);

static const VTLPublicTransport VPublicConvoy = {(v_dtor_t)&VDtorPublicConvoy,
                                         (v_display_t)&VdisplayPublicConvoy};


void CtorPublicConvoy(PublicConvoy *const this)
{
    CtorPublicTransport(&this->m_publicTransport);
    this->m_publicTransport.m_pvt = &VPublicConvoy;
    this->m_pt1 = NEW(Minibus);
    CtorMinibus((Minibus * const)this->m_pt1);
    this->m_pt2 = NEW(Taxi);
    CtorTaxi((Taxi * const)this->m_pt2);
    CtorMinibus(&this->m_m);
    CtorTaxi(&this->m_t);
}

void VDtorPublicConvoy(PublicConvoy *const this)
{
    this->m_pt1->m_pvt->m_dtor(this->m_pt1);
    free(this->m_pt1);
    this->m_pt2->m_pvt->m_dtor(this->m_pt2);
    free(this->m_pt2);
    VDtorTaxi(&this->m_t);
    VDtorMinibus(&this->m_m);
    this->m_publicTransport.m_pvt = &VPublicTransport;
    VDtorPublicTransport(&this->m_publicTransport);
}

void CCtorPublicConvoy(PublicConvoy *const this, const PublicConvoy *const other)
{
    CtorPublicTransport(&this->m_publicTransport);
    this->m_publicTransport.m_pvt = &VPublicConvoy;
    this->m_pt1 = (PublicTransport *)malloc(sizeof(struct PublicTransport));
    CCtorPublicTransport(this->m_pt1, other->m_pt1);
    this->m_pt2 = (PublicTransport *)malloc(sizeof(struct PublicTransport));
    CCtorPublicTransport(this->m_pt2, other->m_pt2);
    CCtorMinibus(&this->m_m, &other->m_m);
    CCtorTaxi(&this->m_t, &other->m_t);
}

void VdisplayPublicConvoy(PublicConvoy *const this)
{
    this->m_pt1->m_pvt->m_display(this->m_pt1);
    this->m_pt2->m_pvt->m_display(this->m_pt2);
    VdisplayMinibus(&this->m_m);
    VdisplayTaxi(&this->m_t);
}

/*-------------------------------- SpecialTaxi -------------------------------*/
/*the vtable is the same as PublicTransport..*/
typedef struct SpecialTaxi
{
    Taxi m_taxi;
}SpecialTaxi;

void VDtorSpecialTaxi(SpecialTaxi *const this);
void VdisplaySpecialTaxi(SpecialTaxi *const this);

static const VTLPublicTransport VSpecialTaxi = {(v_dtor_t)&VDtorSpecialTaxi,
                                                (v_display_t)&VdisplaySpecialTaxi};

void CtorSpecialTaxi(SpecialTaxi *const this)
{
    CtorTaxi(&this->m_taxi);
    this->m_taxi.m_publicTransport.m_pvt = &VSpecialTaxi;
    printf("SpecialTaxi::Ctor()\n");
}

void VDtorSpecialTaxi(SpecialTaxi *const this)
{
    printf("SpecialTaxi::Dtor()\n");
    this->m_taxi.m_publicTransport.m_pvt = &VTaxi;
    VDtorTaxi(&this->m_taxi);
}

void CCtorSpecialTaxi(SpecialTaxi *const this, const SpecialTaxi *const other)
{
    CCtorTaxi(&this->m_taxi, &other->m_taxi);
    this->m_taxi.m_publicTransport.m_pvt = &VSpecialTaxi;
    printf("SpecialTaxi::CCtor()\n");
}

void VdisplaySpecialTaxi(SpecialTaxi *const this)
{
    printf("SpecialTaxi::display() ID:%d\n",
           get_IDPublicTransport(&this->m_taxi.m_publicTransport));
}

void print_infoPublicTransport(PublicTransport * const a)
{
    a->m_pvt->m_display(a);
}

void print_info()
{
    print_countPublicTransport();
}

void print_infoMinibus(Minibus * const m)
{
    VTLMinibus *pvtMin = (VTLMinibus *)m->m_publicTransport.m_pvt;
    pvtMin->m_wash(m, 3);
}

PublicTransport print_infoi(int i)
{
    PublicTransport toReturn;
    Minibus temp;
    CtorMinibus(&temp);
    printf("print_info(int i)\n");
    VdisplayMinibus(&temp);
    CCtorPublicTransport(&toReturn, &temp.m_publicTransport);
    VDtorMinibus(&temp);

    return toReturn;
}

void taxi_display(Taxi s)
{
    VdisplayTaxi(&s);
    VDtorTaxi(&s);
}


int main()
{
    int i;
    Minibus m;
    Minibus m2;
    PublicTransport tmpPT;
    Minibus tmpMinibus;
    Taxi tmpTaxi;
    SpecialTaxi tmpSpecialTaxi;
    PublicTransport *array[3];
    PublicTransport arr2[3];
    Minibus arr3[4];
    Taxi *arr4;
    SpecialTaxi st;
    PublicConvoy *ts1;
    PublicConvoy *ts2;

    CtorMinibus(&m);
    print_infoMinibus(&m);
    tmpPT = print_infoi(3);
    VdisplayPublicTransport(&tmpPT);
    VDtorPublicTransport(&tmpPT);
    array[0] = NEW(Minibus);
    CtorMinibus((Minibus *)array[0]);
    array[1] = NEW(Taxi);
    CtorTaxi((Taxi *)array[1]);
    array[2] = NEW(Minibus);
    CtorMinibus((Minibus *)array[2]);

    for (i = 0; i < 3; ++i)
    {
        array[i]->m_pvt->m_display(array[i]);
    }
    for (i = 0; i < 3; ++i)
    {
        array[i]->m_pvt->m_dtor(array[i]);
    }

    CtorMinibus(&tmpMinibus);
    CCtorPublicTransport(arr2, &tmpMinibus.m_publicTransport);
    VDtorMinibus(&tmpMinibus);

    CtorTaxi(&tmpTaxi);
    CCtorPublicTransport(arr2 + 1, &tmpTaxi.m_publicTransport);
    VDtorTaxi(&tmpTaxi);

    CtorPublicTransport(arr2 + 2);

    for (i = 0; i < 3; ++i)
    {
        VdisplayPublicTransport(arr2 + i);
    }
    print_countPublicTransport();
    CtorMinibus(&m2);
    print_countPublicTransport();

    for (i = 0; i < 4; ++i)
    {
        CtorMinibus(arr3 + i);
    }

    arr4 = NEW(Taxi[4]);
    for (i = 0; i < 4; ++i)
    {
        CtorTaxi(arr4 + i);
    }

    for (i = 3; 0 <= i; --i)
    {
        arr4[i].m_publicTransport.m_pvt->m_dtor(arr4 + i);
    }
    printf("%d\n", (1 > 2) ? 1 : 2);
    printf("%d\n", (1 > 2.0) ? (int)1 : (int)2.0);

    CtorSpecialTaxi(&st);
    CCtorTaxi(&tmpTaxi, &st.m_taxi);
    taxi_display(tmpTaxi);

    ts1 = NEW(PublicConvoy);
    CtorPublicConvoy(ts1);

    ts2 = NEW(PublicConvoy);
    CCtorPublicConvoy(ts2, ts1);
    ts1->m_publicTransport.m_pvt->m_display(ts1);
    ts2->m_publicTransport.m_pvt->m_display(ts2);

    VDtorPublicConvoy(ts1);
    ts2->m_publicTransport.m_pvt->m_display(ts2);
    VDtorPublicConvoy(ts2);

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