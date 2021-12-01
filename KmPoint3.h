#include "KmLib3.h"

template<typename Real = double, int Dim3 = 178>
struct KM_API KmPoint3{
        public:
        typedef KmPoint3<Real, Dim3> Self;

        KmPoint3(){
            for(int i = 0; i < Dim3; ++i){
                x[i] = 0;
            }
            gid = 0;
        }

        KmPoint3(Real (&x)[Dim3], int gid = -1){
            for(int i = 0; i < Dim3; ++i){
                this->x[i] = x[i];
            }
            this->gid = gid;
        }

        KmPoint3(const Self &other){
            for(int i = 0; i < Dim3; ++i){
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
        Real x[Dim3];
        int gid;
};

template<class Real, int Dim2>
ostream& operator<<(ostream &out, KmPoint3<Real, Dim2> &other){
    out<<other[0];
    for(int i = 1; i < Dim2; ++i)
        out<<" "<<other[i];
    out<<" "<<other.id();
    return out;
}
