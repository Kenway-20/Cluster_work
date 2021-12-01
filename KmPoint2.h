#include "KmLib2.h"

template<typename Real = double, int Dim2 = 128 >
struct KM_API KmPoint2{
        public:
        typedef KmPoint2<Real, Dim2> Self;

        KmPoint2(){
            for(int i = 0; i < Dim2; ++i){
                x[i] = 0;
            }
            gid = 0;
        }

        KmPoint2(Real (&x)[Dim2], int gid = -1){
            for(int i = 0; i < Dim2; ++i){
                this->x[i] = x[i];
            }
            this->gid = gid;
        }

        KmPoint2(const Self &other){
            for(int i = 0; i < Dim2; ++i){
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
        Real x[Dim2];
        int gid;
};

template<class Real, int Dim2>
ostream& operator<<(ostream &out, KmPoint2<Real, Dim2> &other){
    out<<other[0];
    for(int i = 1; i < Dim2; ++i)
        out<<" "<<other[i];
    out<<" "<<other.id();
    return out;
}
