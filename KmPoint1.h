//
// Created by LENOVO on 2021/11/25.
//

#ifndef TEST_CLUST_KMPOINT1_H
#define TEST_CLUST_KMPOINT1_H
#ifndef KMPOINT1_H
#define KMPOINT1_H
#include "KmLib1.h"

template<typename Real = double, int Dim1 = 128 >
struct KM_API KmPoint1{
        public:
        typedef KmPoint1<Real, Dim1> Self;

        KmPoint1(){
            for(int i = 0; i < Dim1; ++i){
                x[i] = 0;
            }
            gid = 0;
        }

        KmPoint1(Real (&x)[Dim1], int gid = -1){
            for(int i = 0; i < Dim1; ++i){
                this->x[i] = x[i];
            }
            this->gid = gid;
        }

        KmPoint1(const Self &other){
            for(int i = 0; i < Dim1; ++i){
                x[i] = other[i];
            }
            gid = other.gid;
        }

        Real &operator[](int idx){	return x[idx];	}
        const Real &operator[](int idx) const {	return x[idx]; }

        int id(){ return gid; }
        void setId(int id){
            gid = id;
        }

        Real get(int idx){ return x[idx]; }
        private:
        Real x[Dim1];
        int gid;
};

template<class Real, int Dim1>
ostream& operator<<(ostream &out, KmPoint1<Real, Dim1> &other){
    out<<other[0];
    for(int i = 1; i < Dim1; ++i)
        out<<" "<<other[i];
    out<<" "<<other.id();
    return out;
}

#endif
#endif //TEST_CLUST_KMPOINT1_H
