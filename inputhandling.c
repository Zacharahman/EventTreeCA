void readinput()
{
  /* This reads the piped input file, or standard input.
     the variable names should not be longer than 128 characters */
  int verbose=0;
  char vname[128],equals[128],space[128],semicolon[128];
  do{
    scanf("%[^=]",vname);scanf("%s",equals);scanf("%c",space);updateglobals(vname);scanf("%c",semicolon);
    if (verbose){ printf("At this point variable name is (%s), equals is (%s), semicolon is (%s)\n",vname,equals,semicolon);} 
    scanf("%c",semicolon);}
  while (strcmp(vname,"END")!=0);
}

void updateglobals(char *vname)
{
  /* given a variable name, scan the appropriate format into the appropriate global variable */
  int verbose=GLOBAL_verbose;
  char comma_vs_semicolon[1],**strra=NULL;
  int length=0,nv=0;
  if (strcmp(vname,"GLOBAL_verbose")==0){ scanf("%d",&GLOBAL_verbose); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_verbose);}}
  if (strcmp(vname,"ON_MY_COMPUTER")==0){ scanf("%d",&ON_MY_COMPUTER); if (verbose){ printf("%s read to be %d\n",vname,ON_MY_COMPUTER);}}
  if (strcmp(vname,"GLOBAL_STRING")==0){ scanf("%[^,;]",GLOBAL_STRING); if (verbose){ printf("%s read to be %s\n",vname,GLOBAL_STRING);}}
  if (strcmp(vname,"GLOBAL_RECORD_NUMBER")==0){ scanf("%d",&GLOBAL_RECORD_NUMBER); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_RECORD_NUMBER);}}
  if (strcmp(vname,"GLOBAL_Lra_length")==0){ scanf("%d",&GLOBAL_Lra_length); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_Lra_length);}}
  if (strcmp(vname,"GLOBAL_Yisun_length")==0){ scanf("%d",&GLOBAL_Yisun_length); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_Yisun_length);}}
  if (strcmp(vname,"GLOBAL_TF")==0){ scanf("%lf",&GLOBAL_TF); if (verbose){ printf("%s read to be %lf\n",vname,GLOBAL_TF);}}
  if (strcmp(vname,"PTREE_BOTHER")==0){ scanf("%d",&PTREE_BOTHER); if (verbose){ printf("%s read to be %d\n",vname,PTREE_BOTHER);}}
  if (strcmp(vname,"GLOBAL_PTREE_BITBYBIT")==0){ scanf("%d",&GLOBAL_PTREE_BITBYBIT); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_PTREE_BITBYBIT);}}
  if (strcmp(vname,"GLOBAL_PTREE_BITBYBIT_CURRENT_NUMBER")==0){ scanf("%d",&GLOBAL_PTREE_BITBYBIT_CURRENT_NUMBER); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_PTREE_BITBYBIT_CURRENT_NUMBER);}}
  if (strcmp(vname,"GLOBAL_PTREE_ZZZ")==0){ scanf("%d",&GLOBAL_PTREE_ZZZ); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_PTREE_ZZZ);}}
  if (strcmp(vname,"GLOBAL_PTREE_NREGIONS")==0){ scanf("%d",&GLOBAL_PTREE_NREGIONS); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_PTREE_NREGIONS);}}
  if (strcmp(vname,"GLOBAL_PTREE_NLEGS")==0){ scanf("%d",&GLOBAL_PTREE_NLEGS); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_PTREE_NLEGS);}}
  if (strcmp(vname,"GLOBAL_PTREE_LEGTIME")==0){ scanf("%d",&GLOBAL_PTREE_LEGTIME); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_PTREE_LEGTIME);}}
  if (strcmp(vname,"GLOBAL_PTREE_EVENT_THRESHOLD")==0){ scanf("%d",&GLOBAL_PTREE_EVENT_THRESHOLD); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_PTREE_EVENT_THRESHOLD);}}
  if (strcmp(vname,"GLOBAL_PTREE_EVENT_WITHIN")==0){ scanf("%lf",&GLOBAL_PTREE_EVENT_WITHIN); if (verbose){ printf("%s read to be %lf\n",vname,GLOBAL_PTREE_EVENT_WITHIN);}}
  if (strcmp(vname,"GLOBAL_PTREE_REGION_TYPE")==0){ scanf("%d",&GLOBAL_PTREE_REGION_TYPE); if (verbose){ printf("%s read to be %d\n",vname,GLOBAL_PTREE_REGION_TYPE);}}
  if (strcmp(vname,"END")==0){ /* do nothing */ if (verbose){ printf("end of input reached\n");}}
