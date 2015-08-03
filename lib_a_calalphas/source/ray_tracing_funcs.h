void Interplation_on_source_plane(REAL *source_map, REAL *posy1, REAL *posy2, REAL ysc1, REAL ysc2,REAL dsi, int nsx, int nsy, int nlx, int nly, REAL *lensed_map);
void sfits_to_lfits(char *source_fits,REAL *posx1, REAL *posx2, REAL *alpha1, REAL *alpha2,REAL ysc1,REAL ysc2, REAL dsi, int nlx, int nly, char *lensed_fits);
void smap_to_lmap(REAL *source_map, int nsx, int nsy, REAL *posx1, REAL *posx2, REAL *alpha1, REAL *alpha2,REAL ysc1,REAL ysc2, REAL dsi, int nlx, int nly, REAL *lensed_map);
REAL *read_from_fits(char *source_fits, long *nsx, long *nsy);
void save_to_fits(REAL *lensed_map, int nlx, int nly, char *lensed_fits);
void simple_sfits_to_lfits(char *source_fits,REAL *posx1, REAL *posx2, REAL *alpha1, REAL *alpha2,REAL ysc1,REAL ysc2, REAL dsi, int nlx, int nly, char *lensed_fits);
