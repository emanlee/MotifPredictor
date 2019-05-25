#include <malloc.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"  
#include "get_model_TF.h"

/*
  cd /data/source/
  rm -rf get_model_TF*
  
Compile:
 LANG=C gcc -Wall get_model_TF.c  -o get_model_TF

Run: 
./get_model_TF  \
-input_TF2miRNA   humanCP.TF2miRNA.txt \
-input_TF2gene    humanCP.TF2gene.txt    \
-input_miRNA2TF   humanCP.miRNA2TF.txt   \
-input_miRNA2gene humanCP.miRNA2gene.txt  \
-output_file      humanCP.TF_motif.txt

 */

int main(int argc, char *argv[]) 
{

	char input_TF2miRNA[800]="";
	char input_TF2gene[800]="";   
	char input_miRNA2gene[800]="";  
//	char input_miRNA2TF[800]="";  ////// NO need this file 

	char output_file[800]="";  
	
	long i,  row_count;
	struct pairnode *tf2miRNAnodes,  *tf2genenodes, *miRNA2genenodes;
	long rowcount_tf2miRNA, rowcount_tf2gene, rowcount_miRNA2gene ;
	 
 

	if (argc>2)
	{
		for (i=0; i<argc; i++)
		{
			if ( strcmp(argv[i], "-input_TF2miRNA")==0)// 
			{
				i=i+1;
				strcpy(input_TF2miRNA, argv[i]);
			}
			if ( strcmp(argv[i], "-input_TF2gene")==0)// 
			{
				i=i+1;
				strcpy(input_TF2gene, argv[i]);
			}
			if ( strcmp(argv[i], "-input_miRNA2gene")==0)// 
			{
				i=i+1;
				strcpy(input_miRNA2gene, argv[i]);
			}
			 
//			if ( strcmp(argv[i], "-input_miRNA2TF")==0)// 
//			{
//				i=i+1;
//				strcpy(input_miRNA2TF, argv[i]);
//			}
			if ( strcmp(argv[i], "-output_file")==0)// 
			{
				i=i+1;
				strcpy(output_file, argv[i]);
			} 
		 

			
		}		 
	}
	
	if (argc<=2)
	{
		puts("usage\n get_model_TF \n");
	 
		//return -1;
	}
	
	
	//load file 
	//	
	printf("loading file %s ...\n",input_TF2miRNA);
	row_count=file_line_count(input_TF2miRNA);
	//struct pairnode *tf2miRNAnodes
	tf2miRNAnodes=(struct pairnode *)malloc(row_count*sizeof(struct pairnode));  
	load_files(input_TF2miRNA, tf2miRNAnodes, &rowcount_tf2miRNA);
	 
 
	//load file 
	//	struct pairnode  *tf2genenodes 
	printf("loading file %s ...\n",input_TF2gene);
	row_count=file_line_count(input_TF2gene);
	
	tf2genenodes=(struct pairnode *)malloc(row_count*sizeof(struct pairnode));  
	load_files(input_TF2gene, tf2genenodes, &rowcount_tf2gene);

	//load file  
	//		puts("  load file input_miRNA2gene")
	printf("loading file %s ...\n",input_miRNA2gene);
	row_count=file_line_count(input_miRNA2gene);
	//struct pairnode   *miRNA2genenodes;
	miRNA2genenodes=(struct pairnode *)malloc(row_count*sizeof(struct pairnode));  
	load_files(input_miRNA2gene, miRNA2genenodes, &rowcount_miRNA2gene);

	
	// 
	 get_model(   tf2miRNAnodes,    rowcount_tf2miRNA,
				  tf2genenodes,     rowcount_tf2gene,
				  miRNA2genenodes,  rowcount_miRNA2gene,
				  output_file
				);

	free(tf2miRNAnodes);  
	free(tf2genenodes);   
	free(miRNA2genenodes);  

	return 0;
}