/*   if (strcmp(vname,"yy")==0){ scanf("%zz",&yy); if (verbose){ printf("%s read to be %zz\n",vname,yy);}} */
}

void dumpoutput(char *filename)
{
  /* prints an output file */
  int verbose=0;
  char text[256];
  char vname[128];
  FILE *fp=NULL;
  int length=0,nv=0;
  if (verbose){ printf(" %% [entering dumpoutput]\n");}
  sprintf(text,"./%s%s",filename,GLOBAL_STRING);
  if (filename==NULL || (fp = fopen(text, "w")) == NULL){ printf("dumpoutput to stdout\n"); fp = stdout;}
  sprintf(vname,"GLOBAL_verbose"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_verbose);
  sprintf(vname,"ON_MY_COMPUTER"); fprintf(fp,"%s= %d;\n",vname,ON_MY_COMPUTER);
  sprintf(vname,"GLOBAL_STRING"); fprintf(fp,"%s= %s;\n",vname,GLOBAL_STRING);
  sprintf(vname,"GLOBAL_RECORD_NUMBER"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_RECORD_NUMBER);
  sprintf(vname,"GLOBAL_Lra_length"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_Lra_length);
  sprintf(vname,"GLOBAL_Yisun_length"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_Yisun_length);
  sprintf(vname,"GLOBAL_TF"); fprintf(fp,"%s= %lg;\n",vname,GLOBAL_TF);
  sprintf(vname,"PTREE_BOTHER"); fprintf(fp,"%s= %d;\n",vname,PTREE_BOTHER);
  sprintf(vname,"GLOBAL_PTREE_BITBYBIT"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_PTREE_BITBYBIT);
  sprintf(vname,"GLOBAL_PTREE_BITBYBIT_CURRENT_NUMBER"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_PTREE_BITBYBIT_CURRENT_NUMBER);
  sprintf(vname,"GLOBAL_PTREE_ZZZ"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_PTREE_ZZZ);
  sprintf(vname,"GLOBAL_PTREE_NREGIONS"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_PTREE_NREGIONS);
  sprintf(vname,"GLOBAL_PTREE_NLEGS"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_PTREE_NLEGS);
  sprintf(vname,"GLOBAL_PTREE_LEGTIME"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_PTREE_LEGTIME);
  sprintf(vname,"GLOBAL_PTREE_EVENT_THRESHOLD"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_PTREE_EVENT_THRESHOLD);
  sprintf(vname,"GLOBAL_PTREE_EVENT_WITHIN"); fprintf(fp,"%s= %lg;\n",vname,GLOBAL_PTREE_EVENT_WITHIN);
  sprintf(vname,"GLOBAL_PTREE_REGION_TYPE"); fprintf(fp,"%s= %d;\n",vname,GLOBAL_PTREE_REGION_TYPE);
  sprintf(vname,"END"); fprintf(fp,"END= 0");
  if (fp!=stdout){ fclose(fp);}
/*   sprintf(vname,"yy"); fprintf(fp,"%s= ",vname); length=ww; for (nv=0;nv<length;nv++){ fprintf(fp,"%zz%s",yy[nv],nv<length-1?",":";");} fprintf(fp,"\n"); */
/*   sprintf(vname,"yy"); fprintf(fp,"%s= %zz;\n",vname,yy); */
  if (verbose){ printf(" %% [finishing dumpoutput]\n");}
}
