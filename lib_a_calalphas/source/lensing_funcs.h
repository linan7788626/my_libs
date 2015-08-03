void Loadin_sigma_mesh(int Num,char *fname,REAL* sdens);
void Loadin_grids_mesh(REAL boxsize, REAL xc1, REAL xc2, int Ncc, REAL *posx1, REAL *posx2);
//----------------------------------------------------------------------------------
void sdens_to_kappa(REAL pmass, REAL* sdens, int Ncc, REAL Dcell, REAL zl, REAL zs, REAL *kappa);
void zero_padding(REAL *in, int nx, int ny, REAL *out);
//----------------------------------------------------------------------------------
void print_matrix(REAL *in, int nx, int ny);
void center_matrix(REAL *in, int nx, int ny, REAL *out);
void corner_matrix(REAL *in, int nx, int ny, REAL *out);
//----------------------------------------------------------------------------------
void kernel_green_iso(int Ncc, REAL *in, REAL Dcell);
void kernel_shears_iso(int Ncc,REAL *in1,REAL *in2,REAL Dcell);
void kernel_alphas_iso(int Ncc,REAL *in1,REAL *in2,REAL Dcell);
void kernel_smooth_iso(double sigma,int Ncc,REAL *in,REAL Dcell);
//----------------------------------------------------------------------------------
void lanczos_diff_1_tag(REAL *mi, REAL *m1, REAL *m2, REAL Dcell, int Ncc, int dif_tag);
void lanczos_diff_2_tag(REAL *m1, REAL *m2, REAL *m11, REAL *m12, REAL *m21, REAL *m22, REAL Dcell, int Ncc, int dif_tag);
//----------------------------------------------------------------------------------
void write_2_signals(char *out1,char *out2,REAL *in1,REAL *in2, int Ncc);
void write_1_signal(char *out1,REAL *in1, int Ncc);
void print_1_signal(REAL *in1,int Ncc);
void print_2_signals(REAL *in1,REAL *in2,int Ncc);
//----------------------------------------------------------------------------------
void kappa_to_phi(REAL *kappa, REAL *phi,int Ncc2,REAL Dcell);
void kappa_to_alphas(REAL *kappa,REAL *alpha1,REAL *alpha2,int Ncc2,REAL Dcell);
void kappa_to_shears(REAL *kappa,REAL *shear1,REAL *shear2, int Ncc2,REAL Dcell);
void kappa_to_kappac(REAL *kappa,REAL *kappa_cal, int Ncc2,REAL Dcell);
//----------------------------------------------------------------------------------
void sdens_to_phi(REAL pmass, REAL * sdens, int Nc, REAL boxsize, REAL zl, REAL zs, REAL * phi);
void sdens_to_kappac(REAL pmass, REAL * sdens, int Nc, REAL boxsize, REAL zl, REAL zs, REAL * kappac);
void sdens_to_alphas(REAL pmass, REAL * sdens, int Nc, REAL boxsize, REAL zl, REAL zs, REAL * alpha1, REAL * alpha2);
void sdens_to_shears(REAL pmass, REAL * sdens, int Nc, REAL boxsize, REAL zl, REAL zs, REAL * shear1, REAL * shear2);
void sdens_to_mu(REAL pmass, REAL *sdens, int Nc, REAL boxsize, REAL zl, REAL zs, REAL *mu);
//----------------------------------------------------------------------------------
void nkappa_to_alphas(REAL *kappa,REAL *alpha1,REAL *alpha2,int Nc,REAL Dcell);
//----------------------------------------------------------------------------------
void calculate_mu(REAL *kappa,REAL *shear1,REAL *shear2, int Ncc, REAL *mu);
void find_critical_curves(REAL *mu_in, int nx, int ny,REAL *mu_out);
