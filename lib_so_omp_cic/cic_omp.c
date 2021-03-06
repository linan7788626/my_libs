#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//--------------------------------------------------------------------
void cal_cic_sdens(float *xp1, float *xp2, int Np, float bsc1, float bsc2, float dsx, int nx, int ny, float *sdens) {

	int i,j;
	int i1,j1,m;
	float xb1,xb2;
	float ww1,ww2,ww3,ww4,wx,wy;
	float ds = 1.0/(dsx*dsx);

#pragma omp parallel num_threads(4)	\
	shared(xp1,xp2,Np,bsc1,bsc2,dsx,nx,ny,sdens,ds) \
	private(m,i1,j1,xb1,xb2,wx,wy,ww1,ww2,ww3,ww4)
	{
	float *sdens_sp;
	sdens_sp = (float *)calloc(nx*ny,sizeof(float));
	#pragma omp for schedule(dynamic,16)

		for(m=0;m<Np;m++) {

			xb1 = (xp1[m]-bsc1)/dsx+(float)nx/2.0;
			xb2 = (xp2[m]-bsc2)/dsx+(float)ny/2.0;

			i1 = (int)xb1;
			j1 = (int)xb2;

			if (i1<0||i1>nx-2||j1<0||j1>ny-2) continue;

			wx = 1.-(xb1-(float)(i1));
			wy = 1.-(xb2-(float)(j1));

			ww1 = wx*wy*ds;
			ww2 = wx*(1.0-wy)*ds;
			ww3 = (1.0-wx)*wy*ds;
			ww4 = (1.0-wx)*(1.0-wy)*ds;


			sdens_sp[i1*nx+j1] += ww1;
			sdens_sp[i1*nx+(j1+1)] += ww2;
			sdens_sp[(i1+1)*nx+j1] += ww3;
			sdens_sp[(i1+1)*nx+(j1+1)] += ww4;
		}
	#pragma omp critical
	{
		for(i=0;i<nx;i++) for(j=0;j<ny;j++) {
			sdens[i*ny+j] += sdens_sp[i*ny+j];
		}
	}
	free(sdens_sp);
	}
}
//--------------------------------------------------------------------
void cal_cic_sdens_single(float *xp1, float *xp2, int Np, float bsc1, float bsc2, float dsx, int nx, int ny, float *sdens) {

	int i1,j1,m;
	float xb1,xb2;
	float ww1,ww2,ww3,ww4,wx,wy;
	float ds = 1.0/(dsx*dsx);

	for(m=0;m<Np;m++) {

		xb1 = (xp1[m]-bsc1)/dsx+(float)nx/2.0-0.5;
		xb2 = (xp2[m]-bsc2)/dsx+(float)ny/2.0-0.5;

		i1 = (int)xb1;
		j1 = (int)xb2;

		if (i1<0||i1>nx-2||j1<0||j1>ny-2) continue;

		wx = 1.-(xb1-(float)(i1));
		wy = 1.-(xb2-(float)(j1));

		ww1 = wx*wy*ds;
		ww2 = wx*(1.0-wy)*ds;
		ww3 = (1.0-wx)*wy*ds;
		ww4 = (1.0-wx)*(1.0-wy)*ds;


		sdens[i1*nx+j1] += ww1;
		sdens[i1*nx+(j1+1)] += ww2;
		sdens[(i1+1)*nx+j1] += ww3;
		sdens[(i1+1)*nx+(j1+1)] += ww4;
	}
}

void weighted_cic(double *cic_in,double *x_in,double *y_in,double bsx,double bsy,int nx,int ny,int np,double *cic_out) {
    double dx = bsx/nx;
    double dy = bsy/ny;
    double xc = bsx/2.0;
    double yc = bsy/2.0;
    double wx,wy;
    double xp,yp,zp;

    int i;
    int ip,jp;

    for (i=0;i<np;i++) {
        xp = (x_in[i]+xc)/dx-0.5;
        yp = (y_in[i]+yc)/dy-0.5;
		zp = cic_in[i];

        ip = (int)xp;
        jp = (int)yp;

		if (ip<0||ip>(nx-2)||jp<0||jp>(ny-2)) continue;
        wx = 1.0-(xp-(double)ip);
        wy = 1.0-(yp-(double)jp);

        cic_out[ip*ny+jp] += wx*wy*zp;
        cic_out[ip*ny+(jp+1)] += wx*(1.0-wy)*zp;
        cic_out[(ip+1)*ny+jp] += (1.0-wx)*wy*zp;
        cic_out[(ip+1)*ny+(jp+1)] += (1.0-wx)*(1.0-wy)*zp;
    }
}
