/* this holds a pnode */
struct pnode
{
  struct pnode *parent;
  struct region *region;
  double weight;
  double relevance;
  struct llitem *childllitem;
  int broodsize;
  void *temp; /* for histograms and such */
};

/* this holds a ptree */
struct ptree
{
  int nregions;
  struct region **regionra;
  int nlegs;
  int legtime;
  int length;
  struct llitem **eventra;
  int tab;
  double update_every;
  double update_last;
  double total_time;
  int gate_flag;
  struct llitem *pretree;
  struct llitem *postree;
  struct hist *wh;
  struct hist *rh;
};

/* this holds a obsdisthist */
struct obsdisthist
{
  int length;
  struct hist **hra;
  int nrecords;
  double *value;
  double *ballot_2;
  double *ballot_3;
};

/* this holds a region */
struct region
{
  int region_type;
  int label;
  double last_event;
  double event_within;
  int event_threshold;
  struct llist *neuronllist;
  struct pnode *pn; /* for yggdrasil->pp regions */
};

/* Here are the ptree functions */
struct pnode * pnodemake(struct pnode *,struct region *,double,double);
void pnodetfree(void *);
struct ptree * ptreemake(int,double,int,int,int,int);
void ptreemakepospre(struct ptree *);
void ptreereset(struct ptree *);
void ptreetfree(struct ptree *);
int region2region_compare_last_event(void *,void *);
int region2region_compare_label(void *,void *);
int region2pnode_compare_label(void *,void *);
int pnode2pnode_compare_label(void *,void *);
int pnode2pnode_compare_relevance(void *,void *);
int pnode2pnode_compare_weight(void *,void *);
void regionramake(struct ptree *,double,int,int);
void regionratfree(struct ptree *);
int region_has_event(struct region *,double,double);
int region_has_event_old(struct region *,double,double);
void ptreeupdate_helper(struct ptree *,double,double,double,int);
void ptreeupdate(struct ptree *,double,double,double);
void pstrengthen_starter(struct ptree *,struct llist *,double);
void pstrengthen_helper(int,struct ptree *,struct pnode *,struct llitem *,struct llist *,int,double);
void pnodeprintf(struct pnode *,struct llitem *,int,int);
void pnodeprune_starter(int,struct ptree *,struct pnode *,struct llitem *,struct llist *);
void pnodeprune_helper(int,struct ptree *,struct pnode *,struct llist *);
double pnode_shear(double,double);
void pnodeZZZ_starter(int,struct ptree *,struct pnode *,struct llitem *,double,int);
void pnodeZZZ_helper(int,struct ptree *,struct pnode *,double);
void pnodebalance_starter(struct pnode *,struct llitem *);
void ptreerate(struct ptree *);
struct llist * ptreextract_starter(struct ptree *,double,int);
void ptreextract_helper(struct pnode *,struct llitem *,struct region **,double);
double pnode_worth(double,double,double);
void ptree2jpg_starter(struct ptree *,char *,double,double,double,double);
void ptree2jpg_helper(int,int,double,double,double,double,struct pnode *,struct llitem *,FILE *,FILE *,struct llist *);
void ptree2star_helper(int,int,int,double,double,double,double,struct pnode *,struct llitem *,FILE *,FILE *,struct llist *);
void ptreedump_starter(struct ptree *,char *,int,int,double,double,double,double,int);
void ptreedump_helper(int,struct pnode *,struct llitem *,FILE *,struct llist *,int);
struct ptree * ptreadback(char *,int);
void ptreeplusequals_starter(struct ptree *,struct ptree *);
void ptreeplusequals_helper(struct ptree *,struct pnode *,struct llitem *,struct ptree *,struct pnode *,struct llitem *);
struct ptree * ptreesetequalto_starter(struct ptree *);
void ptreesetequalto_helper(struct ptree *,struct pnode *,struct llitem *,struct ptree *,struct pnode *,struct llitem *);
struct ptree * ptreesubtptree_starter(struct ptree *,struct ptree *,int);
void ptreesubtptree_helper(struct ptree *,struct pnode *,struct llitem *,struct ptree *,struct pnode *,struct llitem *,double);
void pnodefrob_starter(struct pnode *,struct llitem *,int,int,double *,double *);
void ptreex2(struct ptree *,struct pnode *,struct llitem *,struct ptree *,struct pnode *,struct llitem *,int,int,int,double *,double *,double *,double *);
void ptreerelent_breadth(struct ptree *,struct pnode *,struct llitem *,struct ptree *,struct pnode *,struct llitem *,int,int,int,int,double *,double *,double *);
void ptreerelent_depth(struct ptree *,struct pnode *,struct llitem *,struct ptree *,struct pnode *,struct llitem *,int,int,int,double *);
void pnodeclear_starter(struct pnode *,struct llitem *);
void pnodetimesd_starter(struct pnode *,struct llitem *,double,double);
void pnodefabswr_starter(struct pnode *,struct llitem *,double,double);
void pnodestats_starter(struct pnode *,struct llitem *,int,int,int,int *,double *,double *,double *,double *,double *,double *,double *,double *);
void pnode2llist_starter(struct pnode *,struct llitem *,int,int,struct llist *);
void pnode2hist_starter(struct pnode *,struct llitem *,int,int,struct hist *,struct hist *);
void pnodehist_starter(struct pnode *,struct llitem *,int,int,struct hist *,struct hist *);
double ptreex2_match(int,int,double *,int *);
double ptreex1_smatch(int,int,double *,double,int *);
double ptreex1_xmatch(int,int,double *,double,int *);
void ptreex1(int,struct ptree **,struct pnode **,struct llitem **,int,struct ptree *,struct pnode *,struct llitem *,struct ptree *,struct pnode *,struct llitem *,int,int);
void ptreex1sbias(int ,struct ptree **,struct pnode **,struct llitem **,int,struct ptree *,struct pnode *,struct llitem *,struct ptree *,struct pnode *,struct llitem *,int,int,int,double *,double *);
void pnodeprintf_label(void *);
void pnodeshizuffle_starter(struct pnode *,struct llitem *,struct ptree *);
void ptreex2_disthist(double *,double *,int);
double logfactorial(double);
double binomial(double,double,double);
double Pmode(double,double,int,double *);
double multithresh_single(double *,int,double);
double multithresh(double *,int,double);
void discdata_threshold(double *,int,int,int ,char *);
void llistmedian(struct llist *,struct llist *,int (*)(void *,void *),int,void **,int *,int *);
void ptreeobsdistend(int,int,struct ptree *,struct pnode *,struct llitem *,int);
void obsdistdisc(int,int,struct llist **,double *,double *);
void ptreeobsdist(int,struct ptree *,struct pnode *,struct llitem *,int,struct ptree *,struct pnode *,struct llitem *,int,int);
void ptree_trialaverage_helper(int,int,int,int,int,int,int,int,char **,char *);
void ptree_trialaverage(int,char **);
void pnode2distribution_starter(struct ptree *,struct pnode *,struct llitem *,struct ptree *,struct pnode *,struct llitem *,int,int);
void pnode2distribution_helper(struct ptree *,struct pnode *,struct llitem *,int,int,struct llist **,int,int,struct hist **);
void pnode2distribution_ender(struct ptree *,struct pnode *,struct llitem *,int,int);
void ptree_trialdistribution_helper(int,int,int,int,char **,char *);
void ptree_trialdistribution(int,char **);
struct obsdisthist * obsdisthistmake(int);
void obsdisthisttfree(struct obsdisthist *);
void obsdisthist2file(void *,FILE *);
void * file2obsdisthist(FILE *,int *);
void obsdisthistupdate(struct obsdisthist *,int,double,double);
void obsdisthistprintf(struct obsdisthist *,char *);
void obsdisthistappraise(struct obsdisthist *,int,int);
void obsdisthistevaluate_helper(int,int,int,double *,int,int,int,double *,double *);
void obsdisthistevaluate(struct obsdisthist *,int,int);
void pnode_obs2dist_starter(int,int,int,struct pnode *,struct llitem *,int,int,int);
void ptree_classify_helper1(struct ptree *,struct pnode *,struct llitem *,struct ptree *,struct pnode *,struct llitem *,int,int,int);
void ptree_classify_helper2(struct ptree *,struct pnode *,struct llitem *,int,int,int,double *,double *);
void ptree_classify_helper3(char *,int,int,struct ptree *,double *,double *);
void ptree_classify_starter(int,int,int,char **,char *,int);
void ptree_dumptemp_starter(struct ptree *,char *,int,void (*)(void *,FILE *),int);
void ptree_dumptemp_helper(int ,struct pnode *,struct llitem *,FILE *,struct llist *,void (*)(void *,FILE *),int);
struct ptree * ptree_readbacktemp(char *,void *(*)(FILE *,int *),int *);
void hist_tofig(void *,FILE *,void *,double,double,double);
void pnode_obsdisthist_tofig(void *,FILE *,void *,double,double,double);
void pnode_tofig_helper(struct llist *,int,struct pnode *,struct llitem *,int,int,FILE *,void (*)(void *,FILE *,void *,double,double,double),void *);
void pnode_obsdisthist_tofig_starter(struct ptree *,char *,int);
double pnode_obsdisthist_value(void *,void *);
void pnode_statstemp_starter(struct pnode *,struct llitem *,int,int,int,int *,double *,double *,double *,double *,double (*)(void *,void *),void *);
void pnode_normanddots(void *,void *,void *);
void pnode_obsdisthist2obsdisthist_appraise(void *,void *,void *);
void pnode2pnode_void_operate(struct ptree *,struct pnode *,struct llitem *,struct ptree *,struct pnode *,struct llitem *,int,int,void (*)(void *,void *,void *),void *,int);
void pnode_set_weight(void *,void *);
void pnode_evaluate_relevance(void *,void *);
void pnode_evaluate_obsdisthist_mean(void *,void *);
void pnode_evaluate_weight(void *,void *);
void pnode_dig_and_evaluate(int,struct litem *,struct ptree *,struct pnode *,struct llitem *,void (*)(void *,void *),void *);
void pnode_obsdisthist2mtrx(void *,void *,void *);
void pnode_obsdisthist2obsdisthist_meansubtmean(void *,void *,void *);
void pnode_obsdisthist2reweight_obsdisthist_mean_shift(void *,void *,void *);
void pnode_obsdisthist2obsdisthist_reweight(void *,void *,void *);
void pnode2pnode_void_hist_operate(struct llist *,struct ptree *,struct pnode *,struct llitem *,struct llist *,struct ptree *,struct pnode *,struct llitem *,int,int,void (*)(struct llist *,void *,struct llist *,void *,void *),void *,int);
